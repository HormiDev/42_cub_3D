/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mix_color_precalc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:52:57 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/17 18:11:06 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

unsigned char ***ft_precalc_mixcolor(void)
{
	unsigned char	***preclac;
	int				i;
	int				j;
	int				k;

	preclac = ft_alloc_lst(sizeof(unsigned char **) * 256, 3);
	i = 0;
	while (i < 256)
	{
		preclac[i] = ft_alloc_lst(sizeof(unsigned char *) * 256, 3);
		j = 0;
		while (j < 256)
		{
			preclac[i][j] = ft_alloc_lst(sizeof(unsigned char) * 101, 3);
			k = 0;
			while (k < 101)
			{
				preclac[i][j][k] = (i * (100 - k) + j * k) / 100;
				k++;
			}
			j++;
		}
		i++;
	}
	return (preclac);
}

/**
 * @brief Mezcla dos colores en un porcentaje dado.
 *
 * Esta función mezcla dos colores (color y mix_color) en un porcentaje especificado
 * (0 a 100). Si el porcentaje es menor que 0, no se realiza ninguna acción. Si es mayor
 * que 100, se ajusta al 100%.
 *
 * @param color Puntero al color base que se va a mezclar.
 * @param mix_color Puntero al color con el que se va a mezclar.
 * @param percent Porcentaje de mezcla (0 a 100).
 */
void ft_mix_color_precalc(unsigned int *color, unsigned int  *mix_color, int percent, t_game *game)
{
	unsigned char *rgba_c;
	unsigned char *rgba_m;

	rgba_c = (unsigned char *)color;
	rgba_m = (unsigned char *)mix_color;
	rgba_c[0] = game->precalc.mix_colors[rgba_c[0]][rgba_m[0]][percent];
	rgba_c[1] = game->precalc.mix_colors[rgba_c[1]][rgba_m[1]][percent];
	rgba_c[2] = game->precalc.mix_colors[rgba_c[2]][rgba_m[2]][percent];
	rgba_c[3] = game->precalc.mix_colors[rgba_c[3]][rgba_m[3]][percent];
}
