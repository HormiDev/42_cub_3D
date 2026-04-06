/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:38:41 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/06 23:03:26 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Asigna el tipo de pared al rayo según el cuadrante y la dirección.
 *
 * Esta función determina el tipo de pared (Norte, Sur, Este, Oeste)
 * en función del cuadrante y si el rayo se mueve hacia arriba/derecha
 * o hacia abajo/izquierda.
 *
 * @param ray t_raycast donde se almacenará el tipo de pared.
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param up_right arriba/derecha (0) o hacia abajo/izquierda (1).
 */
void	ft_ray_type(t_raycast *ray, int cuadrant, int up_right)
{
	if (up_right == 0)
	{
		if (cuadrant == 0)
			ray->type = WALL_NO;
		else if (cuadrant == 1)
			ray->type = WALL_WE;
		else if (cuadrant == 2)
			ray->type = WALL_SO;
		else
			ray->type = WALL_EA;
	}
	else
	{
		if (cuadrant == 0)
			ray->type = WALL_EA;
		else if (cuadrant == 1)
			ray->type = WALL_NO;
		else if (cuadrant == 2)
			ray->type = WALL_WE;
		else
			ray->type = WALL_SO;
	}
}

/**
 * @brief Dibuja una línea en la imagen del mapa.
 *
 * Esta función dibuja una línea entre dos puntos en la imagen del
 * mapa utilizando el algoritmo de Bresenham.
 * Se utiliza para representar rayos o líneas de visión en el mapa.
 *
 * @param game estructura que contiene la imagen del mapa.
 * @param start Punto de inicio de la línea.
 * @param end Punto final de la línea.
 * @param color Color de la línea a dibujar.
 */
void	ft_draw_line_in_image(t_game *game, t_vector2 start, t_vector2 end,
		int color)
{
	t_vector2	pixel;
	int			steps;
	int			i;
	t_vector2	increment;

	steps = ft_int_max(ft_int_diff(start.x, end.x), ft_int_diff(start.y,
				end.y));
	i = 0;
	pixel.x = start.x;
	pixel.y = start.y;
	increment.x = (start.x - end.x) / steps;
	increment.y = (start.y - end.y) / steps;
	while (i <= steps)
	{
		ft_draw_pixel_in_img(game->img_map->img, (int)pixel.x, (int)pixel.y,
			color);
		pixel.x -= increment.x;
		pixel.y -= increment.y;
		i++;
	}
}

/**
 * @brief Calcula la diferencia absoluta entre dos números double.
 *
 * devuelve la diferencia absoluta entre dos números de tipo double.
 * Se utiliza para calcular distancias y diferencias en coordenadas.
 *
 * @param a Primer número.
 * @param b Segundo número.
 * @return La diferencia absoluta entre a y b.
 */
double	ft_double_diff(double a, double b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

/**
 * @brief Calcula la distancia entre dos puntos en un espacio bidimensional.
 *
 * Calcula la distancia euclidiana entre dos puntos representados por t_vector2.
 *
 * @param a Primer punto (vector).
 * @param b Segundo punto (vector).
 * @return La distancia entre los puntos a y b.
 */
double	ft_vector_distance(t_vector2 a, t_vector2 b)
{
	t_vector2	diff;

	diff.x = ft_double_diff(a.x, b.x);
	diff.y = ft_double_diff(a.y, b.y);
	return (ft_sqrt(pow(diff.x, 2) + pow(diff.y, 2)));
}
