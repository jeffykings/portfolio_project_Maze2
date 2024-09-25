#include "main.h"

#define FOV (M_PI / 3)
#define HALF_FOV (FOV / 2)
#define NUM_RAYS SCREEN_WIDTH
#define MAX_DEPTH 16

typedef struct {
    float distance;
    int wall_type;
    float wall_x;
} RaycastHit;

/**
 * cast_ray - Cast a single ray and return hit information
 * @game: Pointer to the GameState structure
 * @angle: Angle of the ray
 *
 * Return: RaycastHit structure with hit information
 */
static RaycastHit cast_ray(GameState *game, float angle)
{
    RaycastHit hit = {0};
    float sin_a = sinf(angle);
    float cos_a = cosf(angle);

    float dist = 0;
    int hit_wall = 0;

    while (!hit_wall && dist < MAX_DEPTH)
    {
        dist += 0.1f;
        int test_x = (int)(game->player_pos.x + cos_a * dist);
        int test_y = (int)(game->player_pos.y + sin_a * dist);

        if (test_x < 0 || test_x >= MAP_WIDTH || test_y < 0 || test_y >= MAP_HEIGHT)
        {
            hit_wall = 1;
            hit.distance = MAX_DEPTH;
        }
        else if (worldMap[test_x][test_y] != 0)
        {
            hit_wall = 1;
            hit.distance = dist;
            hit.wall_type = worldMap[test_x][test_y];
            
            /** Calculate wall_x for texture mapping */
            float wall_x = game->player_pos.x + cos_a * dist;
            float wall_y = game->player_pos.y + sin_a * dist;
            hit.wall_x = wall_x - floorf(wall_x);
            if (cos_a > 0.0001 || cos_a < -0.0001)
                hit.wall_x = wall_y - floorf(wall_y);
        }
    }

    return hit;
}

/**
 * render_frame - Render a single frame of the game
 * @game: Pointer to the GameState structure
 */
void render_frame(GameState *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
    SDL_RenderClear(game->renderer);

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        float ray_angle = (game->player_angle - HALF_FOV) + ((float)x / (float)SCREEN_WIDTH) * FOV;
        RaycastHit hit = cast_ray(game, ray_angle);

        /** Adjust for fisheye effect */
        float corrected_dist = hit.distance * cosf(ray_angle - game->player_angle);

        /** Calculate wall height */
        int wall_height = (int)((float)SCREEN_HEIGHT / corrected_dist);

        /** Clamp wall height */
        if (wall_height > SCREEN_HEIGHT)
            wall_height = SCREEN_HEIGHT;

        int wall_top = (SCREEN_HEIGHT / 2) - (wall_height / 2);
        int wall_bottom = (SCREEN_HEIGHT / 2) + (wall_height / 2);

        /** Draw ceiling */
        SDL_SetRenderDrawColor(game->renderer, 100, 100, 100, 255);
        SDL_RenderDrawLine(game->renderer, x, 0, x, wall_top);

        /** Draw textured wall */
        int texture_x = (int)(hit.wall_x * TILE_SIZE);
        for (int y = wall_top; y < wall_bottom; y++)
        {
            int texture_y = (y - wall_top) * TILE_SIZE / wall_height;
            SDL_Color color = get_texture_color(hit.wall_type - 1, texture_x, texture_y);
            SDL_SetRenderDrawColor(game->renderer, color.r, color.g, color.b, 255);
            SDL_RenderDrawPoint(game->renderer, x, y);
        }

        /** Draw floor */
        SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
        SDL_RenderDrawLine(game->renderer, x, wall_bottom, x, SCREEN_HEIGHT);
    }

    if (game->show_map)
        draw_map(game);

    SDL_RenderPresent(game->renderer);
}

/**
 * draw_map - Draw the 2D map on the screen
 * @game: Pointer to the GameState structure
 */
void draw_map(GameState *game)
{
    int map_size = 100;
    int tile_size = map_size / MAP_WIDTH;

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            SDL_Rect tile_rect = {x * tile_size, y * tile_size, tile_size, tile_size};
            if (worldMap[x][y] != 0)
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            else
                SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(game->renderer, &tile_rect);
        }
    }

    /** Draw player on map */
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_Rect player_rect = {
        (int)(game->player_pos.x * tile_size) - 2,
        (int)(game->player_pos.y * tile_size) - 2,
        4, 4
    };
    SDL_RenderFillRect(game->renderer, &player_rect);
}
