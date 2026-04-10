/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_player_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:01 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_set_player_spawn(t_game *game, t_vector_int pos)
{
	game->player->position.x = pos.x + 0.5;
	game->player->position.y = pos.y + 0.5;
	ft_set_player_spawn_rotation(game, game->map[pos.y][pos.x]);
	game->player_spawn_position = game->player->position;
	game->player_spawn_rotation = game->player->rotation.x;
	game->player_spawn_initialized = 1;
	game->map[pos.y][pos.x] = '0';
}

int	ft_find_player_spawn(t_game *game)
{
	t_vector_int	pos;

	pos.y = 0;
	while (game->map[pos.y])
	{
		pos.x = 0;
		while (game->map[pos.y][pos.x])
		{
			if (ft_is_spawn_char(game->map[pos.y][pos.x]))
			{
				ft_set_player_spawn(game, pos);
				return (1);
			}
			pos.x++;
		}
		pos.y++;
	}
	return (0);
}

void	ft_restore_spawn_if_not_found(t_game *game,
			int found_spawn)
{
	if (!found_spawn && game->player_spawn_initialized)
	{
		game->player->position = game->player_spawn_position;
		game->player->rotation.x = game->player_spawn_rotation;
	}
}

void	ft_setup_secondary_player(t_game *game, int idx)
{
	t_prerender_model	*tmp;

	tmp = game->players[idx].model;
	ft_memcpy(&game->players[idx], &game->players[0], sizeof(t_player));
	game->players[idx].model = tmp;
	game->players[idx].active = 1;
	game->players[idx].alive = 1;
	game->players[idx].type = ENTITY_PLAYER;
	game->players[idx].size = 2.0;
	if (idx % 2 == 0)
		game->players[idx].position.x -= 0.3;
	else
		game->players[idx].position.x += 0.3;
	if (idx > 1)
		game->players[idx].position.y += 0.3;
}

void	ft_init_multiplayer_players(t_game *game)
{
	int		idx;

	idx = 1;
	while (idx < game->config.n_players && idx < 4)
	{
		ft_setup_secondary_player(game, idx);
		idx++;
	}
}
