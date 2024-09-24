#include "main.h"

/**
 * handle_input - Process player input for movement and rotation
 */
void handle_input(void)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            quit_game = 1;

        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_w: move_forward(); break;
                case SDLK_s: move_backward(); break;
                case SDLK_a: rotate_left(); break;
                case SDLK_d: rotate_right(); break;
            }
        }
    }
}

/**
 * move_forward - Move the player forward
 */
void move_forward(void)
{
    if (map[(int)(player.x + player.dir_x * MOVE_SPEED)][(int)(player.y)] == 0)
        player.x += player.dir_x * MOVE_SPEED;
    if (map[(int)(player.x)][(int)(player.y + player.dir_y * MOVE_SPEED)] == 0)
        player.y += player.dir_y * MOVE_SPEED;
}

/**
 * move_backward - Move the player backward
 */
void move_backward(void)
{
    if (map[(int)(player.x - player.dir_x * MOVE_SPEED)][(int)(player.y)] == 0)
        player.x -= player.dir_x * MOVE_SPEED;
    if (map[(int)(player.x)][(int)(player.y - player.dir_y * MOVE_SPEED)] == 0)
        player.y -= player.dir_y * MOVE_SPEED;
}

/**
 * rotate_left - Rotate the player left
 */
void rotate_left(void)
{
    double old_dir_x = player.dir_x;
    player.dir_x = player.dir_x * cos(-ROT_SPEED) - player.dir_y * sin(-ROT_SPEED);
    player.dir_y = old_dir_x * sin(-ROT_SPEED) + player.dir_y * cos(-ROT_SPEED);
    double old_plane_x = player.plane_x;
    player.plane_x = player.plane_x * cos(-ROT_SPEED) - player.plane_y * sin(-ROT_SPEED);
    player.plane_y = old_plane_x * sin(-ROT_SPEED) + player.plane_y * cos(-ROT_SPEED);
}

/**
 * rotate_right - Rotate the player right
 */
void rotate_right(void)
{
    double old_dir_x = player.dir_x;
    player.dir_x = player.dir_x * cos(ROT_SPEED) - player.dir_y * sin(ROT_SPEED);
    player.dir_y = old_dir_x * sin(ROT_SPEED) + player.dir_y * cos(ROT_SPEED);
    double old_plane_x = player.plane_x;
    player.plane_x = player.plane_x * cos(ROT_SPEED) - player.plane_y * sin(ROT_SPEED);
    player.plane_y = old_plane_x * sin(ROT_SPEED) + player.plane_y * cos(ROT_SPEED);
}
