/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:01 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_config_player(t_game *game)
{
	int	found_spawn;

	ft_init_all_players(game);
	ft_init_player_actions(game);
	ft_init_flamethrower_state(game);
	game->player = &game->players[0];
	game->players[0].active = 1;
	game->players[0].alive = 1;
	found_spawn = ft_find_player_spawn(game);
	ft_restore_spawn_if_not_found(game, found_spawn);
	ft_init_multiplayer_players(game);
}
