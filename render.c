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

        /** Render floor and ceiling with textures */
        for (int y = wall_bottom; y < SCREEN_HEIGHT; y++)
        {
            float distance = SCREEN_HEIGHT / (2.0f * y - SCREEN_HEIGHT);
            float floor_x = game->player_pos.x + distance * cosf(ray_angle);
            float floor_y = game->player_pos.y + distance * sinf(ray_angle);
            int tex_x = (int)(floor_x * TILE_SIZE) % TILE_SIZE;
            int tex_y = (int)(floor_y * TILE_SIZE) % TILE_SIZE;
            SDL_Color floor_color = get_texture_color(5, tex_x, tex_y); /** Assuming texture 5 is floor */
            SDL_Color ceiling_color = get_texture_color(6, tex_x, tex_y); /** Assuming texture 6 is ceiling */
            SDL_SetRenderDrawColor(game->renderer, floor_color.r, floor_color.g, floor_color.b, 255);
            SDL_RenderDrawPoint(game->renderer, x, y);
            SDL_SetRenderDrawColor(game->renderer, ceiling_color.r, ceiling_color.g, ceiling_color.b, 255);
            SDL_RenderDrawPoint(game->renderer, x, SCREEN_HEIGHT - y);
        }
    }

    render_enemies(game);
    render_weapon(game);
    if (game->is_raining)
        render_rain(game);

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

/**
 * render_enemies - Render enemies on the screen
 * @game: Pointer to the GameState structure
 */
void render_enemies(GameState *game)
{
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].is_active)
        {
            /** Calculate enemy position relative to player */
            float dx = game->enemies[i].position.x - game->player_pos.x;
            float dy = game->enemies[i].position.y - game->player_pos.y;
            float distance = sqrtf(dx * dx + dy * dy);
            float enemy_angle = atan2f(dy, dx) - game->player_angle;

            /** Check if enemy is in field of view */
            if (fabsf(enemy_angle) < FOV / 2)
            {
                int enemy_screen_x = (int)((0.5f + enemy_angle / FOV) * SCREEN_WIDTH);
                int enemy_height = (int)(SCREEN_HEIGHT / distance);
                
                /** Render enemy sprite */
                SDL_Rect enemy_rect = {
                    enemy_screen_x - enemy_height / 2,
                    SCREEN_HEIGHT / 2 - enemy_height / 2,
                    enemy_height,
                    enemy_height
                };
                SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
                SDL_RenderFillRect(game->renderer, &enemy_rect);
            }
        }
    }
}

/**
 * render_weapon - Render the current weapon on screen
 * @game: Pointer to the GameState structure
 */
void render_weapon(GameState *game)
{
    SDL_Rect weapon_rect = {
        SCREEN_WIDTH / 2 - 50,
        SCREEN_HEIGHT - 100,
        100,
        100
    };
    SDL_SetRenderDrawColor(game->renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(game->renderer, &weapon_rect);
}

/**
 * render_rain - Render rain effect
 * @game: Pointer to the GameState structure
 */
void render_rain(GameState *game)
{
    SDL_SetRenderDrawColor(game->renderer, 200, 200, 255, 100);
    for (int i = 0; i < 1000; i++)
    {
        int rain_x = rand() % SCREEN_WIDTH;
        int rain_y = rand() % SCREEN_HEIGHT;
        SDL_RenderDrawLine(game->renderer, rain_x, rain_y, rain_x, rain_y + 5);
    }
}
