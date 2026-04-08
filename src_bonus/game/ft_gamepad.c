/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:22:23 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/08 13:46:14 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
** ft_remap_gamepads - Remapea gamepads cuando cambia n_players
** @game: estructura del juego
**
** Cierra gamepads >= n_players e intenta abrir nuevos para los slots necesarios.
*/
void	ft_remap_gamepads(t_game *game)
{
	int		i;
	int		slot;
	const char	*paths[] = {"/dev/input/js0", "/dev/input/js1",
		"/dev/input/js2", "/dev/input/js3", "/dev/input/event0",
		"/dev/input/event1", "/dev/input/event2", "/dev/input/event3",
		NULL};

	slot = game->config.n_players;
	while (slot < MAX_GAMEPADS)
	{
		if (game->gamepads[slot].fd != -1)
			close(game->gamepads[slot].fd);
		ft_reset_single_gamepad(&game->gamepads[slot]);
		slot++;
	}
	i = 0;
	slot = 0;
	while (paths[i] && slot < game->config.n_players)
	{
		if (!game->gamepads[slot].connected)
			ft_try_open_gamepad_at(game, paths[i], slot);
		if (game->gamepads[slot].connected)
			slot++;
		i++;
	}
	ft_recount_gamepads(game);
}


void	ft_gamepad_handle_system_buttons(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_GAMEPADS)
	{
		if (game->gamepads[i].connected && game->gamepads[i].menu_pressed)
		{
			if (!game->show_menu)
				input_handle_menu_b(game);
			game->gamepads[i].menu_pressed = 0;
		}
		i++;
	}
}

/*
** ft_apply_player0_input - Maneja input del jugador 0
** @game: estructura del juego
**
** Aplica gamepad si hay input activo, sino deja teclado.
*/
void	ft_apply_player0_input(t_game *game)
{
	if (game->gamepads[0].connected && ft_gamepad_has_input(&game->gamepads[0]))
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
