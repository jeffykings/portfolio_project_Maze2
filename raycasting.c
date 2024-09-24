#include "main.h"

/**
 * render_walls - Render the 3D walls using raycasting, now with textures
 */
void render_walls(void)
{
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        double ray_dir_x = player.dir_x + player.plane_x * camera_x;
        double ray_dir_y = player.dir_y + player.plane_y * camera_x;

        int map_x = (int)player.x;
        int map_y = (int)player.y;

        double side_dist_x, side_dist_y;

        double delta_dist_x = fabs(1 / ray_dir_x);
        double delta_dist_y = fabs(1 / ray_dir_y);
        double perp_wall_dist;

        int step_x, step_y;
        int hit = 0;
        int side;

        if (ray_dir_x < 0)
        {
            step_x = -1;
            side_dist_x = (player.x - map_x) * delta_dist_x;
        }
        else
        {
            step_x = 1;
            side_dist_x = (map_x + 1.0 - player.x) * delta_dist_x;
        }

        if (ray_dir_y < 0)
        {
            step_y = -1;
            side_dist_y = (player.y - map_y) * delta_dist_y;
        }
        else
        {
            step_y = 1;
            side_dist_y = (map_y + 1.0 - player.y) * delta_dist_y;
        }

        while (hit == 0)
        {
            if (side_dist_x < side_dist_y)
            {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0;
            }
            else
            {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1;
            }
            if (map[map_x][map_y] > 0)
                hit = 1;
        }

        if (side == 0)
            perp_wall_dist = (map_x - player.x + (1 - step_x) / 2) / ray_dir_x;
        else
            perp_wall_dist = (map_y - player.y + (1 - step_y) / 2) / ray_dir_y;

        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);

        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_start < 0)
            draw_start = 0;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
        if (draw_end >= SCREEN_HEIGHT)
            draw_end = SCREEN_HEIGHT - 1;

        /* Select texture based on wall orientation */
        SDL_Texture *wall_texture;
        if (side == 1)
        {
            if (ray_dir_y > 0)
                wall_texture = wall_textures[1]; /* South */
            else
                wall_texture = wall_textures[0]; /* North */
        }
        else
        {
            if (ray_dir_x > 0)
                wall_texture = wall_textures[3]; /* West */
            else
                wall_texture = wall_textures[2]; /* East */
        }

        /* Render the texture on the wall */
        SDL_Rect rect = {x, draw_start, 1, draw_end - draw_start};
        SDL_RenderCopy(renderer, wall_texture, NULL, &rect);
    }
}
