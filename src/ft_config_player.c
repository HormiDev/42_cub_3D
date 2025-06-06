/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/06/06 18:45:29 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void	ft_config_player(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.position.x = j + 0.5;
				game->player.position.y = i + 0.5;
				game->player.reverse_y_position = -game->player.position.y + game->width_height[1];
				if (game->map[i][j] == 'N')
					game->player.rotation.x = 90.0;
				else if (game->map[i][j] == 'S')
					game->player.rotation.x = 270.0;
				else if (game->map[i][j] == 'E')
					game->player.rotation.x = 0.0;
				else if (game->map[i][j] == 'W')
					game->player.rotation.x = 180.0;
				game->map[i][j] = '0';
			} 
			j++;
		}
		i++;
	}
}
