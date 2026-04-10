/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pre_vector_cloud_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:17:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

double	ft_calculate_ray_distance(double fov_y, int i,
		int render_height)
{
	double	vertical_angle;

	vertical_angle = (fov_y / 2.0) - (i * fov_y / (double)render_height);
	return (0.5 / ft_sin(vertical_angle) * ft_cos(vertical_angle));
}
