#include "main.h"

#define NUM_TEXTURES 5
#define TEXTURE_SIZE 64

SDL_Surface *wallTextures[NUM_TEXTURES];

/**
 * load_textures - Load wall textures
 *
 * Return: true if successful, false otherwise
 */
bool load_textures(void)
{
    const char *textureFiles[NUM_TEXTURES] = {
        "textures/wall1.bmp",
        "textures/wall2.bmp",
        "textures/wall3.bmp",
        "textures/wall4.bmp",
        "textures/wall5.bmp"
    };

    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        wallTextures[i] = SDL_LoadBMP(textureFiles[i]);
        if (wallTextures[i] == NULL)
        {
            SDL_Log("Failed to load texture: %s", SDL_GetError());
            return false;
        }
    }
    return true;
}

/**
 * unload_textures - Free loaded textures
 */
void unload_textures(void)
{
    for (int i = 0; i < NUM_TEXTURES; i++)
    {
        if (wallTextures[i] != NULL)
        {
            SDL_FreeSurface(wallTextures[i]);
            wallTextures[i] = NULL;
        }
    }
}

/**
 * get_texture_color - Get color from texture at specific coordinates
 * @texture_id: ID of the texture
 * @x: X coordinate on the texture
 * @y: Y coordinate on the texture
 *
 * Return: SDL_Color representing the pixel color
 */
SDL_Color get_texture_color(int texture_id, int x, int y)
{
    SDL_Color color = {0, 0, 0, 255};
    if (texture_id < 0 || texture_id >= NUM_TEXTURES)
        return color;

    SDL_Surface *texture = wallTextures[texture_id];
    if (texture == NULL)
        return color;

    Uint32 *pixels = (Uint32 *)texture->pixels;
    Uint32 pixel = pixels[(y % TEXTURE_SIZE) * TEXTURE_SIZE + (x % TEXTURE_SIZE)];
    SDL_GetRGB(pixel, texture->format, &color.r, &color.g, &color.b);

    return color;
}
