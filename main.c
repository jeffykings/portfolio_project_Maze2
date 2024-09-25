#include "main.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
int quit_game = 0;
int map[MAP_WIDTH][MAP_HEIGHT];
Player player

/**
 * main - Entry point of the program
 *
 * Return: 0 on success, exit code on failure
 */
int main(void)
{
    if (init_sdl() != 0)
        return (EXIT_FAILURE);

    if (load_textures() != 0)
        return (EXIT_FAILURE);

    if (load_map("map.txt") != 0)
        return (EXIT_FAILURE);

    /* Game loop */
    while (!quit_game)
    {
        handle_input();
        render_walls();
        SDL_RenderPresent(renderer); /* Update screen */
        SDL_Delay(16); /* Limit to ~60 frames per second */
    }

    cleanup_textures();
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

    quit_game = 0; /* Initialize quit flag to false */
    player.x = 3.0;
    player.y = 3.0;
    player.dir_x = -1.0;
    player.dir_y = 0.0;
    player.plane_x = 0.0;
    player.plane_y = 0.66;

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
