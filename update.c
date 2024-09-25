#include "main.h"

/**
 * update_game_state - Update game logic and handle collisions
 * @game: Pointer to the GameState structure
 */
void update_game_state(GameState *game)
{
    /** Keep player angle within 0 to 2*PI */
    game->player_angle = fmodf(game->player_angle, 2 * M_PI);
    if (game->player_angle < 0)
        game->player_angle += 2 * M_PI;

    /** Collision detection */
    int map_pos_x = (int)game->player_pos.x;
    int map_pos_y = (int)game->player_pos.y;
    float move_step = 0.1f;

    float new_x = game->player_pos.x + cosf(game->player_angle) * move_step;
    float new_y = game->player_pos.y + sinf(game->player_angle) * move_step;

    if (worldMap[(int)new_x][map_pos_y] == 0)
        game->player_pos.x = new_x;
    if (worldMap[map_pos_x][(int)new_y] == 0)
        game->player_pos.y = new_y;
}

/**
 * handle_collisions - Check and resolve collisions with walls
 * @game: Pointer to the GameState structure
 * @new_x: New X position to check
 * @new_y: New Y position to check
 *
 * Return: true if collision occurred, false otherwise
 */
bool handle_collisions(GameState *game, float new_x, float new_y)
{
    int map_pos_x = (int)new_x;
    int map_pos_y = (int)new_y;

    if (map_pos_x < 0 || map_pos_x >= MAP_WIDTH ||
        map_pos_y < 0 || map_pos_y >= MAP_HEIGHT ||
        worldMap[map_pos_x][map_pos_y] != 0)
    {
        return true;
    }
    return false;
}
