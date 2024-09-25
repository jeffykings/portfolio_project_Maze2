#include "main.h"

/**
 * update_game_state - Update game logic
 * @game: Pointer to the GameState structure
 */
void update_game_state(GameState *game)
{
    /** Keep player angle within 0 to 2*PI */
    game->player_angle = fmodf(game->player_angle, 2 * M_PI);
    if (game->player_angle < 0)
        game->player_angle += 2 * M_PI;

    /** Collision detection (simple) */
    int mapX = (int)game->player_pos.x;
    int mapY = (int)game->player_pos.y;
    
    if (worldMap[mapX][mapY] != 0)
    {
        /** Move player back if inside a wall */
        game->player_pos.x = (float)((int)game->player_pos.x);
        game->player_pos.y = (float)((int)game->player_pos.y);
    }
}
