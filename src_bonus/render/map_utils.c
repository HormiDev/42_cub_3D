/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 13:26:29 by username          #+#    #+#             */
/*   Updated: 2026/04/08 02:04:24 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
* @brief Dibuja un pixel en la imagen.
*
* Esta función dibuja un pixel en la imagen especificada 
* por las coordenadas (x, y)
* y el color proporcionado. Asegura que las coordenadas 
* estén dentro de los límites
* de la imagen antes de dibujar.
*
* @param img estructura de la imagen donde se dibujará el pixel.
* @param x Coordenada X del pixel a dibujar.
* @param y Coordenada Y del pixel a dibujar.
* @param color Color del pixel a dibujar.
*/
void	ft_draw_pixel_in_img(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < img->width
		&& y >= 0 && y < img->height)
	{
		pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *) pixel = color;
	}
}

/**
* @brief Dibuja un cuadrado en la imagen.
*
* Esta función dibuja un cuadrado de tamaño 
* TILE_MAP_SIZE en las coordenadas (x, y)
* con el color especificado. Se utiliza para representar tiles en el mapa.
*
* @param game estructura del juego que contiene la imagen del mapa.
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
* Esta función dibuja líneas verticales en el mapa a intervalos de TILE_MAP_SIZE.
* Se utiliza para crear una cuadrícula visual en el mapa.
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

int	ft_get_tile_color(char tile_char)
{
	if (tile_char == '1')
		return (C_ALIEN_GREEN);
	else if (tile_char == '0')
		return (C_ALIEN_DARK);
	return (C_BLACK);
}

/**
* @brief Dibuja una cuadrícula horizontal en el mapa.
*
* Esta función dibuja líneas horizontales 
* en el mapa a intervalos de TILE_MAP_SIZE.
* Se utiliza para crear una cuadrícula visual en el mapa.
*
* @param game estructura del juego que contiene 
* la imagen del mapa.
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
