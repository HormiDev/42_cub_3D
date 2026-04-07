/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_origin_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:41 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/08 00:16:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Verifica si una línea es una directiva del mapa.
 *
 * Esta función comprueba si la línea comienza con alguna de las directivas
 * requeridas para el mapa, como "NO ", "SO ", "EA ", "WE ", "F ", o "C ".
 *
 * @param line Línea a verificar.
 * @return true Si la línea es una directiva.
 * @return false Si la línea no es una directiva.
 */
bool	is_directive_line(char *line)
{
	const char	*dirs[7] = {"NO ", "SO ", "EA ", "WE ", "F ", "C ", "D "};
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp_p(line, dirs[i], ft_strlen(dirs[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Verifica si una línea contiene solo espacios o saltos de línea.
 *
 * Esta función recorre cada carácter y devuelve true si todos los caracteres
 * son espacios, tabulaciones o saltos de línea. De lo contrario, devuelve false.
 *
 * @param line Línea a verificar.
 * @return true Si la línea contiene solo espacios o saltos de línea.
 * @return false Si la línea contiene algún otro carácter.
*/
bool	is_only_spaces(const char *line)
{
	int		j;

	j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
			return (false);
		j++;
	}
	return (true);
}
