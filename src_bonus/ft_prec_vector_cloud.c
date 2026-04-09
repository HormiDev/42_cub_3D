/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_vector_cloud.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:17:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/09 20:13:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_prec_vector_cloud(t_game *game)
{
	int		i;
	int		j;
	double	fov_y;
	double	x;
	double angle_step = FOV / (game->config.render_width - 2);
	double start_angle = (FOV / 2);
	double current_angle;

	fov_y = FOV * ((double)game->config.render_height / (double)game->config.render_width);
	game->prec_vector_cloud = hd_calloc(game->config.render_height / 2,
			sizeof(t_vector2 *));
	game->mist_density_fc = hd_calloc(game->config.render_height / 2,
			sizeof(int));
	i = 0;
	while (i < game->config.render_height / 2)
	{
		game->prec_vector_cloud[i] = hd_calloc(game->config.render_width,
				sizeof(t_vector2));
		j = 0;
		x = 0.5 / ft_sin((fov_y / 2.0) - (i * fov_y / (double)(game->config.render_height))) * ft_cos((fov_y / 2.0) - (i * fov_y / (double)(game->config.render_height)));
		if (x < MAX_RAY_SIZE)
			game->mist_cloud_height = i;
		game->mist_density_fc[i] = -(x / MAX_RAY_SIZE * 100) + 100;
		while (j < game->config.render_width)
		{
			current_angle = start_angle - (j * angle_step);
			game->prec_vector_cloud[i][j].x = x;
			game->prec_vector_cloud[i][j].y = x / ft_format_cos(current_angle) * ft_format_sin(current_angle);
			j++;
		}
		i++;
	}
}
