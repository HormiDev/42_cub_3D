/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_match.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:02:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static void	ft_reset_inputs(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_GAMEPADS)
	{
		input_reset_actions(game, i);
		i++;
	}
}

static void	ft_reset_player_spawn(t_game *game)
{
	if (game->player_spawn_initialized)
	{
		game->players[0].position = game->player_spawn_position;
		game->players[0].rotation.x = game->player_spawn_rotation;
	}
	game->player = &game->players[0];
}

static void	ft_reset_doors(t_game *game)
{
	t_list	*current;
	t_door	*door;

	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		door->state = DOOR_OPEN;
		door->auto_reopen_timer = -1.0;
		game->map[door->position.y][door->position.x] = 'd';
		current = current->next;
	}
}

void	ft_restart_match(t_game *game)
{
	if (!game)
		return ;
	ft_init_timer(game);
	ft_reset_inputs(game);
	ft_config_player(game);
	ft_reset_player_spawn(game);
	ft_config_alien(game);
	ft_reset_doors(game);
}
