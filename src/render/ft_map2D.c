/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2D.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:44:47 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Dibuja el jugador en el mapa.
 *
 * Esta función dibuja un círculo rojo en la posición del jugador en el mapa.
 * También puede dibujar líneas que representan la dirección del jugador, aunque
 * esta funcionalidad está comentada actualmente.
 *
 * @param game Contiene la información del jugador.
 */
void	ft_draw_player(t_game *game)
{
	int	px;
	int	py;

	px = (int)(game->player.position.x * TILE_MAP_SIZE);
	py = (int)(game->player.reverse_y_position * TILE_MAP_SIZE);
	ft_draw_circle(game, px, py, C_RED);
}

/**
 * @brief Dibuja un rayo en el mapa.
 *
 * El color del rayo depende del tipo de pared con la que impacta.
 *
 * @param game contiene la información del jugador y los raycasts.
 * @param ray contiene la información del rayo.
 */
void	ft_draw_raycast(t_game *game, t_raycast *ray)
{
	int	color;

	if (ray->type == WALL_NO)
		color = C_GREEN;
	else if (ray->type == WALL_SO)
		color = C_YELLOW;
	else if (ray->type == WALL_EA)
		color = C_BLUE;
	else if (ray->type == WALL_WE)
		color = C_RED;
	else
		color = C_WHITE;
	ft_draw_line_in_image(game, (t_vector2){game->player.position.x
		* TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
		(t_vector2){ray->impact.x * TILE_MAP_SIZE, (-ray->impact.y
			+ game->width_height[1]) * TILE_MAP_SIZE}, color);
}
