/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   input_manager.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2025/08/21 00:22:23 by username         #+#    #+#              */
/*   Updated: 2026/04/09 03:16:26 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
** input_reset_actions - Resetea todas las acciones de un jugador
** @game: estructura del juego
** @player_index: Índice del jugador (0-3)
**
** Pone a cero todas las acciones (movimiento y rotación) del jugador indicado.
*/

void	input_reset_actions(t_game *game, int player_index)
{
	if (player_index < 0 || player_index >= MAX_GAMEPADS)
		return ;
	game->actions[player_index].front = 0;
	game->actions[player_index].back = 0;
	game->actions[player_index].left = 0;
	game->actions[player_index].right = 0;
	game->actions[player_index].rotate_left = 0;
	game->actions[player_index].rotate_right = 0;
	game->actions[player_index].run = 0;
	game->actions[player_index].interact = 0;
}

/*
** input_merge_sources - Resetea acciones de jugadores con gamepad
** @game: estructura del juego
**
** Recorre todos los jugadores activos y resetea las acciones de aquellos
** que están usando gamepad. Los jugadores con teclado no se resetean.
*/

void	input_merge_sources(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->config.n_players)
	{
		if (game->devices[i] == INPUT_GAMEPAD)
			input_reset_actions(game, i);
		i++;
	}
}

/*
** input_handle_menu_a - Maneja la acción A (aceptar) en el menú
** @game: estructura del juego
**
** Cierra el menú y detiene la música si el menú está activo.
** Return: 0 si éxito, -1 si error o menú no activo
*/

int	input_handle_menu_a(t_game *game)
{
	if (!game || !game->show_menu)
		return (-1);
	if (game->game_state != GAME_PLAYING)
		ft_restart_match(game);
	audio_manager_send(game->audio_manager, "stop");
	game->show_menu = 0;
	return (0);
}

/*
** input_handle_menu_b - Maneja la acción B (cancelar/menú) en el menú
** @game: estructura del juego
**
** Si el menú está activo, cierra el juego. Si no, abre el menú.
** Return: 0 si éxito, -1 si error
*/

int	input_handle_menu_b(t_game *game)
{
	if (!game)
		return (-1);
	if (game->show_menu == 1)
		ft_close_game(0);
	else if (game->show_menu == 2)
		ft_menu_button(game);
	else
	{
		audio_manager_send(game->audio_manager, "music&sounds/menu.wav");
		game->show_menu = 1;
	}
	return (0);
}
