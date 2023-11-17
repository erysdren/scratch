
/*
 * untextured raycaster
 */

#include "sys16.h"
#include "ray.h"

/* basic map */
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
static uint8_t map[MAP_HEIGHT][MAP_WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/* state */
static uint16_t vid_mode_old;
static fix16_t player_origin_x = FIX16(12);
static fix16_t player_origin_y = FIX16(12);
static uint16_t player_angle = 269;

/* raycaster screen buffer */
uint16_t __far *ray_screen_buffer = NULL;

/* initialize raycaster */
int ray_init(void)
{
	/* store current video mode */
	vid_mode_old = video_get_mode();

	/* set our video mode and see if it failed */
	if (video_set_mode(VIDEO_MODE_02H) != VIDEO_MODE_02H)
		return -1;

	/* allocate offscreen buffer memory */
	ray_screen_buffer = memalloc(80 * 25 * 2);
	if (ray_screen_buffer == NULL)
		return -1;

	/* return success */
	return 1;
}

/* quit raycaster */
void ray_quit(void)
{
	/* free offscreen buffer memory */
	memfree(ray_screen_buffer);

	/* restore video mode we started with */
	video_set_mode(vid_mode_old);

	/* print goodbye message */
	print(str("Thank you for playing!\n\r"));
}

/* run one frame of raycaster */
void ray_frame(void)
{
	/* some constants for mode 02h */
	const int draw_w = 80;
	const int draw_h = 25;

	/* current pixel position */
	int x, y;

	player_angle += 1;
	if (player_angle >= 360) player_angle = 0;

	/* lookup sin and cos of player's view */
	fix16_t sn = FIX16_SIN(player_angle);
	fix16_t cs = FIX16_COS(player_angle);

	/* ray sweep loop */
	for (x = 0; x < draw_w; x++)
	{
		int8_t step_x, step_y;
		fix16_t side_dist_x, side_dist_y;
		int8_t hit = FALSE, side = FALSE, oob = FALSE;
		fix16_t dist;

		/* get map position */
		int16_t map_pos_x = FIX16_TO_INT(player_origin_x);
		int16_t map_pos_y = FIX16_TO_INT(player_origin_y);

		/* calculate ray direction */
		fix16_t raydir_x = FIX16_MUL(FIX16_DIV(FIX16(2.0f), FIX16(draw_w)), FIX16(x)) - FIX16(1.0f);
		fix16_t raydir_y = FIX16(1.0f);

		/* rotate around 0,0 by player_angle */
		fix16_t temp_x = raydir_x;
		fix16_t temp_y = raydir_y;
		raydir_x = FIX16_MUL(-temp_x, cs) - FIX16_MUL(-temp_y, sn);
		raydir_y = FIX16_MUL(temp_x, sn) + FIX16_MUL(temp_y, cs);

		/* prevent divide by zero */
		fix16_t delta_dist_x = (raydir_x == 0) ? FIX16_MAX : ABS(FIX16_DIV(FIX16(1.0f), raydir_x));
		fix16_t delta_dist_y = (raydir_y == 0) ? FIX16_MAX : ABS(FIX16_DIV(FIX16(1.0f), raydir_y));

		/* calculate x step and side_dist */
		if (raydir_x < 0)
		{
			step_x = -1;
			side_dist_x = FIX16_MUL((player_origin_x - FIX16(map_pos_x)), delta_dist_x);
		}
		else
		{
			step_x = 1;
			side_dist_x = FIX16_MUL((FIX16(map_pos_x) + FIX16(1) - player_origin_x), delta_dist_x);
		}

		/* calculate y step and side_dist */
		if (raydir_y < 0)
		{
			step_y = -1;
			side_dist_y = FIX16_MUL((player_origin_y - FIX16(map_pos_y)), delta_dist_y);
		}
		else
		{
			step_y = 1;
			side_dist_y = FIX16_MUL((FIX16(map_pos_y) + FIX16(1.0f) - player_origin_y), delta_dist_y);
		}

		/* perform dda */
		while (hit == FALSE && oob == FALSE)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_pos_x += step_x;
				side = FALSE;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_pos_y += step_y;
				side = TRUE;
			}

			/* check if the ray hit a wall */
			if (map[map_pos_y][map_pos_x] > 0)
				hit = TRUE;

			/* check if ray has gone out of bounds */
			if (map_pos_y >= MAP_HEIGHT || map_pos_y < 0 || map_pos_x >= MAP_WIDTH || map_pos_x < 0)
				oob = TRUE;
		}

		/* move to next ray if we've gone out of bounds */
		if (oob == TRUE)
			continue;

		/* check if we've hit a side or not */
		if (side == FALSE)
			dist = (side_dist_x - delta_dist_x);
		else
			dist = (side_dist_y - delta_dist_y);

		/* prevent divide by zero */
		if (dist <= FIX16(0))
			continue;

		/* height of line to draw on screen */
		int line_height = FIX16_TO_INT(FIX16_DIV(FIX16(draw_h), dist));

		int line_start = -line_height / 2 + draw_h / 2;
		int line_end = line_height / 2 + draw_h / 2;

		/* clamp to vertical area */
		line_start = CLAMP(line_start, 0, draw_h);
		line_end = CLAMP(line_end, 0, draw_h);

		/* draw */
		for (y = line_start; y < line_end; y++)
		{
			ray_screen_buffer[y * draw_w + x] = (uint16_t)map[map_pos_y][map_pos_x] << 8 | 'A';
		}
	}
}
