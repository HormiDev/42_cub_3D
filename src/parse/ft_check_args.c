/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:13:40 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/13 20:29:34 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief Verifica los argumentos de línea de comandos para el programa cub3D.
 *
 * Esta función comprueba que se proporcione exactamente un argumento, el cual debe ser
 * un archivo con extensión ".cub". Si no se cumplen las condiciones, imprime un mensaje
 * de error y retorna 0. Si los argumentos son válidos, retorna 1.
 *
 * @param argc Número de argumentos de línea de comandos.
 * @param argv Array de argumentos de línea de comandos.
 * @return 1 si los argumentos son válidos, 0 en caso contrario.
 */
int	ft_check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_dprintf(2, "%sError\n%sInvalid number of arguments.", RED, YELLOW);
		ft_dprintf(2, "Use ./cub3D <map.cub>%s\n", RESET);
		return (0);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_dprintf(2, "%sError\n%sInvalid file extension.", RED, YELLOW);
		ft_dprintf(2, "Use \"filename\".cub file extension%s\n", RESET);
		return (0);
	}
	return (1);
}

