/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/07 19:12:26 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

int ft_update(void *param)
{
	t_game *game = (t_game *)param;
	
	ft_movement_2d(game);
	mlx_clear_window(game->mlx, game->window);
	ft_calculate_raycasts(game);
	ft_render_3d(game);
	//ft_draw_map(game);
	
	mlx_put_image_to_window(game->mlx, game->window, game->img_map->img, 0, 0);
	return (0);
}