/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_paint.c                                        :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2025/08/19 18:22:54 by username         #+#    #+#              */
/*   Updated: 2026/04/09 19:21:28 by username        ###   ########.fr        */
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
		draw_column(game, game->config.render_width - i - 1, &game->raycasts[i]);
		i++;
	}
}
