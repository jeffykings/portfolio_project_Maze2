#ifndef MAIN_H
#define MAIN_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Screen dimensions */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

/* Player struct */
typedef struct Player
{
    float x, y;
    float dir_x, dir_y;
    float plane_x, plane_y;
} Player;

/* Function prototypes */
int init_sdl(void);
void cleanup_sdl(void);
void handle_input(void);
void render_walls(void);
int load_map(const char *filename);
int load_textures(void);
void cleanup_textures(void);
int check_collision(float new_x, float new_y);
void move_forward(void);
void move_backward(void);
void rotate_left(void);
void rotate_right(void);

/* External declarations */
extern SDL_Window *window;
extern SDL_Renderer *renderer;
extern int quit_game;
extern int map[MAP_WIDTH][MAP_HEIGHT];
extern Player player;
extern SDL_Texture *wall_textures[4];

#endif /* MAIN_H */
