/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls_closed_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:21 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/08 01:14:06 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Verifica si una fila tiene contenido real (no solo espacios).
 *
 * Esta función auxiliar verifica si una fila contiene caracteres que no sean
 * espacios o tabulaciones.
 *
 * @param row Fila del mapa a verificar.
 * @return int 1 si tiene contenido real, 0 si solo tiene espacios.
 */
int	ft_row_has_content(char *row)
{
	int		k;

	k = 0;
	while (row[k])
	{
		if (row[k] != ' ' && row[k] != '\t')
			return (1);
		k++;
	}
	return (0);
}

/**
 * @brief Verifica si un espacio está correctamente cerrado.
 *
 * Esta función auxiliar verifica que un espacio vacío esté rodeado por
 * paredes ('1') o por otros espacios vacíos.
 *
 * @param map Mapa a verificar.
 * @param i Índice de fila del espacio.
 * @param j Índice de columna del espacio.
 * @return int 1 si está correctamente cerrado, 0 en caso contrario.
 */
int	ft_check_space_surrounded(char **map, int i, int j)
{
	if (i > 0 && map[i - 1][j] != 0 && map[i - 1][j] != '1'
		&& map[i - 1][j] != ' ' && map[i - 1][j] != 'D')
		return (ft_print_map(map, j, i - 1), 0);
	if (map[i + 1] && map[i + 1][j] != 0 && map[i + 1][j] != '1'
		&& map[i + 1][j] != ' ' && map[i + 1][j] != 'D')
		return (ft_print_map(map, j, i + 1), 0);
	if (j > 0 && map[i][j - 1] != 0 && map[i][j - 1] != '1'
		&& map[i][j - 1] != ' ' && map[i][j - 1] != 'D')
		return (ft_print_map(map, j - 1, i), 0);
	if (map[i][j + 1] != 0 && map[i][j + 1] != '1'
		&& map[i][j + 1] != ' ' && map[i][j + 1] != 'D')
		return (ft_print_map(map, j + 1, i), 0);
	return (1);
}
