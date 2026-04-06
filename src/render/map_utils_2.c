/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:38:41 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/06 23:01:08 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Dibuja un pixel en la imagen.
 *
 *
 * @param img estructura de la imagen donde se dibujará el pixel.
 * @param x Coordenada X del pixel a dibujar.
 * @param y Coordenada Y del pixel a dibujar.
 * @param color Color del pixel a dibujar.
 */
void	ft_draw_pixel_in_img(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

/**
 * @brief Dibuja un círculo en la imagen.
 *
 * @param game estructura del juego que contiene la imagen del mapa.
 * @param cx Coordenada X del centro del círculo.
 * @param cy Coordenada Y del centro del círculo.
 * @param color Color del círculo a dibujar.
 */
void	ft_draw_circle(t_game *game, int cx, int cy, int color)
{
	int		x;
	int		y;
	int		radius;
	int		aux_radius;

	radius = TILE_MAP_SIZE / 6;
	aux_radius = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= aux_radius)
				ft_draw_pixel_in_img(game->img_map->img, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}
