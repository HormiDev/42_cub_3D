/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls_closed_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:23:15 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:31:54 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

static int	ft_check_row_chars(char *row, int row_num)
{
	int	i;

	i = 0;
	while (row && row[i])
	{
		if (row[i] != '1' && row[i] != ' ')
			return (ft_print_map(&row, i, row_num), 0);
		i++;
	}
	return (1);
}

static int	ft_find_last_row(t_game *game)
{
	int	last_row;
	int	j;

	last_row = 0;
	while (game->map[last_row])
		last_row++;
	last_row--;
	while (last_row >= 0 && game->map[last_row])
	{
		j = 0;
		while (game->map[last_row][j])
		{
			if (game->map[last_row][j] != ' ' && game->map[last_row][j] != '\t')
				return (last_row);
			j++;
		}
		last_row--;
	}
	return (-1);
}

/**
 * @brief Verifica si las filas superior e inferior del mapa están cerradas.
 *
 * Esta función recorre las filas superior e inferior del mapa y verifica que
 * devuelve 0. Si ambas filas están correctamente cerradas, devuelve 1.
 *
 * @param game estructura del juego que contiene el mapa.
 * @return int 1 si las filas están cerradas, 0 en caso contrario.
 */
int	ft_check_up_down(t_game *game)
{
	int		last_row;

	if (!ft_check_row_chars(game->map[0], 0))
		return (0);
	last_row = ft_find_last_row(game);
	if (last_row < 0 || !game->map[last_row])
		return (ft_print_map(game->map, 0, 0), 0);
	return (ft_check_row_chars(game->map[last_row], last_row));
}
