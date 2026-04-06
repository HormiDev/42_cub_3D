/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_render_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:01 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/06 22:50:37 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Oculta columnas del sprite que están detrás de paredes.
 */
void	ft_mask_alien_by_depth(t_game *game, t_texture *scaled,
	int screen_x, double alien_distance)
{
	int	x;
	int	ray_index;
	int	y;

	x = 0;
	while (x < scaled->width)
	{
		ray_index = game->config.render_width - (screen_x + x) - 1;
		if (screen_x + x < 0 || screen_x + x >= game->config.render_width
			|| ray_index < 0 || ray_index >= game->config.render_width
			|| (alien_distance - 0.3) >= game->raycasts[ray_index].distance)
		{
			y = 0;
			while (y < scaled->height)
				scaled->cmx[y++][x] = 0x00FFFFFF;
		}
		x++;
	}
}

/**
 * @brief Calcula el tamaño del sprite en pantalla según la distancia.
 */
int	ft_compute_sprite_size(t_game *game, double base_size, double distance)
{
	int	size;

	size = (int)((base_size * game->config.render_height) / distance);
	if (size < MIN_ALIEN_SIZE)
		size = MIN_ALIEN_SIZE;
	return (size);
}

