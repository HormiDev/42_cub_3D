/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:22:54 by username          #+#    #+#             */
/*   Updated: 2026/04/10 00:30:28 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_render_3d(t_game *game)
{
	int	i;

	draw_background(game);
	i = 0;
	while (i < game->config.render_width)
	{
		draw_column(game,
			game->config.render_width - i - 1, &game->raycasts[i]);
		i++;
	}
}
