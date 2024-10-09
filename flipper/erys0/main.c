/*
MIT License

Copyright (c) 2024 erysdren (it/she/they)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>

#define S3L_RESOLUTION_X 128
#define S3L_RESOLUTION_Y 64
#define S3L_FLAT 1
#define S3L_NEAR_CROSS_STRATEGY 2
#define S3L_SORT 1
#define S3L_PIXEL_FUNCTION PlotPixel
#include "small3dlib.h"

#define S3L_UNIT(x) ((S3L_Unit)((x) * S3L_FRACTIONS_PER_UNIT))

#define ORDERED_DITHER (1)
#define MAX_DEPTH (S3L_F * 16)
#define DEPTH_BIAS (S3L_F * 8)

static uint8_t screen[(128 * 64) / 8];
#define PITCH (128 / 8)

static S3L_Unit s3l_cube_vertices[] = { S3L_CUBE_VERTICES(S3L_F * 4) };
static S3L_Index s3l_cube_triangles[] = { S3L_CUBE_TRIANGLES };
static S3L_Model3D s3l_cube_model;
static S3L_Scene s3l_scene;

static inline void PlotPixel(S3L_PixelInfo *pixel)
{
	uint8_t *ofs;
	unsigned int shift, mask;
	Color color;

#if ORDERED_DITHER
	uint8_t i;
	float depth;
	static const uint8_t bayer_4x4[4 * 4] = {
		1, 9, 3, 11,
		13, 5, 15, 7,
		4, 12, 2, 10,
		16, 8, 14, 6
	};

	i = bayer_4x4[((pixel->y % 4) * 4) + (pixel->x % 4)];

	depth = ((float)pixel->depth - (float)DEPTH_BIAS) / (float)MAX_DEPTH;

	depth += (float)i / 16.0f - 0.5f;

	if (depth < 0.5)
		color = ColorBlack;
	else
		return;

#else
	color = ColorBlack;
#endif

	/* get buffer offset */
	ofs = &screen[pixel->y * PITCH + (pixel->x >> 3)];

	/* get shift and mask */
	shift = pixel->x & 7;
	mask = 0x1 << shift;

	/* OR the color in at ofs */
	*ofs = (*ofs & ~mask) | ((color & 0x1) << shift);
}

/* application state */
typedef struct AppState {
	ViewPort *view_port;
	Gui *gui;
	FuriMessageQueue *event_queue;
	FuriMutex *mutex;
} AppState;

/* input handler */
static void input_callback(InputEvent *input_event, void *ctx)
{
	FuriMessageQueue *queue = (FuriMessageQueue *)ctx;
	furi_assert(queue);
	furi_message_queue_put(queue, input_event, 0);
}

/* rendering handler */
static void render_callback(Canvas *const canvas, void *ctx)
{
	AppState *app = (AppState *)ctx;
	furi_assert(app);

	furi_mutex_acquire(app->mutex, FuriWaitForever);

	canvas_clear(canvas);
	memset(screen, 0, sizeof(screen));

	S3L_newFrame();
	S3L_drawScene(s3l_scene);

	canvas_draw_bitmap(canvas, 0, 0, 128, 64, screen);

#if 0
	canvas_set_color(canvas, ColorBlack);
	canvas_draw_box(canvas, 0, 0, 128, 64);
#endif

#if 0
	char str[16];
	snprintf(str, sizeof(str), "%0.4f", test_depth);
	canvas_set_color(canvas, ColorXOR);
	canvas_set_font(canvas, FontSecondary);
	canvas_draw_str(canvas, 0, 8, str);
#endif

	furi_mutex_release(app->mutex);
}

int32_t app_main(void *p)
{
	AppState *app;

	UNUSED(p);

	/* allocate app state */
	app = malloc(sizeof(AppState));

	/* allocate event queue */
	app->event_queue = furi_message_queue_alloc(8, sizeof(InputEvent));

	/* allocate mutex */
	app->mutex = furi_mutex_alloc(FuriMutexTypeNormal);
	if (!app->mutex)
	{
		FURI_LOG_E("app", "Failed to create mutex\n");
		return 1;
	}

	/* allocate viewport */
	app->view_port = view_port_alloc();
	view_port_draw_callback_set(app->view_port, render_callback, app);
	view_port_input_callback_set(app->view_port, input_callback, app->event_queue);

	/* register viewport */
	app->gui = furi_record_open(RECORD_GUI);
	gui_add_view_port(app->gui, app->view_port, GuiLayerFullscreen);

	/* init s3l */
	S3L_model3DInit(s3l_cube_vertices, S3L_CUBE_VERTEX_COUNT, s3l_cube_triangles, S3L_CUBE_TRIANGLE_COUNT, &s3l_cube_model);
	S3L_sceneInit(&s3l_cube_model, 1, &s3l_scene);
	s3l_scene.camera.transform.translation.z = -8 * S3L_F;

	/* main loop */
	while (1)
	{
		FuriStatus status;
		InputEvent event;

		status = furi_message_queue_get(app->event_queue, &event, 100U);

		furi_mutex_acquire(app->mutex, FuriWaitForever);

		if (status == FuriStatusOk)
		{
			if (event.type == InputTypePress || event.type == InputTypeLong || event.type == InputTypeRepeat)
			{
				switch (event.key)
				{
					case InputKeyUp:
						s3l_scene.camera.transform.translation.z += S3L_F;
						break;

					case InputKeyDown:
						s3l_scene.camera.transform.translation.z -= S3L_F;
						break;

					case InputKeyLeft:
						s3l_scene.camera.transform.rotation.y += (float)S3L_F / 360.0f * 2.0f;
						break;

					case InputKeyRight:
						s3l_scene.camera.transform.rotation.y -= (float)S3L_F / 360.0f * 2.0f;
						break;

					case InputKeyBack:
						goto done;

					default:
						break;
				}
			}
		}

		s3l_scene.models[0].transform.rotation.y += 10;
		s3l_scene.models[0].transform.rotation.x += 4;

		furi_mutex_release(app->mutex);

		view_port_update(app->view_port);
	}

done:

	/* shutdown and free everything */
	view_port_enabled_set(app->view_port, false);
	gui_remove_view_port(app->gui, app->view_port);
	furi_record_close(RECORD_GUI);
	view_port_free(app->view_port);
	furi_message_queue_free(app->event_queue);
	furi_mutex_free(app->mutex);
	free(app);

	return 0;
}
