/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 19:52:57 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/12 01:12:01 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void ft_init_t_color(t_color *color)
{
	color->rgba = &color->color;
}


void ft_mix_t_color(t_color *color, t_color *mix_color, int percent)
{
	if (percent < 0)
		return;
	if (percent > 100)
		percent = 100;
	int inv_percent = 100 - percent;
	color->rgba[0] = (color->rgba[0] * inv_percent + mix_color->rgba[0] * percent) / 100;
	color->rgba[1] = (color->rgba[1] * inv_percent + mix_color->rgba[1] * percent) / 100;
	color->rgba[2] = (color->rgba[2] * inv_percent + mix_color->rgba[2] * percent) / 100;
	color->rgba[3] = (color->rgba[3] * inv_percent + mix_color->rgba[3] * percent) / 100;
}

