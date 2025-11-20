/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_vector_cloud.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:17:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/20 00:53:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_prec_vector_cloud(t_game *game)
{
	int		i;
	int		j;
	double	fov_y;
	double	x;
	double angle_step = FOV / RENDER_WIDTH;
	double start_angle = game->player.rotation.x - (FOV / 2);
	double current_angle;

	fov_y = FOV * ((double)RENDER_HEIGHT / (double)RENDER_WIDTH);
	game->prec_vector_cloud = ft_alloc_lst(sizeof(t_vector2 *) * RENDER_HEIGHT / 2, 4);
	i = 0;
	while (i < RENDER_HEIGHT / 2)
	{
		game->prec_vector_cloud[i] = ft_alloc_lst(sizeof(t_vector2) * RENDER_WIDTH, 4);
		j = 0;
		x = ft_cos((fov_y / 2.0) - i * (fov_y / (double)(RENDER_HEIGHT / 2))) / 2.0;
		while (j < RENDER_WIDTH)
		{
			current_angle = start_angle + j * angle_step;
			game->prec_vector_cloud[i][j].x = x;
			game->prec_vector_cloud[i][j].y = x * ft_cos(current_angle) / ft_sin(current_angle);
			j++;
		}
		i++;
	}
}
