#include "main.h"

#define MAX_DEPTH 30

/**
 * cast_single_ray - Cast a single ray and calculate distance to wall
 * @game: Pointer to the GameState structure
 * @angle: Angle of the ray (in radians)
 * Return: Distance to the wall
 */
static float cast_single_ray(GameState *game, float angle)
{
    float sin_a = sinf(angle);
    float cos_a = cosf(angle);
    float dist = 0;
    int map_x, map_y;

    while (dist < MAX_DEPTH)
    {
        dist += 0.1f;
        map_x = (int)(game->player.x + dist * cos_a);
        map_y = (int)(game->player.y + dist * sin_a);

        if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
            break;

        if (game->map[map_x][map_y] == 1)
            return dist;
    }

    return dist;
}

/**
 * cast_rays - Perform raycasting
 * @game: Pointer to the GameState structure
 */
void cast_rays(GameState *game)
{
    float ray_angle = game->player.angle - FOV / 2 * M_PI / 180;
    float angle_step = (FOV * M_PI / 180) / NUM_RAYS;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        float dist = cast_single_ray(game, ray_angle);
        game->ray_distances[i] = dist * cosf(game->player.angle - ray_angle);
        ray_angle += angle_step;
    }
}

/**
 * draw_walls - Draw walls based on raycasting results
 * @game: Pointer to the GameState structure
 */
void draw_walls(GameState *game)
{
    int wall_height;
    SDL_Rect wall;

    for (int i = 0; i < NUM_RAYS; i++)
    {
        if (game->ray_distances[i] <= 0)
            continue;

        wall_height = (int)(SCREEN_HEIGHT / game->ray_distances[i]);
        if (wall_height > SCREEN_HEIGHT)
            wall_height = SCREEN_HEIGHT;

        wall.x = i;
        wall.y = (SCREEN_HEIGHT - wall_height) / 2;
        wall.w = 1;
        wall.h = wall_height;

        /* Calculate shading based on distance */
        int shade = 255 - (int)(game->ray_distances[i] * 8);
        if (shade < 0)
            shade = 0;

        SDL_SetRenderDrawColor(game->renderer, shade, shade, shade, 255);
        SDL_RenderFillRect(game->renderer, &wall);
    }
}

/**
 * draw_floor_ceiling - Draw floor and ceiling
 * @game: Pointer to the GameState structure
 */
void draw_floor_ceiling(GameState *game)
{
    SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 255);
    SDL_Rect floor = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(game->renderer, &floor);

    SDL_SetRenderDrawColor(game->renderer, 200, 200, 200, 255);
    SDL_Rect ceiling = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderFillRect(game->renderer, &ceiling);
}
