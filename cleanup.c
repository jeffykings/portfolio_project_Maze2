#include "main.h"

/**
 * cleanup - Free resources and quit SDL
 * @game: Pointer to the GameState structure
 */
void cleanup(GameState *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    unload_textures();
    SDL_Quit();
}
