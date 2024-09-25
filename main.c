#include "main.h"

/**
 * main - Entry point for the maze game
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char *argv[])
{
    GameState game;
    bool quit = false;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    if (!init_sdl(&game))
    {
        fprintf(stderr, "Failed to initialize SDL\n");
        return 1;
    }

    if (!load_map(&game, argv[1]))
    {
        fprintf(stderr, "Failed to load map\n");
        cleanup(&game);
        return 1;
    }

    while (!quit)
    {
        handle_events(&game, &quit);
        cast_rays(&game);
        draw_floor_ceiling(&game);
        draw_walls(&game);
        draw_map(&game);
        SDL_RenderPresent(game.renderer);
    }

    cleanup(&game);
    return 0;
}
