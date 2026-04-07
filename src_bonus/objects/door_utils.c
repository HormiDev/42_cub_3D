/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:21:55 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 11:16:52 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_is_door(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->width_height[0])
		return (0);
	if (y < 0 || y >= game->width_height[1])
		return (0);
	return (game->map[y][x] == 'D');
}

t_door	*ft_get_door_at(t_game *game, int x, int y)
{
	t_list	*current;
	t_door	*door;

	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		if (door->position.x == x && door->position.y == y)
			return (door);
		current = current->next;
	}
	return (NULL);
}

double	ft_get_door_height(t_door *door)
{
	if (!door)
		return (1.0);
	if (door->state == DOOR_OPEN)
		return (0.0);
	if (door->state == DOOR_CLOSED)
		return (1.0);
	return (1.0 - door->animation_progress);
}

static double	ft_distance_to_door(t_vector2 pos, t_door *door)
{
	double	dx;
	double	dy;

	dx = pos.x - (door->position.x + 0.5);
	dy = pos.y - (door->position.y + 0.5);
	return (ft_sqrt(dx * dx + dy * dy));
}

static void	ft_trigger_door(t_door *door, double distance)
{
	if (distance < door->trigger_distance)
	{
		if (door->state == DOOR_CLOSED)
			door->state = DOOR_OPENING;
		else if (door->state == DOOR_CLOSING)
			door->state = DOOR_OPENING;
	}
	else
	{
		if (door->state == DOOR_OPEN)
			door->state = DOOR_CLOSING;
		else if (door->state == DOOR_OPENING)
			door->state = DOOR_CLOSING;
	}
}

static int	ft_is_player_near_door(t_player *player, t_door *door)
{
	double	distance;

	if (!player || !player->active || !player->alive)
		return (0);
	distance = ft_distance_to_door(player->position, door);
	if (distance < door->trigger_distance)
		return (1);
	return (0);
}

static int	ft_any_player_near_door(t_game *game, t_door *door)
{
	int	i;

	if (ft_is_player_near_door(game->player, door))
		return (1);
	i = 0;
	while (i < game->config.n_players)
	{
		if (ft_is_player_near_door(&game->players[i], door))
			return (1);
		i++;
	}
	return (0);
}

int	ft_try_toggle_door(t_game *game)
{
	t_vector_int	door_tile;
	t_door			*door;
	double			distance;

	if (!game || !game->player)
		return (0);
	if (!ft_raycast_door_hit(game, game->player->rotation.x, 4.0, &door_tile))
		return (0);
	door = ft_get_door_at(game, door_tile.x, door_tile.y);
	if (!door)
		return (0);
	distance = ft_distance_to_door(game->player->position, door);
	if (distance > door->trigger_distance)
		return (0);
	if (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
	{
		door->state = DOOR_OPENING;
		door->auto_reopen_timer = -1.0;
	}
	else if (door->state == DOOR_OPEN || door->state == DOOR_OPENING)
	{
		door->state = DOOR_CLOSING;
		door->auto_reopen_timer = door->auto_reopen_delay;
	}
	return (1);
}

void	ft_check_door_triggers(t_game *game)
{
	t_list	*current;
	t_door	*door;
	int		near_player;

	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		near_player = ft_any_player_near_door(game, door);
		if (near_player)
			ft_trigger_door(door, 0.0);
		else
			ft_trigger_door(door, door->trigger_distance + 1.0);
		current = current->next;
	}
}
