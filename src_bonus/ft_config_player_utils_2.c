/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_player_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:01 by username          #+#    #+#             */
/*   Updated: 2026/04/10 04:02:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Establece la rotación del jugador según el carácter de dirección.
 *
 * Esta función configura la rotación del jugador basándose en el carácter
 * que representa la dirección inicial ('N', 'S', 'E', 'W').
 *
 * @param game estructura del juego.
 * @param direction_char Carácter que representa la dirección ('N', 'S', 'E',
	'W').
 */
void	ft_set_player_spawn_rotation(t_game *game, char direction_char)
{
	if (direction_char == 'N')
		game->player->rotation.x = 90.0;
	else if (direction_char == 'S')
		game->player->rotation.x = 270.0;
	else if (direction_char == 'E')
		game->player->rotation.x = 0.0;
	else if (direction_char == 'W')
		game->player->rotation.x = 180.0;
	game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
}

/**
 * @brief Configura la posición y rotación del jugador en el mapa.
 *
 * Esta función recorre el mapa del juego para encontrar la posición del jugador
 * representada por los caracteres 'N', 'S', 'E' o 'W'. Establece la posición y
 * rotación del jugador según el carácter encontrado,
	y luego reemplaza el carácter
 * en el mapa con '0'.
 *

	* @param game estructura del juego que contiene el mapa y la información del jugador.
 */

void	ft_init_all_players(t_game *game)
{
	int	idx;

	idx = 0;
	while (idx < MAX_PLAYERS)
	{
		game->players[idx].active = 0;
		game->players[idx].alive = 1;
		game->players[idx].type = ENTITY_PLAYER;
		game->ordered_ojects[idx] = &game->players[idx];
		idx++;
	}
}

void	ft_init_player_actions(t_game *game)
{
	int	idx;

	idx = 0;
	while (idx < MAX_GAMEPADS)
	{
		game->actions[idx].flamethrower_charges = game->config.charges;
		game->actions[idx].flamethrower_ready = 1;
		game->actions[idx].flamethrower_last_time = 0;
		idx++;
	}
}

void	ft_init_flamethrower_state(t_game *game)
{
	int	idx;

	idx = 0;
	while (idx < MAX_GAMEPADS)
	{
		game->actions[idx].flamethrower_cooldown_remaining = 0;
		game->actions[idx].flamethrower_animating = 0;
		game->actions[idx].flamethrower_anim_time = 0;
		game->actions[idx].flamethrower_anim_frame = 0;
		idx++;
	}
}

int	ft_is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}
