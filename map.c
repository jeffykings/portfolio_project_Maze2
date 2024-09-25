#include "main.h"

/**
 * load_map - Load map from file
 * @game: Pointer to the GameState structure
 * @filename: Name of the map file
 * Return: true on success, false on failure
 */
bool load_map(GameState *game, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error opening map file\n");
        return false;
    }

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (fscanf(file, "%d", &game->map[x][y]) != 1)
            {
                fprintf(stderr, "Error reading map data\n");
                fclose(file);
                return false;
            }
        }
    }

    fclose(file);
    return true;
}

/**
 * draw_map - Draw 2D map (for debugging)
 * @game: Pointer to the GameState structure
 */
void draw_map(GameState *game)
{
    int cell_size = 10;
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            SDL_Rect cell = {x * cell_size, y * cell_size, cell_size, cell_size};
            if (game->map[x][y] == 1)
            {
                SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
            }
            else
            {
                SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(game->renderer, &cell);
        }
    }

    /* Draw player position */
    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
    SDL_Rect player = {game->player.x * cell_size, game->player.y * cell_size, cell_size, cell_size};
    SDL_RenderFillRect(game->renderer, &player);
}
