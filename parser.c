#include "main.h"

/**
 * load_map - Load map data from a file
 *
 * @filename: Path to the map file
 *
 * Return: 0 on success, -1 on failure
 */
int load_map(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return (-1);

    /* Parse map file and load into array */
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            fscanf(file, "%d", &map[i][j]);
        }
    }
    fclose(file);
    return (0);
}
