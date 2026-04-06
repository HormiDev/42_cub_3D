/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:21:27 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

/**
 * @brief Imprime una celda del mapa con color si es un error.
 *
 * @param map el mapa.
 * @param pos posicion actual.
 * @param error_y fila del error (-1 si no hay).
 * @param error_x columna del error (-1 si no hay).
 */
static void	ft_print_cell(char **map, t_vector2 *pos, int error_y, int error_x)
{
	if (pos->x == error_y && pos->y == error_x)
	{
		if (ft_isprint(map[(int)pos->x][(int)pos->y]))
			ft_dprintf(2, "%s%c%s", RED, map[(int)pos->x][(int)pos->y], RESET);
		else
			ft_dprintf(2, "%s%c%s", RED, '?', RESET);
	}
	else
		ft_dprintf(1, "%c", map[(int)pos->x][(int)pos->y]);
}

/**
 * @brief Imprime un mapa completo con errores resaltados.
 *
 * @param map el mapa a imprimir.
 * @param error_x columna del error (-1 si no hay).
 * @param error_y fila del error (-1 si no hay).
 */
void	ft_print_map(char **map, int error_x, int error_y)
{
	t_vector2	pos;

	if (error_x != -1 || error_y != -1)
		ft_dprintf(2, "%sError: in %d, %d\n%s", RED, error_y + 1, error_x + 1,
			RESET);
	if (!map)
	{
		ft_dprintf(2, "Map: (null)\n");
		return ;
	}
	ft_dprintf(2, "Map:\n");
	pos.x = 0;
	while (map[(int)pos.x])
	{
		pos.y = 0;
		while (map[(int)pos.x][(int)pos.y])
		{
			ft_print_cell(map, &pos, error_y, error_x);
			pos.y++;
		}
		ft_dprintf(1, "\n");
		pos.x++;
	}
}
