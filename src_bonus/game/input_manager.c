/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:00:00 by ismherna          #+#    #+#             */
/*   Updated: 2026/01/07 13:22:02 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
** input_reset_actions - Resetea todas las acciones de un jugador
** @game: Puntero a la estructura del juego
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
}

/*
** input_merge_sources - Resetea acciones de jugadores con gamepad
** @game: Puntero a la estructura del juego
**
** Recorre todos los jugadores activos y resetea las acciones de aquellos
** que están usando gamepad. Los jugadores con teclado no se resetean.
*/
void	input_merge_sources(t_game *game)
{
	int	i;

	/* Resetear solo las acciones de jugadores con gamepad */
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
** @game: Puntero a la estructura del juego
**
** Cierra el menú y detiene la música si el menú está activo.
** Return: 0 si éxito, -1 si error o menú no activo
*/
int	input_handle_menu_a(t_game *game)
{
	if (!game || !game->show_menu)
		return (-1);
	audio_stop_menu(game);
	game->show_menu = 0;
	return (0);
}

/*
** input_handle_menu_b - Maneja la acción B (cancelar/menú) en el menú
** @game: Puntero a la estructura del juego
**
** Si el menú está activo, cierra el juego. Si no, abre el menú.
** Return: 0 si éxito, -1 si error
*/
int	input_handle_menu_b(t_game *game)
{
	if (!game)
		return (-1);
	if (game->show_menu)
	{
		audio_stop_menu(game);
		ft_close_game(0);
	}
	else
		game->show_menu = 1;
	return (0);
}
