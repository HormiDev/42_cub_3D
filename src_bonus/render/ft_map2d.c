/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:45 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/08 02:09:27 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static void	ft_draw_border_edges(t_game *game, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i < 2 || i > size - 2)
		{
			ft_draw_pixel_in_img(game->minimap->img, i, 0, C_ALIEN_GRID);
			ft_draw_pixel_in_img(game->minimap->img, i, size - 1,
				C_ALIEN_GRID);
		}
		i++;
	}
}

static void	ft_draw_border_sides(t_game *game, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (i < 2 || i > size - 2)
		{
			ft_draw_pixel_in_img(game->minimap->img, 0, i, C_ALIEN_GRID);
			ft_draw_pixel_in_img(game->minimap->img, size - 1, i,
				C_ALIEN_GRID);
		}
		i++;
	}
}

void	ft_draw_minimap_border(t_game *game)
{
	int	size;

	size = WINDOW_HEIGHT / 5;
	ft_draw_border_edges(game, size);
	ft_draw_border_sides(game, size);
}

void	ft_map2d(t_game *game)
{
	int	my;
	int	visible_range;

	ft_draw_minimap_background(game);
	visible_range = MAX_RAY_SIZE * 1.4;
	my = (int)game->player->position.y - visible_range;
	while (my <= (int)game->player->position.y + visible_range)
	{
		if (my >= 0 && my < game->width_height[1])
			ft_draw_minimap_row(game, my);
		my++;
	}
	ft_draw_minimap_border(game);
	ft_draw_player_indicator(game);
	ft_draw_objects(game);
	ft_draw_minimap_doors(game);
}
