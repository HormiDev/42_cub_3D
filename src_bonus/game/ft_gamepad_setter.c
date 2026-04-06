/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad_setter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:22:23 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 23:13:59 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
** ft_read_gamepad_events - Lee eventos del gamepad
** @game: estructura del juego
** @i: Índice del gamepad a leer
**
** Lee todos los eventos pendientes del gamepad y los procesa.
*/
void	ft_read_gamepad_events(t_game *game, int i)
{
	struct js_event	event;
	ssize_t			bytes;

	bytes = read(game->gamepads[i].fd, &event, sizeof(event));
	while (bytes > 0)
	{
		ft_process_gamepad_event(game, &game->gamepads[i], event);
		bytes = read(game->gamepads[i].fd, &event, sizeof(event));
	}
	if (bytes == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
		ft_handle_gamepad_error(game, i);
}

/*
** ft_update_gamepad - Actualiza el estado de todos los gamepads
** @game: estructura del juego
**
** Lee eventos de todos los gamepads conectados.
*/
void	ft_update_gamepad(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_GAMEPADS)
	{
		if (!game->gamepads[i].connected || game->gamepads[i].fd == -1)
		{
			i++;
			continue ;
		}
		ft_read_gamepad_events(game, i);
		i++;
	}
}

/*
** ft_set_player_movement - Aplica movimiento del stick al jugador
** @act: Acciones del jugador a modificar
** @gp: Gamepad del que leer el input
**
** Traduce el stick izquierdo a acciones de movimiento.
*/
void	ft_set_player_movement(t_player_actions *act, t_gamepad *gp)
{
	if (gp->left_stick_y == -1)
		act->front = 1;
	else if (gp->left_stick_y == 1)
		act->back = 1;
	if (gp->left_stick_x == -1)
		act->left = 1;
	else if (gp->left_stick_x == 1)
		act->right = 1;
	if (gp->right_stick_click)
		act->run = 1;
}

/*
** ft_set_player_rotation - Aplica rotación del stick al jugador
** @act: Acciones del jugador a modificar
** @gp: Gamepad del que leer el input
**
** Traduce el stick derecho y bumpers a rotación.
*/
void	ft_set_player_rotation(t_player_actions *act, t_gamepad *gp)
{
	if (gp->right_stick_x == -1 || gp->lb)
		act->rotate_left = 1;
	else if (gp->right_stick_x == 1 || gp->rb)
		act->rotate_right = 1;
}

/*
** ft_gamepad_apply_to_player - Aplica input del gamepad al jugador
** @game: estructura del juego
** @gp: Gamepad del que leer
** @player_idx: Índice del jugador a actualizar
**
** Traduce el input del gamepad a acciones del jugador.
*/
void	ft_gamepad_apply_to_player(t_game *game, t_gamepad *gp, int player_idx)
{
	if (player_idx >= game->config.n_players)
		return ;
	ft_set_player_movement(&game->actions[player_idx], gp);
	ft_set_player_rotation(&game->actions[player_idx], gp);
	if (gp->rt_pressed)
	{
		flamethrower(game, player_idx);
		gp->rt_pressed = 0;
	}
	if (gp->a_pressed)
	{
		game->actions[player_idx].interact = 1;
		gp->a_pressed = 0;
	}
	game->devices[player_idx] = INPUT_GAMEPAD;
}
