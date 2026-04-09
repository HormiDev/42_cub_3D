/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_raycasts.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:15:03 by username          #+#    #+#             */
/*   Updated: 2026/04/10 00:19:34 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
* @brief Calcula los raycasts para cada columna de la ventana.
*
* Esta función recorre cada columna de la ventana y
* calcula el raycast correspondiente
* utilizando la función ft_raycast. Los resultados
* se almacenan en el array de raycasts
* del juego.
*
* @param game estructura del juego que contiene
* la información del jugador y los raycasts.
*/

void	ft_calculate_raycasts(t_game *game)
{
	int		i;
	double	angle_step;
	double	start_angle;
	double	current_angle;

	start_angle = game->player->rotation.x - (FOV / 2);
	angle_step = FOV / game->config.render_width;
	i = 0;
	while (i < game->config.render_width)
	{
		current_angle = start_angle + i * angle_step;
		ft_raycast(&(t_raycast_input){game, current_angle,
			&game->raycasts[i], MAX_RAY_SIZE, game->player->position});
		i++;
	}
}

void	ft_raycast_set_max_size(t_game *game, t_raycast *ray,
	t_raycast_ctx	*ctx)
{
	t_vector2	distance;
	double		cos_angle;
	double		sin_angle;

	(void)game;
	cos_angle = ft_cos(ctx->angle);
	sin_angle = ft_sin(ctx->angle);
	distance.x = cos_angle * ctx->max_size;
	distance.y = sin_angle * ctx->max_size;
	ft_rotate_to_cuadrant(ctx->cuadrant, &distance.x, &distance.y);
	ray->impact.x = ray->origin_position.x + distance.x;
	ray->impact.y = ray->origin_position.y + distance.y;
	ray->distance = ctx->max_size;
	ray->type = -1;
}
