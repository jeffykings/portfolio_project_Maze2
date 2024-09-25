#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define FOV 60
#define NUM_RAYS SCREEN_WIDTH

typedef struct {
    float x;
    float y;
    float angle;
} Player;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player player;
    int map[MAP_WIDTH][MAP_HEIGHT];
} GameState;

/* Function prototypes */
bool init_sdl(GameState *game);
void cleanup(GameState *game);
void handle_events(GameState *game, bool *quit);
void cast_rays(GameState *game);
void draw_walls(GameState *game);
void draw_floor_ceiling(GameState *game);
void draw_map(GameState *game);
void move_player(GameState *game, float dx, float dy);
void rotate_player(GameState *game, float angle);
bool load_map(GameState *game, const char *filename);

#endif /* MAIN_H */
