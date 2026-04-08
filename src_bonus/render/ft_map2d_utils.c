/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2d_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:45 by username          #+#    #+#             */
/*   Updated: 2026/04/08 02:04:28 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	ft_calc_steps_and_normalize(t_vector2 *delta)
{
	t_vector_int	abs_delta;
	int				steps;

	abs_delta.x = (int)delta->x;
	abs_delta.y = (int)delta->y;
	ft_vector_int_abs(&abs_delta);
	steps = ft_vector_int_max(abs_delta);
	delta->x /= steps;
	delta->y /= steps;
	return (steps);
}

void	ft_draw_line_minimap(t_game *game, t_vector2 p1,
	t_vector2 p2, int color)
{
	t_vector2	delta;
	t_vector2	current;
	int			steps;
	int			i;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	steps = ft_calc_steps_and_normalize(&delta);
	current = p1;
	i = 0;
	while (i <= steps)
	{
		if (current.x >= 0 && current.x < game->minimap->width
			&& current.y >= 0 && current.y < game->minimap->height)
			ft_draw_pixel_in_img(game->minimap->img,
				(int)current.x, (int)current.y, color);
		current.x += delta.x;
		current.y += delta.y;
		i++;
	}
}

t_vector2	ft_world_corner_to_screen(t_game *game, double wx, double wy)
{
	t_vector2	relative;
	t_vector2	screen;
	double		cos_a;
	double		sin_a;
	int			centre;

	centre = WINDOW_HEIGHT / 10;
	relative.x = wx - game->player->position.x;
	relative.y = -(wy - game->player->position.y);
	cos_a = ft_format_cos(game->player->rotation.x - 90.0);
	sin_a = ft_format_sin(game->player->rotation.x - 90.0);
	screen.x = centre + (relative.x * cos_a - relative.y
			* sin_a) * game->minimap->height / (MAX_RAY_SIZE * 2);
	screen.y = centre + (relative.x * sin_a + relative.y
			* cos_a) * game->minimap->height / (MAX_RAY_SIZE * 2);
	return (screen);
}

void	ft_draw_tile_edges(t_game *game, int mx, int my, int color)
{
	t_vector2	corners[4];

	corners[0] = ft_world_corner_to_screen(game, mx, my);
	corners[1] = ft_world_corner_to_screen(game, mx + 1, my);
	corners[2] = ft_world_corner_to_screen(game, mx + 1, my + 1);
	corners[3] = ft_world_corner_to_screen(game, mx, my + 1);
	ft_draw_line_minimap(game, corners[0], corners[1], color);
	ft_draw_line_minimap(game, corners[1], corners[2], color);
	ft_draw_line_minimap(game, corners[2], corners[3], color);
	ft_draw_line_minimap(game, corners[3], corners[0], color);
}

void	ft_draw_minimap_tile(t_game *game, int mx, int my)
{
	int	color;

	color = ft_get_tile_color(game->map[my][mx]);
	if (game->map[my][mx] == '1')
		ft_draw_tile_edges(game, mx, my, color);
}
