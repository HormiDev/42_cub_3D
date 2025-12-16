/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prec_fish_eye_correction.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:49:44 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/12 19:27:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void ft_prec_fish_eye_correction(t_game *game)
{
	int i;
	double fe_corection;
	
	// tas impementar hd_alloc para liberar game->fish_eye_correction antes de reasignar
	game->fish_eye_correction = ft_alloc_lst(sizeof(double) * game->config.render_width, 4);
	i = 0;
	while (i < game->config.render_width)
	{
		fe_corection = ((double)i / (double)game->config.render_width * FOV) - (FOV / 2.0);
		if (fe_corection < 0.0)
			fe_corection = -fe_corection;
		game->fish_eye_correction[i] = ft_cos(fe_corection);
		i++;
	}
}