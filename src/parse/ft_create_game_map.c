/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_game_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/17 01:28:10 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

void	ft_create_game_map(t_game *game, t_file *map_file, const int *height_start_end, const int *width_start_end)
{
	int i;
	int j;

	game->map = ft_alloc_lst(sizeof(char *) * (game->width_height[1] + 1), 4);
	i = 0;
	while (i < game->width_height[1])
	{
		game->map[i] = ft_alloc_lst(sizeof(char) * (game->width_height[0] + 1), 4);
		ft_strncpy(game->map[i], &(map_file->array_content)[height_start_end[0] + i][width_start_end[0]], game->width_height[0]);
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map[i][j] == '\n')
				game->map[i][j] = '\0';
			j++;
		}
		i++;
	}
}
