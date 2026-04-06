/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:22:23 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 23:13:40 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
** ft_init_gamepad_paths - Inicializa los gamepads buscando en rutas
** @game: estructura del juego
**
** Busca gamepads en las rutas /dev/input/js* y /dev/input/event*.
*/
void	ft_init_gamepad_paths(t_game *game)
{
	const char	*paths[] = {"/dev/input/js0", "/dev/input/js1",
		"/dev/input/js2", "/dev/input/js3", "/dev/input/event0",
		"/dev/input/event1", "/dev/input/event2", "/dev/input/event3",
		NULL};
	int			i;
	int			slot;

	i = 0;
	slot = 0;
	while (paths[i] && slot < MAX_GAMEPADS)
	{
		if (ft_try_open_gamepad_at(game, paths[i], slot))
			slot++;
		i++;
	}
}

/*
** ft_init_gamepad - Inicializa el sistema de gamepads
** @game: estructura del juego
**
** Resetea todos los gamepads y busca dispositivos conectados.
*/
void	ft_init_gamepad(t_game *game)
{
	int	i;

	game->gamepad_count = 0;
	game->waiting_for_gamepads = 0;
	game->kb_player = 0;
	i = 0;
	while (i < MAX_GAMEPADS)
	{
		ft_reset_single_gamepad(&game->gamepads[i]);
		i++;
	}
	ft_init_gamepad_paths(game);
	if (game->gamepad_count == 0)
		ft_printf("Info: No gamepad detected "
			"(keyboard controls active)\n");
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
}

/*
** ft_free_gamepad - Libera recursos de los gamepads
** @game: estructura del juego
**
** Cierra todos los file descriptors y resetea el estado.
*/
void	ft_free_gamepad(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_GAMEPADS)
	{
		if (game->gamepads[i].fd != -1)
			close(game->gamepads[i].fd);
		ft_reset_single_gamepad(&game->gamepads[i]);
		i++;
	}
	game->gamepad_count = 0;
	game->waiting_for_gamepads = 0;
}

/*
** ft_recount_gamepads - Recuenta gamepads conectados
** @game: estructura del juego
**
** Actualiza el contador de gamepads conectados.
*/
void	ft_recount_gamepads(t_game *game)
{
	int	i;

	game->gamepad_count = 0;
	i = 0;
	while (i < MAX_GAMEPADS)
	{
		if (game->gamepads[i].connected)
			game->gamepad_count++;
		i++;
	}
}

/*
** ft_handle_gamepad_error - Maneja errores de lectura del gamepad
** @game: estructura del juego
** @slot: Slot del gamepad con error
**
** Cierra y resetea el gamepad que tuvo un error de lectura.
*/
void	ft_handle_gamepad_error(t_game *game, int slot)
{
	if (game->gamepads[slot].fd != -1)
		close(game->gamepads[slot].fd);
	ft_reset_single_gamepad(&game->gamepads[slot]);
	ft_recount_gamepads(game);
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
}
