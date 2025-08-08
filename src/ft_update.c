/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/08 19:47:13 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void ft_calc_delta_time(t_game *game)
{
	long current_time;
	long time_diff;

	current_time = ft_get_time();
	time_diff = ft_long_diff(game->last_frame_time, current_time);
	game->delta_time = time_diff / 1000.0;
	game->last_frame_time = current_time;
}

int ft_update(void *param)
{
	t_game 	*game = (t_game *)param;

	ft_calc_delta_time(game);
	printf("Delta Time: %f seconds\n", game->delta_time);
	ft_movement_2d(game);
	mlx_clear_window(game->mlx, game->window);
	ft_calculate_raycasts(game);
	ft_render_3d(game);
	//ft_draw_map(game);
	
	mlx_put_image_to_window(game->mlx, game->window, game->img_map->img, 0, 0);
	return (0);
}