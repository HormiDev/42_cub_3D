/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:23:15 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/09/11 17:29:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Parsea el mapa del juego.
 *
 * Esta función determina las dimensiones del mapa (ancho y alto) y crea el mapa
 * en la estructura del juego. También verifica que el mapa sea válido y lo rota
 * si es necesario.
 *
 * @param game Puntero a la estructura del juego donde se almacenará el mapa.
 * @param map_file Puntero a la estructura del archivo que contiene el mapa.
 */
void	ft_parse_map(t_game *game, t_file *map_file)
{
	int height_start_end[2];
	int width_start_end[2];

	height_start_end[0] = ft_start_line_map(map_file);
	height_start_end[1] = ft_end_line_map(map_file, height_start_end[0]);
	game->width_height[1] = height_start_end[1] - height_start_end[0] + 1;
	width_start_end[0] = ft_start_column_map(map_file, height_start_end);
	width_start_end[1] = ft_end_column_map(map_file, height_start_end);
	game->width_height[0] = width_start_end[1] - width_start_end[0] + 1;
	if (game->width_height[0] < 3 || game->width_height[1] < 3)
	{
		ft_dprintf(2, "%sError: Failed to load map: it's small\n%s", RED, RESET);
		ft_close_game(1);
	}
	ft_create_game_map(game, map_file, height_start_end, width_start_end);
	ft_check_map(game);
	ft_rotate_map_y(game);
}
