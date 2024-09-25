#include "main.h"

/**
 * move_player - Move the player in the specified direction
 * @game: Pointer to the GameState structure
 * @dx: Change in x-direction
 * @dy: Change in y-direction
 */
void move_player(GameState *game, float dx, float dy)
{
    float new_x = game->player.x + dx * cos(game->player.angle) - dy * sin(game->player.angle);
    float new_y = game->player.y + dx * sin(game->player.angle) + dy * cos(game->player.angle);

    /* Check for collision */
    if (game->map[(int)new_x][(int)new_y] == 0)
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

/**
 * rotate_player - Rotate the player by the specified angle
 * @game: Pointer to the GameState structure
 * @angle: Angle to rotate by (in radians)
 */
void rotate_player(GameState *game, float angle)
{
    game->player.angle += angle;
    if (game->player.angle < 0)
        game->player.angle += 2 * M_PI;
    if (game->player.angle > 2 * M_PI)
        game->player.angle -= 2 * M_PI;
}
