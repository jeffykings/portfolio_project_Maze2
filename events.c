#include "main.h"

/**
 * handle_events - Process SDL events
 * @game: Pointer to the GameState structure
 */
void handle_events(GameState *game)
{
    SDL_Event event;
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
                    case SDLK_LEFT:
                        game->player_angle -= 0.1f;
                        break;
                    case SDLK_RIGHT:
                        game->player_angle += 0.1f;
                        break;
                    case SDLK_UP:
                        game->player_pos.x += cosf(game->player_angle) * 0.2f;
                        game->player_pos.y += sinf(game->player_angle) * 0.2f;
                        break;
                    case SDLK_DOWN:
                        game->player_pos.x -= cosf(game->player_angle) * 0.2f;
                        game->player_pos.y -= sinf(game->player_angle) * 0.2f;
                        break;
                }
                break;
        }
    }
}
