# include <stdio.h>
# include "../includes/cub_3d.h"

static void ft_print_color(const char *label, int color[3])
{
    ft_dprintf(1, "%s: R:%d, G:%d, B=%d\n", label, color[0], color[1], color[2]);
}

static void ft_print_map(char **map)
{
    int i;

    i = 0;
    if(!map)
    {
        ft_dprintf(1, "Map: (null)\n");
        return ;
    }
    ft_dprintf(1, "Map:\n");
    while(map[i])
    {
        ft_dprintf(1, "%s\n", map[i]);
        i++;
    }
}

void ft_debug_game(t_game *game)
{
    ft_dprintf(1, "\n--- DEBUG GAME STRUCT ---\n");
    if (!game)
    {
        ft_dprintf(1, "Error: game structure is NULL\n");
        return;
    }

    ft_dprintf(1, "Map size: width=%d, height=%d\n", game->width_height[0], game->width_height[1]);

    if (game->floor_color)
        ft_print_color("Floor color", game->floor_color);
    else
        ft_dprintf(1, "Floor color: (null)\n");

    if (game->ceiling_color)
        ft_print_color("Ceiling color", game->ceiling_color);
    else
        ft_dprintf(1, "Ceiling color: (null)\n");

    ft_dprintf(1, "Textures:\n");
    if (game->textures)
    {
        const char *labels[] = {"NORTH", "SOUTH", "WEST", "EAST"};
        for (int i = 0; i < 4; i++)
        {
            if (game->textures[i])
                ft_dprintf(1, " %s: %s\n", labels[i], game->textures[i]);
            else
                ft_dprintf(1, " %s: (null)\n", labels[i]);
        }
    }
    else
    {
        ft_dprintf(1, " Textures array is NULL or uninitialized\n");
    }

    if (game->map)
    {
        ft_print_map(game->map);
    }
    else
        ft_dprintf(1, "Map: (null)\n");

    ft_dprintf(1, "\n--------------------------\n");
}
