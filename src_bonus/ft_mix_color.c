/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mix_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 22:18:57 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/14 01:06:31 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

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
void ft_mix_color(unsigned int *color, unsigned int  *mix_color, int percent)
{
	unsigned char *rgba_c;
	unsigned char *rgba_m;

	int inv_percent = 100 - percent;
	rgba_c = (unsigned char *)color;
	rgba_m = (unsigned char *)mix_color;
	rgba_c[0] = (rgba_c[0] * inv_percent + rgba_m[0] * percent) / 100;
	rgba_c[1] = (rgba_c[1] * inv_percent + rgba_m[1] * percent) / 100;
	rgba_c[2] = (rgba_c[2] * inv_percent + rgba_m[2] * percent) / 100;
	rgba_c[3] = (rgba_c[3] * inv_percent + rgba_m[3] * percent) / 100;// revisar comportamiento real de mezcla alpha
}

/**
 * @brief Mezcla dos colores en un nivel de mezcla dado (0-255).
 *
 * Esta función mezcla dos colores (color y mix_color) en un nivel de mezcla especificado
 * (0 a 255). Si el nivel de mezcla es menor que 0, no se realiza ninguna acción. Si es mayor
 * que 255, se ajusta al 255.
 *
 * @param color Puntero al color base que se va a mezclar.
 * @param mix_color Puntero al color con el que se va a mezclar.
 * @param mix Nivel de mezcla (0 a 255).
 */
void ft_mix_color_alpha(unsigned int *color, unsigned int  *mix_color, int mix)
{
	unsigned char *rgba_c;
	unsigned char *rgba_m;

	int inv_mix = 255 - mix;
	rgba_c = (unsigned char *)color;
	rgba_m = (unsigned char *)mix_color;
	rgba_c[0] = (rgba_c[0] * inv_mix + rgba_m[0] * mix) / 255;
	rgba_c[1] = (rgba_c[1] * inv_mix + rgba_m[1] * mix) / 255;
	rgba_c[2] = (rgba_c[2] * inv_mix + rgba_m[2] * mix) / 255;
	rgba_c[3] = (rgba_c[3] * inv_mix + rgba_m[3] * mix) / 255;
}
