/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:06:20 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/21 00:21:57 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include "../includes/cub_3d.h"

void ft_print_map(char **map)
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


void debug_print_textures(t_game *game)
{
	const char *direction_names[4] = {"WALL_NO", "WALL_SO", "WALL_WE", "WALL_EA"};
	t_list *curr_list;
	t_texture *tex;
	int index;
	int count;
	index = 0;
	while (index < 4)
	{
		printf("Direction %s:\n", direction_names[index]);
		curr_list = game->textures[index];
		if (!curr_list)
		{
			printf("  No textures loaded.\n");
			index++;
			continue;
		}
		count = 0;
		while (curr_list)
		{
			tex = (t_texture *)curr_list->content;
			printf("  Texture %d:\n", count);
			printf("    Path: %s\n", tex->path ? tex->path : "(null)");
			printf("    Size: %dx%d\n", tex->width, tex->height);
			curr_list = curr_list->next;
			count++;
		}
		index++;
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

    if (game->map)
        ft_print_map(game->map);
    else
        ft_dprintf(1, "Map: (null)\n");

    ft_dprintf(1, "\n--------------------------\n");

    debug_print_textures(game);

    ft_dprintf(1, "\n--- END DEBUG GAME STRUCT ---\n");
}
