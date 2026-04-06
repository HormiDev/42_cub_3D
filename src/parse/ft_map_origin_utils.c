/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_origin_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:22:11 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

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
	int			i;
	const char	*dirs[6] = {"NO ", "SO ", "EA ", "WE ", "F ", "C "};

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp_p(line, dirs[i], ft_strlen(dirs[i])) == 0)
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Verifica si una línea contiene solo espacios,
	tabulaciones o saltos de línea.
 *
 * son espacios, tabulaciones o saltos de línea. De lo contrario,
	devuelve false.
 * @param line Línea a verificar.
 * @return true Si la línea contiene solo espacios,
	tabulaciones o saltos de línea.
 * @return false Si la línea contiene algún otro carácter.
 */
bool	is_only_spaces(const char *line)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
			return (false);
		j++;
	}
	return (true);
}
