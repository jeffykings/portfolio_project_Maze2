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
#define MAX_ENEMIES 10

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    Vector2 position;
    float angle;
    bool is_active;
} Enemy;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool is_running;
    Vector2 player_pos;
    float player_angle;
    bool show_map;
    bool is_raining;
    int current_weapon;
    Enemy enemies[MAX_ENEMIES];
    int num_enemies;
} GameState;

/** Function prototypes */
bool init_sdl(GameState *game);
void handle_events(GameState *game);
void update_game_state(GameState *game);
void render_frame(GameState *game);
void cleanup(GameState *game);
bool load_textures(void);
void unload_textures(void);
SDL_Color get_texture_color(int texture_id, int x, int y);
bool handle_collisions(GameState *game, float new_x, float new_y);
void draw_map(GameState *game);
void init_enemies(GameState *game);
void update_enemies(GameState *game);
void render_enemies(GameState *game);
void render_weapon(GameState *game);
void render_rain(GameState *game);

/** Global variables */
extern int worldMap[MAP_WIDTH][MAP_HEIGHT];

#endif /* MAIN_H */
