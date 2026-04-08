/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2d_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:45 by username          #+#    #+#             */
/*   Updated: 2026/04/08 02:11:59 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_draw_minimap_row(t_game *game, int my)
{
	int	mx;
	int	visible_range;

	visible_range = MAX_RAY_SIZE * 1.4;
	mx = (int)game->player->position.x - visible_range;
	while (mx <= (int)game->player->position.x + visible_range)
	{
		if (mx >= 0 && mx < game->width_height[0]
			&& my >= 0 && my < game->width_height[1])
			ft_draw_minimap_tile(game, mx, my);
		mx++;
	}
}

static void	ft_draw_player_circle(t_game *game, int center_x, int center_y)
{
	t_vector_int	p;
	t_vector_int	d;

	p.y = center_y - 4;
	while (p.y <= center_y + 4)
	{
		p.x = center_x - 4;
		while (p.x <= center_x + 4)
		{
			d.x = p.x - center_x;
			d.y = p.y - center_y;
			if (d.x * d.x + d.y * d.y <= 16)
				ft_draw_pixel_in_img(game->minimap->img, p.x, p.y,
					C_ALIEN_PLAYER);
			p.x++;
		}
		p.y++;
	}
}

void	ft_draw_player_indicator(t_game *game)
{
	int			center;
	t_vector2	line_end;

	center = WINDOW_HEIGHT / 10;
	ft_draw_player_circle(game, center, center);
	line_end.x = center;
	line_end.y = center - 10;
	ft_draw_line_minimap(game, (t_vector2){center, center}, line_end,
		C_ALIEN_PLAYER);
}

void	ft_draw_minimap_background(t_game *game)
{
	t_vector_int	p;
	int				size;

	size = WINDOW_HEIGHT / 5;
	p.y = 0;
	while (p.y < size)
	{
		p.x = 0;
		while (p.x < size)
		{
			ft_draw_pixel_in_img(game->minimap->img, p.x, p.y,
				C_ALIEN_DARK);
			p.x++;
		}
		p.y++;
	}
}
