/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_game_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by username          #+#    #+#             */
/*   Updated: 2026/04/08 01:14:24 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
* @brief Crea el mapa del juego a partir del archivo de mapa.
*
* Esta función asigna memoria para el mapa del juego y copia las líneas del
* archivo de mapa en la estructura del juego, asegurándose de que cada línea
* termine con un carácter nulo ('\0').
*
* @param game estructura del juego donde se almacenará el mapa.
* @param map_file estructura de archivo que contiene el contenido del mapa.
* @param h_start_end Array que contiene los índices l de inicio y fin
* @param w_start_end Array que contiene los índices c de inicio y fin.
*/

void	ft_create_game_map(t_game *game, t_file *map_file,
			const int *h_start_end, const int *w_start_end)
{
	int	i;
	int	j;

	game->map = hd_calloc(game->width_height[1] + 1, sizeof(char *));
	i = 0;
	while (i < game->width_height[1])
	{
		game->map[i] = hd_calloc(game->width_height[0] + 1, sizeof(char));
		ft_strncpy(game->map[i],
			&(map_file->array_content)[h_start_end[0] + i][w_start_end[0]],
			game->width_height[0]);
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map[i][j] == '\n')
				game->map[i][j] = '\0';
			j++;
		}
		i++;
	}
}
