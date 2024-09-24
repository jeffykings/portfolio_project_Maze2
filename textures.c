#include "main.h"

/* Array to hold wall textures */
SDL_Texture *wall_textures[4];

/**
 * load_textures - Load textures for walls
 *
 * Return: 0 on success, -1 on failure
 */
int load_textures(void)
{
    const char *texture_files[4] = {
        "wall_north.bmp",
        "wall_south.bmp",
        "wall_east.bmp",
        "wall_west.bmp"
    };

    for (int i = 0; i < 4; i++)
    {
        SDL_Surface *surface = SDL_LoadBMP(texture_files[i]);
        if (!surface)
        {
            fprintf(stderr, "Error loading texture: %s\n", SDL_GetError());
            return (-1);
        }

        wall_textures[i] = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!wall_textures[i])
        {
            fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
            return (-1);
        }
    }

    return (0);
}

/**
 * cleanup_textures - Clean up loaded textures
 */
void cleanup_textures(void)
{
    for (int i = 0; i < 4; i++)
    {
        SDL_DestroyTexture(wall_textures[i]);
    }
}
