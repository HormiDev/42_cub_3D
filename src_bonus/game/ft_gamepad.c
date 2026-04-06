/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/15 18:08:47 by ismherna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
** ft_apply_player0_input - Maneja input del jugador 0
** @game: estructura del juego
**
** Aplica gamepad si hay input activo, sino deja teclado.
*/
void	ft_apply_player0_input(t_game *game)
{
	if (game->gamepads[0].connected
		&& ft_gamepad_has_input(&game->gamepads[0]))
	{
		input_reset_actions(game, 0);
		ft_gamepad_apply_to_player(game, &game->gamepads[0], 0);
		game->devices[0] = INPUT_GAMEPAD;
		game->kb_player = -1;
	}
	else
	{
		if (game->devices[0] == INPUT_GAMEPAD)
			input_reset_actions(game, 0);
		game->devices[0] = INPUT_KEYBOARD;
		game->kb_player = 0;
	}
}

/*
** ft_apply_other_players - Maneja input de jugadores 1-3
** @game: estructura del juego
**
** Requieren gamepad obligatoriamente.
*/
void	ft_apply_other_players(t_game *game)
{
	int	i;

	i = 1;
	while (i < game->config.n_players && i < MAX_GAMEPADS)
	{
		if (i < game->gamepad_count && game->gamepads[i].connected)
		{
			input_reset_actions(game, i);
			ft_gamepad_apply_to_player(game, &game->gamepads[i], i);
		}
		i++;
	}
}

/*
** ft_gamepad_movement - Actualiza acciones según gamepads/teclado
** @game: estructura del juego
**
** Distribuye el input: player 0 puede usar teclado o gamepad,
** players 1-3 requieren gamepad.
*/
void	ft_gamepad_movement(t_game *game)
{
	if (game->show_menu)
	{
		if (game->gamepad_count > 0)
			ft_gamepad_menu_input_for_all(game);
		return ;
	}
	ft_apply_player0_input(game);
	ft_apply_other_players(game);
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
	else
		game->waiting_for_gamepads = 0;
}
