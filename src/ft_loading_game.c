/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:17:36 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/12 18:57:39 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

t_cub_3d	*ft_init_cub3d(void)
{
	t_cub_3d	*cub3d;

	cub3d = ft_alloc_lst(sizeof(t_cub_3d), 4);
	cub3d->win_width = 800;
	cub3d->win_height = 600;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, cub3d->win_height, "Cub3D");
	mlx_hook(cub3d->win, 17, 0, ft_close_game, cub3d);
	return (cub3d);
}