#include "main.h"

/**
 * handle_events - Handle user input and events
 * @game: Pointer to the GameState structure
 * @quit: Pointer to the quit flag
 */
void handle_events(GameState *game, bool *quit)
{
    SDL_Event e;
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            *quit = true;
        }
    }

    if (keystate[SDL_SCANCODE_W])
        move_player(game, 0.1f, 0);
    if (keystate[SDL_SCANCODE_S])
        move_player(game, -0.1f, 0);
    if (keystate[SDL_SCANCODE_A])
        move_player(game, 0, -0.1f);
    if (keystate[SDL_SCANCODE_D])
        move_player(game, 0, 0.1f);
    if (keystate[SDL_SCANCODE_LEFT])
        rotate_player(game, -0.1f);
    if (keystate[SDL_SCANCODE_RIGHT])
        rotate_player(game, 0.1f);
}
