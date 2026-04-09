/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_config_player.c                                :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/12 13:30:01 by username         #+#    #+#              */
/*   Updated: 2026/04/09 13:14:18 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
* @brief Establece la rotación del jugador según el carácter de dirección.
*
* Esta función estática configura la rotación del jugador basándose en el carácter
* que representa la dirección inicial ('N', 'S', 'E', 'W').
*
* @param game estructura del juego.
* @param direction_char Carácter que representa la dirección ('N', 'S', 'E', 'W').
*/

static void	ft_set_player_spawn_rotation(t_game *game, char direction_char)
{
	if (direction_char == 'N')
		game->player->rotation.x = 90.0;
	else if (direction_char == 'S')
		game->player->rotation.x = 270.0;
	else if (direction_char == 'E')
		game->player->rotation.x = 0.0;
	else if (direction_char == 'W')
		game->player->rotation.x = 180.0;
	// Normalizar el ángulo por consistencia
	game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
}

/**
* @brief Configura la posición y rotación del jugador en el mapa.
*
* Esta función recorre el mapa del juego para encontrar la posición del jugador
* representada por los caracteres 'N', 'S', 'E' o 'W'. Establece la posición y
* rotación del jugador según el carácter encontrado, y luego reemplaza el carácter
* en el mapa con '0'.
*
* @param game estructura del juego que contiene el mapa y la información del jugador.
*/

void	ft_config_player(t_game *game)
{
	int	i;
	int	j;
	int	idx;
	int	found_spawn;

	i = 0;
	idx = 0;
	found_spawn = 0;
	while (idx < MAX_PLAYERS)
	{
		game->players[idx].active = 0;
		game->players[idx].alive = 1;
		game->players[idx].type = ENTITY_PLAYER;
		game->ordered_ojects[idx] = &game->players[idx];
		if (idx < MAX_GAMEPADS)
		{
			game->actions[idx].flamethrower_charges = game->config.charges;
			game->actions[idx].flamethrower_ready = 1;
			game->actions[idx].flamethrower_last_time = 0;
			game->actions[idx].flamethrower_cooldown_remaining = 0;
		}
		idx++;
	}
	game->player = &game->players[0];
	game->players[0].active = 1;
	game->players[0].alive = 1;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
					|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player->position.x = j + 0.5;
				game->player->position.y = i + 0.5;
				ft_set_player_spawn_rotation(game, game->map[i][j]);
				game->player_spawn_position = game->player->position;
				game->player_spawn_rotation = game->player->rotation.x;
				game->player_spawn_initialized = 1;
				found_spawn = 1;
				game->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (!found_spawn && game->player_spawn_initialized)
	{
		game->player->position = game->player_spawn_position;
		game->player->rotation.x = game->player_spawn_rotation;
	}
	idx = 1;
	while (idx < game->config.n_players && idx < 4)
	{
		ft_memcpy(&game->players[idx], &game->players[0], sizeof(t_player));
		game->players[idx].active = 1;
		game->players[idx].alive = 1;
		game->players[idx].type = ENTITY_PLAYER;
		game->players[idx].size = 2.0;
		game->players[idx].position.x += (idx % 2) ? 0.3 : -0.3;
		if (idx > 1)
			game->players[idx].position.y += 0.3;
		idx++;
	}
}
