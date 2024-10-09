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

#include <time.h>

#include "qcvm.h"

#define ASIZE(a) (sizeof(a)/sizeof(a[0]))

static struct {
	double primes;
	double start;
	double end;
	double elapsed;
} results;

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
	canvas_set_color(canvas, ColorBlack);
	canvas_set_font(canvas, FontSecondary);

	/* draw information */
	char str[512];
	snprintf(str, sizeof(str), "primes: %f", results.primes);
	canvas_draw_str(canvas, 0, 8, str);
	snprintf(str, sizeof(str), "start: %f", results.start);
	canvas_draw_str(canvas, 0, 16, str);
	snprintf(str, sizeof(str), "end: %f", results.end);
	canvas_draw_str(canvas, 0, 24, str);
	snprintf(str, sizeof(str), "elapsed: %f", results.elapsed);
	canvas_draw_str(canvas, 0, 32, str);

	furi_mutex_release(app->mutex);
}

static void *load_file(const char *filename, size_t *sz)
{
	void *buffer;
	size_t filesize;
	FILE *file;

	file = fopen(filename, "rb");
	if (!file) return NULL;
	fseek(file, 0L, SEEK_END);
	filesize = ftell(file);
	fseek(file, 0L, SEEK_SET);
	buffer = calloc(1, filesize);
	fread(buffer, 1, filesize, file);
	fclose(file);

	if (sz) *sz = filesize;

	return buffer;
}

static int _print(qcvm_t *qcvm)
{
	int argc, r, i;

	if ((r = qcvm_query_argument_count(qcvm, &argc)) != QCVM_OK)
		return r;

	for (i = 0; i < argc; i++)
	{
		const char *s = NULL;

		if ((r = qcvm_get_argument_string(qcvm, i, &s)) != QCVM_OK)
			return r;

		fprintf(stdout, s);
	}

	fflush(stdout);

	return QCVM_OK;
}

struct qcvm_builtin builtins[] = {
	{"print", _print}
};

static void qcvm_test(void)
{
	float r;

	/* load progs */
	qcvm_t *qcvm = calloc(1, sizeof(qcvm_t));
	qcvm->progs = load_file("sieve.dat", &qcvm->len_progs);

	/* setup builtins */
	qcvm->num_builtins = ASIZE(builtins);
	qcvm->builtins = builtins;

	/* init qcvm */
	qcvm_init(qcvm);

	/* get start time */
	results.start = (double)clock() / (double)CLOCKS_PER_SEC;

	/* run sieve function */
	qcvm_run(qcvm, "main");

	/* get return value */
	qcvm_get_return_float(qcvm, &r);
	results.primes = (double)r;

	/* get end time */
	results.end = (double)clock() / (double)CLOCKS_PER_SEC;

	/* get elapsed time */
	results.elapsed = results.end - results.start;

	/* free data */
	free(qcvm->progs);
	free(qcvm);
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

	/* run qcvm test */
	qcvm_test();

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
				if (event.key == InputKeyBack)
					goto done;
			}
		}

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
