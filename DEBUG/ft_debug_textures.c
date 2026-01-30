/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:06:20 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/21 19:59:54 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include "../includes/cub_3d.h"

void ft_print_map(char **map, int error_x, int error_y)
{
    int i;
	int j;

	if (error_x != -1 || error_y != -1)
		ft_dprintf(2, "%sError: in %d, %d\n%s", RED, error_y + 1, error_x + 1, RESET);
    if(!map)
    {
        ft_dprintf(2, "Map: (null)\n");
        return ;
    }
    ft_dprintf(2, "Map:\n");
	i = 0;
    while(map[i])
    {
		j = 0;
		while (map[i][j])
		{
			if (i == error_y && j == error_x)
			{
				if (ft_isprint(map[i][j]))
					ft_dprintf(2, "%s%c%s", RED, map[i][j], RESET);
				else
					ft_dprintf(2, "%s%c%s", RED, '?', RESET);
			}
			else
				ft_dprintf(1, "%c", map[i][j]);
			j++;
		}
		ft_dprintf(1, "\n");
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
        ft_print_map(game->map, -1, -1);
    else
        ft_dprintf(1, "Map: (null)\n");

    ft_dprintf(1, "\n--------------------------\n");

    debug_print_textures(game);

    ft_dprintf(1, "\n--- END DEBUG GAME STRUCT ---\n");
}
