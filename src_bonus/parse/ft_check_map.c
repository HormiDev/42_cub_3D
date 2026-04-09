/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:34 by username          #+#    #+#             */
/*   Updated: 2026/04/09 23:29:11 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
* @brief Realiza la operación principal de la función seleccionada.
*
* @param parametro1 Descripción del primer parámetro.
* @param parametro2 Descripción del segundo parámetro.
*/

void	ft_check_map_valid_characters(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N'
					&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
			&& map[i][j] != ' ' && map[i][j] != '\t' && map[i][j] != '\n'
			&& map[i][j] != 'D')
			{
				ft_print_map(map, j, i);
				ft_dprintf(2,
					"%s%c Invalid character in map%s\n", RED, map[i][j], RESET);
				ft_close_game(1);
			}
			j++;
		}
		i++;
	}
}

/**
* @brief Cuenta el número de jugadores en el mapa.
*
* Recorre el mapa y cuenta cuántas veces aparecen los caracteres que representan
* a los jugadores ('N', 'S', 'E', 'W'). Debe haber exactamente un jugador.
*
* @param game estructura del juego que contiene el mapa.
* @return int Número de jugadores encontrados en el mapa.
*/

int	ft_check_map_count_player(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
					|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count);
}

static int	ft_check_map_dimensions(t_game *game)
{
	int	height;
	int	max_width;
	int	row_len;

	height = 0;
	max_width = 0;
	while (game->map[height])
	{
		row_len = ft_strlen(game->map[height]);
		if (row_len > 0 && game->map[height][row_len - 1] == '\n')
			row_len--;
		if (row_len > max_width)
			max_width = row_len;
		height++;
	}
	if (height > 1000 || max_width > 1000)
		return (0);
	return (1);
}

/**
* @brief Verifica si el mapa está cerrado.
*
* Comprueba si el mapa está cerrado, es decir, si todas las áreas accesibles
* están rodeadas por paredes ('1'). Si el mapa no está cerrado, se imprime un
* mensaje de error y se cierra el juego.
*
* @param game estructura del juego que contiene el mapa.
* @return int 1 si el mapa está cerrado, 0 si no lo está.
*/

void	ft_check_map(t_game *game)
{
	int	player_count;

	ft_check_map_valid_characters(game->map);
	if (!ft_check_map_dimensions(game))
	{
		ft_dprintf(2, RED "Error: Map dimensions exceed 1000x1000\n" RESET);
		ft_close_game(1);
	}
	player_count = ft_check_map_count_player(game);
	if (player_count != 1)
	{
		if (player_count < 1)
			ft_dprintf(2, "%sError: No player found in map%s", RED, RESET);
		else
		{
			ft_dprintf(2, "%sError: More than one player found in map\n", RED);
			ft_dprintf(2, RESET);
		}
		ft_close_game(1);
	}
	if (!ft_check_map_closed(game))
	{
		ft_dprintf(2, RED "Error: Map is not closed\n" RESET);
		ft_close_game(1);
	}
}
