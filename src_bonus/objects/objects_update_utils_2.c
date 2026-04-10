/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update_utils_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:14 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 01:42:18 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_get_exclusion_bounds(t_game *game, t_vector2 center,
	int radius, int bounds[4])
{
	bounds[0] = (int) center.x - radius;
	bounds[1] = (int) center.x + radius;
	bounds[2] = (int) center.y - radius;
	bounds[3] = (int) center.y + radius;
	if (bounds[0] < 0)
		bounds[0] = 0;
	if (bounds[2] < 0)
		bounds[2] = 0;
	if (bounds[1] >= game->width_height[0])
		bounds[1] = game->width_height[0] - 1;
	if (bounds[3] >= game->width_height[1])
		bounds[3] = game->width_height[1] - 1;
}

void	ft_mark_exclusion_area(t_game *game, t_vector2 center, int radius)
{
	int	bounds[4];
	int	x;
	int	y;

	ft_get_exclusion_bounds(game, center, radius, bounds);
	y = bounds[2];
	while (y <= bounds[3])
	{
		x = bounds[0];
		while (x <= bounds[1])
		{
			game->map_transitable_aux[y][x] = '1';
			x++;
		}
		y++;
	}
}

void	ft_mark_player_areas(t_game *game)
{
	int	i;
	int	radius;

	radius = (int)(MAX_RAY_SIZE * 1.5);
	if (game->player && game->player->alive)
		ft_mark_exclusion_area(game, game->player->position, radius);
	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive)
			ft_mark_exclusion_area(game, game->players[i].position, radius);
		i++;
	}
	if (game->players[4].active)
		ft_mark_exclusion_area(game, game->players[4].position,
			(int) MAX_RAY_SIZE);
}

int	ft_aviable_positions(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map_transitable_aux[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	ft_try_set_random_position(t_vector2 *pos, int count,
	int index, t_vector_int tile)
{
	if (count != index)
		return (0);
	pos->x = tile.x + 0.5;
	pos->y = tile.y + 0.5;
	return (1);
}
