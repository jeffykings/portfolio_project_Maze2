#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: 0 on success, exit code on failure
 */
int main(void)
{
    if (init_sdl() != 0)
        return (EXIT_FAILURE);

    load_textures();  /* Load textures */
    load_map("map.txt"); /* Load the map file */

    /* Game loop */
    while (!quit_game)
    {
        handle_input();
        render_walls();
        SDL_RenderPresent(renderer); /* Update screen */
    }

    cleanup_sdl();
    return (0);
}

/**
 * init_sdl - Initialize SDL2 and create window
 *
 * Return: 0 on success, -1 on failure
 */
int init_sdl(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return (-1);

    window = SDL_CreateWindow("Maze Project", SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
        return (-1);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
        return (-1);

    return (0);
}

/**
 * cleanup_sdl - Clean up and quit SDL
 */
void cleanup_sdl(void)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
