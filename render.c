#include "main.h"

/** ... (keep existing raycasting code) ... */

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
        /** ... (keep existing wall rendering code) ... */

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
