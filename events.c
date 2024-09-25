#include "main.h"

/**
 * handle_events - Process SDL events and update game state
 * @game: Pointer to the GameState structure
 */
void handle_events(GameState *game)
{
    SDL_Event event;
    const Uint8 *keyboard_state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                game->is_running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        game->is_running = false;
                        break;
                    case SDLK_m:
                        game->show_map = !game->show_map;
                        break;
                    case SDLK_r:
                        game->is_raining = !game->is_raining;
                        break;
                    case SDLK_1:
                    case SDLK_2:
                    case SDLK_3:
                        game->current_weapon = event.key.keysym.sym - SDLK_1;
                        break;
                }
                break;
        }
    }

    /** Handle continuous key presses for movement */
    float move_speed = 0.1f;
    float rotation_speed = 0.05f;

    if (keyboard_state[SDL_SCANCODE_LEFT])
        game->player_angle -= rotation_speed;
    if (keyboard_state[SDL_SCANCODE_RIGHT])
        game->player_angle += rotation_speed;

    float move_x = 0, move_y = 0;
    if (keyboard_state[SDL_SCANCODE_W])
    {
        move_x += cosf(game->player_angle) * move_speed;
        move_y += sinf(game->player_angle) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_S])
    {
        move_x -= cosf(game->player_angle) * move_speed;
        move_y -= sinf(game->player_angle) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_A])
    {
        move_x += sinf(game->player_angle) * move_speed;
        move_y -= cosf(game->player_angle) * move_speed;
    }
    if (keyboard_state[SDL_SCANCODE_D])
    {
        move_x -= sinf(game->player_angle) * move_speed;
        move_y += cosf(game->player_angle) * move_speed;
    }

    /** Apply movement if no collision */
    if (!handle_collisions(game->player_pos.x + move_x, game->player_pos.y))
        game->player_pos.x += move_x;
    if (!handle_collisions(game->player_pos.x, game->player_pos.y + move_y))
        game->player_pos.y += move_y;
}
