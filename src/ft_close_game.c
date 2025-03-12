/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:25:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/12 18:54:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

int	ft_close_game(void *param)
{
	mlx_destroy_window(((t_cub_3d *)(param))->mlx, ((t_cub_3d *)(param))->win);
	mlx_destroy_display(((t_cub_3d *)(param))->mlx);
	ft_alloc_lst(0, 0);
	exit(0);
}