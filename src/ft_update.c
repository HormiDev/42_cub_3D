/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/07/24 18:19:18 by ide-dieg         ###   ########.fr       */
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
	ft_draw_map(game);
	return (0);
}