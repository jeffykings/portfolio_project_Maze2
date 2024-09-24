#include "main.h"

/**
 * check_collision - Check for player collisions with walls
 *
 * @new_x: New X coordinate of the player
 * @new_y: New Y coordinate of the player
 *
 * Return: 1 if collision, 0 if no collision
 */
int check_collision(float new_x, float new_y)
{
    if (map[(int)new_x][(int)new_y] > 0)
        return (1);
    return (0);
}
