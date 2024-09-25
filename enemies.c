#include "main.h"

/**
 * init_enemies - Initialize enemies in the game
 * @game: Pointer to the GameState structure
 */
void init_enemies(GameState *game)
{
    game->num_enemies = 5; /** Adjust as needed */
    for (int i = 0; i < game->num_enemies; i++)
    {
        game->enemies[i].position.x = rand() % MAP_WIDTH;
        game->enemies[i].position.y = rand() % MAP_HEIGHT;
        game->enemies[i].angle = (float)(rand() % 360) * M_PI / 180.0f;
        game->enemies[i].is_active = true;
    }
}

/**
 * update_enemies - Update enemy positions and states
 * @game: Pointer to the GameState structure
 */
void update_enemies(GameState *game)
{
    for (int i = 0; i < game->num_enemies; i++)
    {
        if (game->enemies[i].is_active)
        {
            /** Simple AI: move randomly */
            game->enemies[i].angle += (float)(rand() % 100 - 50) / 1000.0f;
            float move_x = cosf(game->enemies[i].angle) * 0.05f;
            float move_y = sinf(game->enemies[i].angle) * 0.05f;

            /** Check for collisions */
            if (!handle_collisions(game, game->enemies[i].position.x + move_x, game->enemies[i].position.y))
                game->enemies[i].position.x += move_x;
            if (!handle_collisions(game, game->enemies[i].position.x, game->enemies[i].position.y + move_y))
                game->enemies[i].position.y += move_y;
        }
    }
}
