/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_origin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/29 19:20:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Verifica si todas las directivas están presentes en el mapa.
 *
 * Esta función comprueba un arreglo que indica si cada directiva
 * ha sido encontrada. Si alguna directiva no se encuentra,
	imprime un mensaje de error
 * y finaliza el programa.
 *
 * @param found cada directiva fue encontrada.
 * @param dirs nombres de las directivas requeridas.
 */
static void	check_all_directives_found(bool found[6], const char *dirs[6])
{
	int	k;

	k = 0;
	while (k < 6)
	{
		if (!found[k])
		{
			ft_dprintf(2,
				RED "Error: Missing texture or color definition: %s\n" RESET,
				dirs[k]);
			ft_close_game(1);
		}
		k++;
	}
}

static void	update_found_directive(char *line, bool found[6],
		const char *dirs[6])
{
	int	k;

	k = 0;
	while (k < 6)
	{
		if (ft_strncmp_p(line, dirs[k], ft_strlen(dirs[k])) == 0)
		{
			found[k] = true;
			break ;
		}
		k++;
	}
}

static int	find_map_start_index(t_file *map_file, bool found[6],
		const char *dirs[6])
{
	int	i;

	i = 0;
	while (map_file->array_content[i])
	{
		if (!is_only_spaces(map_file->array_content[i]))
		{
			update_found_directive(map_file->array_content[i], found, dirs);
			if (!is_directive_line(map_file->array_content[i]))
				break ;
		}
		i++;
	}
	return (i);
}

int	ft_get_map_start_index(t_file *map_file)
{
	bool		found[6];
	const char	*dirs[6];
	int			i;
	int			k;

	k = 0;
	while (k < 6)
	{
		found[k] = false;
		k++;
	}
	dirs[0] = "NO ";
	dirs[1] = "SO ";
	dirs[2] = "EA ";
	dirs[3] = "WE ";
	dirs[4] = "F ";
	dirs[5] = "C ";
	i = find_map_start_index(map_file, found, dirs);
	check_all_directives_found(found, dirs);
	return (i);
}
