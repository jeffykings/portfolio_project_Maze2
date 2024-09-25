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
                }
                break;
        }
    }

    /** Handle continuous key presses */
    if (keyboard_state[SDL_SCANCODE_LEFT])
        game->player_angle -= 0.05f;
    if (keyboard_state[SDL_SCANCODE_RIGHT])
        game->player_angle += 0.05f;
    if (keyboard_state[SDL_SCANCODE_UP])
    {
        game->player_pos.x += cosf(game->player_angle) * 0.1f;
        game->player_pos.y += sinf(game->player_angle) * 0.1f;
    }
    if (keyboard_state[SDL_SCANCODE_DOWN])
    {
        game->player_pos.x -= cosf(game->player_angle) * 0.1f;
        game->player_pos.y -= sinf(game->player_angle) * 0.1f;
    }
}
