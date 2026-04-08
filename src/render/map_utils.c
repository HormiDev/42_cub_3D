/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:38:41 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/08 02:40:01 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Dibuja un cuadrado en la imagen.
 *
 * @param game Estructura del juego que contiene la imagen del mapa.
 * @param x Coordenada X donde se dibujará el cuadrado.
 * @param y Coordenada Y donde se dibujará el cuadrado.
 * @param color Color del cuadrado a dibujar.
 */
void	ft_draw_sq(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_MAP_SIZE)
	{
		j = 0;
		while (j < TILE_MAP_SIZE)
		{
			ft_draw_pixel_in_img(game->img_map->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief Dibuja una cuadrícula vertical en el mapa.
 *
 * @param game estructura del juego que contiene la imagen del mapa.
 * @param color Color de las líneas de la cuadrícula.
 */
void	ft_draw_grid_vertical(t_game *game, int color)
{
	int	i;
	int	y;
	int	aux_w;
	int	aux_h;

	aux_h = game->width_height[1] * TILE_MAP_SIZE;
	aux_w = game->width_height[0] * TILE_MAP_SIZE;
	i = 0;
	while (i <= aux_w)
	{
		y = 0;
		while (y < aux_h)
		{
			ft_draw_pixel_in_img(game->img_map->img, i, y, color);
			y++;
		}
		i += TILE_MAP_SIZE;
	}
}

/**
 * @brief Dibuja una cuadrícula horizontal en el mapa.
 *
 * @param game estructura que contiene la imagen
 * @param color Color de las líneas de la cuadrícula.
 */
void	ft_draw_grid_horizontal(t_game *game, int color)
{
	int	i;
	int	x;
	int	aux_w;
	int	aux_h;

	aux_h = game->width_height[1] * TILE_MAP_SIZE;
	aux_w = game->width_height[0] * TILE_MAP_SIZE;
	i = 0;
	while (i <= aux_h)
	{
		x = 0;
		while (x < aux_w)
		{
			ft_draw_pixel_in_img(game->img_map->img, x, i, color);
			x++;
		}
		i += TILE_MAP_SIZE;
	}
}

/**
 * @brief Dibuja un tile en el minimapa.
 *
 * Esta función dibuja un tile de tamaño especificado en las coordenadas
 * con el color proporcionado. Se utiliza para representar tiles en el minimapa.
 * @param game estructura del juego que contiene la imagen del mapa.
 * @param pos Posición (x, y) donde se dibujará el tile.
 * @param size Tamaño del tile a dibujar.
 * @param color Color del tile a dibujar.
 */
void	ft_draw_minimap_tile(t_game *game, t_vector2 pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_draw_pixel_in_img(game->img_map->img, (int)pos.x + j,
				(int)pos.y + i, color);
			j++;
		}
		i++;
	}
}
