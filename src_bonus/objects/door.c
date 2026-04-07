/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:08 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 22:14:11 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static t_door	*ft_create_door(int x, int y)
{
	t_door	*door;

	door = hd_calloc(1, sizeof(t_door));
	if (!door)
		return (NULL);
	door->position.x = x;
	door->position.y = y;
	door->state = DOOR_CLOSED;
	door->auto_reopen_delay = 5.0;
	door->auto_reopen_timer = -1.0;
	door->texture_index = 0;
	return (door);
}
void	ft_free_doors(t_game *game)
{
	if (game->doors)
		game->doors = NULL;
}

void	ft_init_doors(t_game *game)
{
	int		y;
	int		x;
	t_door	*door;

	game->doors = NULL;
	y = -1;
	while (++y < game->width_height[1])
	{
		x = -1;
		while (++x < game->width_height[0])
		{
			if (game->map[y][x] == 'D')
			{
				door = ft_create_door(x, y);
				if (!door)
					ft_close_game(1);
				ft_lstadd_back(&game->doors, hd_alloc(ft_lstnew(door), free));
			}
		}
	}
}

static void	ft_update_door_auto_reopen(t_game *game, t_door *door, double delta_time)
{
	if (door->state != DOOR_CLOSED)
		return ;
	if (door->auto_reopen_timer < 0.0)
		return ;
	door->auto_reopen_timer -= delta_time;
	if (door->auto_reopen_timer <= 0.0)
	{
		door->auto_reopen_timer = -1.0;
		door->state = DOOR_OPEN;
		game->map[door->position.y][door->position.x] = 'd';
	}
}

void	ft_update_doors(t_game *game)
{
	t_list	*current;
	t_door	*door;

	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		ft_update_door_auto_reopen(game, door, game->delta_time);
		current = current->next;
	}
}
