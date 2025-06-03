/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:06:20 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/06/02 14:09:36 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    ft_print_color("Floor color", game->floor_color);
    ft_print_color("Ceiling color", game->ceiling_color);

    ft_dprintf(1, "Textures:\n");
    const char *labels[] = {"NORTH", "SOUTH", "WEST", "EAST"};
    int i = 0;
    while (i < 4)
    {
        if (game->textures[i])
            ft_dprintf(1, " %s: %s\n", labels[i], game->textures[i]);
        else
            ft_dprintf(1, " %s: (null)\n", labels[i]);
        i++;
    }
    if (game->map)
    {
        ft_print_map(game->map);
    }
    else
        ft_dprintf(1, "Map: (null)\n");

    ft_dprintf(1, "\n--------------------------\n");
}
