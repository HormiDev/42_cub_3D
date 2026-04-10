/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_vector_cloud.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:17:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 03:56:57 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static double	ft_calculate_ray_distance(double fov_y, int i,
		int render_height)
{
	double	vertical_angle;

	vertical_angle = (fov_y / 2.0) - (i * fov_y / (double)render_height);
	return (0.5 / ft_sin(vertical_angle) * ft_cos(vertical_angle));
}

static void	ft_fill_row_vectors(t_game *game, int row, double angle_step,
		double start_angle, double x)
{
	int		j;
	double	current_angle;

	j = 0;
	while (j < game->config.render_width)
	{
		current_angle = start_angle - (j * angle_step);
		game->prec_vector_cloud[row][j].x = x;
		game->prec_vector_cloud[row][j].y = x / ft_format_cos(current_angle)
			* ft_format_sin(current_angle);
		j++;
	}
}

static void	ft_process_row(t_game *game, int i, double angle_step,
		double start_angle, double fov_y)
{
	double	x;

	game->prec_vector_cloud[i] = hd_calloc(game->config.render_width,
			sizeof(t_vector2));
	x = ft_calculate_ray_distance(fov_y, i, game->config.render_height);
	if (x < MAX_RAY_SIZE)
		game->mist_cloud_height = i;
	game->mist_density_fc[i] = -(x / MAX_RAY_SIZE * 100) + 100;
	ft_fill_row_vectors(game, i, angle_step, start_angle, x);
}

static void	ft_fill_vector_cloud(t_game *game, double angle_step,
		double start_angle, double fov_y)
{
	int	i;

	i = 0;
	while (i < game->config.render_height / 2)
	{
		ft_process_row(game, i, angle_step, start_angle, fov_y);
		i++;
	}
}

void	ft_prec_vector_cloud(t_game *game)
{
	double	fov_y;
	double	angle_step;
	double	start_angle;

	angle_step = FOV / (game->config.render_width - 2);
	start_angle = (FOV / 2);
	fov_y = FOV * ((double)game->config.render_height
			/ (double)game->config.render_width);
	game->prec_vector_cloud = hd_calloc(game->config.render_height / 2,
			sizeof(t_vector2 *));
	game->mist_density_fc = hd_calloc(game->config.render_height / 2,
			sizeof(int));
	ft_fill_vector_cloud(game, angle_step, start_angle, fov_y);
}
