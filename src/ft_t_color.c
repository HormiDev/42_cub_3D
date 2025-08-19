/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:52:57 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/19 01:34:31 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

/**
 * @brief Inicializa la estructura t_color.
 *
 * Esta función inicializa la estructura t_color asignando un puntero a su campo rgba.
 * Se utiliza para facilitar el acceso y manipulación del color en formato RGBA.
 *
 * @param color Puntero a la estructura t_color que se va a inicializar.
 */
void ft_init_t_color(t_color *color)
{
	color->rgba = (unsigned char *)color->color;
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
void ft_mix_color(unsigned int *color, unsigned int  *mix_color, int percent)
{
	unsigned char *rgba_c;
	unsigned char *rgba_m;

	if (percent < 0)
		return;
	if (percent > 100)
		percent = 100;
	int inv_percent = 100 - percent;
	rgba_c = (unsigned char *)color;
	rgba_m = (unsigned char *)mix_color;
	rgba_c[0] = (rgba_c[0] * inv_percent + rgba_m[0] * percent) / 100;
	rgba_c[1] = (rgba_c[1] * inv_percent + rgba_m[1] * percent) / 100;
	rgba_c[2] = (rgba_c[2] * inv_percent + rgba_m[2] * percent) / 100;
	rgba_c[3] = (rgba_c[3] * inv_percent + rgba_m[3] * percent) / 100;// revisar comportamiento real de mezcla alpha
}

