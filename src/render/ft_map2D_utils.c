/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2D_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:33:54 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Itera la posición del rayo hacia arriba o abajo según el cuadrante.
 *
 * Esta función ajusta la posición del rayo en el eje Y
 * en el que se encuentre. Se utiliza para avanzar el rayo
 *
 * @param position_xy coordenadas X e Y del rayo.
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param iter Valor de iteración para avanzar el rayo.
 */
void	ft_ray_iter_up(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[1] += iter;
	else if (cuadrant == 1)
		position_xy[0] -= iter;
	else if (cuadrant == 2)
		position_xy[1] -= iter;
	else
		position_xy[0] += iter;
}

/**

 * @brief Itera la posición del rayo hacia la derecha o izquierda
 *
 *
 * @param position_xy Puntero a un array que contiene X e Y del rayo.
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param iter Valor de iteración para avanzar el rayo.
 */
void	ft_ray_iter_right(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[0] += iter;
	else if (cuadrant == 1)
		position_xy[1] += iter;
	else if (cuadrant == 2)
		position_xy[0] -= iter;
	else
		position_xy[1] -= iter;
}

/**
 * @brief distancia desde la posición del jugador hasta el tile del rayo.
 *
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param tile_ray_xy coordenadas X e Y del tile del rayo.
 * @param player_position Posición actual del jugador.
 * @param distance distancias calculadas.
 */
void	ft_calc_distance(int cuadrant, int *tile_ray_xy,
		t_vector2 player_position, t_vector2 *distance)
{
	if (cuadrant == 0)
	{
		distance->x = tile_ray_xy[0] + 1 - player_position.x;
		distance->y = tile_ray_xy[1] + 1 - player_position.y;
	}
	else if (cuadrant == 1)
	{
		distance->x = tile_ray_xy[1] + 1 - player_position.y;
		distance->y = player_position.x - tile_ray_xy[0];
	}
	else if (cuadrant == 2)
	{
		distance->x = player_position.x - tile_ray_xy[0];
		distance->y = player_position.y - tile_ray_xy[1];
	}
	else
	{
		distance->x = player_position.y - tile_ray_xy[1];
		distance->y = tile_ray_xy[0] + 1 - player_position.x;
	}
}

/**
 * @brief Rota las distancias del rayo al cuadrante correspondiente.
 *
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param distance_x distancia en el eje X.
 * @param distance_y distancia en el eje Y.
 */
void	ft_rotate_to_cuadrant(int cuadrant, double *distance_x,
		double *distance_y)
{
	double	aux_distance_x;

	aux_distance_x = *distance_x;
	if (cuadrant == 0)
		return ;
	else if (cuadrant == 1)
	{
		*distance_x = -(*distance_y);
		*distance_y = aux_distance_x;
	}
	else if (cuadrant == 2)
	{
		*distance_x = -(*distance_x);
		*distance_y = -(*distance_y);
	}
	else
	{
		*distance_x = *distance_y;
		*distance_y = -aux_distance_x;
	}
}

/**
 * @brief Calcula la posición del impacto del rayo.
 *
 * Esta función calcula la posición del impacto del rayo en el mapa,
	sumando las distancias
 * hasta el impacto.
 *

 * @param ray estructura t_raycast donde se almacenará el resultado.
 * @param player_position Posición actual del jugador.
 * @param distance_x Distancia en el eje X al impacto.
 * @param distance_y Distancia en el eje Y al impacto.
 */
void	ft_calc_ray_position(t_raycast *ray, t_vector2 *player_position,
		double distance_x, double distance_y)
{
	ray->impact.x = player_position->x + distance_x;
	ray->impact.y = player_position->y + distance_y;
	ray->distance = ft_vector_distance(*player_position, ray->impact);
}
