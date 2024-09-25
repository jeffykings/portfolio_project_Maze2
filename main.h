#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define TILE_SIZE 64

/** Structure to represent a 2D vector */
typedef struct {
    float x;
    float y;
} Vector2;

/** Structure to hold game state */
typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;
    Vector2 player_pos;
    float player_angle;
} GameState;

/** Function prototypes */
bool init_sdl(GameState *game);
void handle_events(GameState *game);
void update_game_state(GameState *game);
void render_frame(GameState *game);
void cleanup(GameState *game);

/** Texture-related functions */
bool load_textures(void);
void unload_textures(void);
SDL_Color get_texture_color(int texture_id, int x, int y);

/** Global variables */
extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

#endif /* MAIN_H */
