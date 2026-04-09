/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   door_utils.c                                      :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/02 16:21:55 by username         #+#    #+#              */
/*   Updated: 2026/04/09 16:38:16 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static void	ft_get_door_position(t_raycast *ray, t_vector_int *door_pos)
{
	if (ray->type == DOOR_NO)
	{
		(*door_pos).x = (int) ray->impact.x;
		(*door_pos).y = (int) ray->impact.y + 0.5;
	}
	else if (ray->type == DOOR_SO)
	{
		(*door_pos).x = (int) ray->impact.x;
		(*door_pos).y = (int) ray->impact.y - 0.5;
	}
	else if (ray->type == DOOR_WE)
	{
		(*door_pos).x = (int) ray->impact.x - 0.5;
		(*door_pos).y = (int) ray->impact.y;
	}
	else if (ray->type == DOOR_EA)
	{
		(*door_pos).x = (int) ray->impact.x + 0.5;
		(*door_pos).y = (int) ray->impact.y;
	}
}

static void	ft_get_door_position_with_wall(t_raycast *ray, t_vector_int *door_pos)
{
	if (ray->type == WALL_NO)
	{
		(*door_pos).x = (int) ray->impact.x;
		(*door_pos).y = (int) ray->impact.y - 0.5;
	}
	else if (ray->type == WALL_SO)
	{
		(*door_pos).x = (int) ray->impact.x;
		(*door_pos).y = (int) ray->impact.y + 0.5;
	}
	else if (ray->type == WALL_WE)
	{
		(*door_pos).x = (int) ray->impact.x + 0.5;
		(*door_pos).y = (int) ray->impact.y;
	}
	else if (ray->type == WALL_EA)
	{
		(*door_pos).x = (int) ray->impact.x - 0.5;
		(*door_pos).y = (int) ray->impact.y;
	}
}

static void	ft_search_door(t_game *game, t_vector_int *door_pos, t_door **door)
{
	t_door	*door_tmp;
	t_list	*current;

	current = game->doors;
	while (current)
	{
		door_tmp = (t_door *) current->content;
		if (door_tmp->position.x == door_pos->x && door_tmp->position.y == door_pos->y)
		{
			*door = door_tmp;
			return ;
		}
		current = current->next;
	}
	*door = 0;
}

static void	ft_close_door(t_game *game, t_door *door)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (game->players[i].active)
		{
			if ((int) game->players[i].position.x == door->position.x && (int) game->players[i].position.y == door->position.y)
				return ;
		}
		i++;
	}
	game->map[door->position.y][door->position.x] = 'D';
	door->state = DOOR_CLOSED;
	door->auto_reopen_timer = door->auto_reopen_delay;
	if (game->audio_manager)
		audio_manager_send(game->audio_manager, "music&sounds/puerta.wav");
}

static void	ft_open_door(t_game *game, t_door *door)
{
	game->map[door->position.y][door->position.x] = 'd';
	door->state = DOOR_OPEN;
	if (game->audio_manager)
		audio_manager_send(game->audio_manager, "music&sounds/puerta.wav");
}

int	ft_try_toggle_door(t_game *game)
{
	(void) game;
	t_door			*door;
	t_raycast		ray;
	t_vector_int	door_pos;

	ft_raycast(game, game->player->rotation.x, &ray, 1.0, game->player->position);
	if (ray.type == -1)
	{
		door_pos.x = (int) ray.impact.x;
		door_pos.y = (int) ray.impact.y;
	}
	if ((ray.type >= DOOR_NO && ray.type <= DOOR_WE))
		ft_get_door_position(&ray, &door_pos);
	if ((ray.type >= WALL_NO && ray.type <= WALL_WE))
		ft_get_door_position_with_wall(&ray, &door_pos);
	ft_search_door(game, &door_pos, &door);
	if (door)
	{
		if (door->state == DOOR_OPEN)
			ft_close_door(game, door);
		else
			ft_open_door(game, door);
	}
	return (0);
}
