/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/06 18:30:11 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Maneja el movimiento del jugador basado en las teclas presionadas.
 *
 * Esta función estática procesa las entradas de movimiento (adelante, atrás, izquierda, derecha)
 * y determina la dirección y velocidad de movimiento.
 *
 * @param game Puntero a la estructura del juego.
 * @param move_speed Velocidad de movimiento calculada.
 */
static void	ft_handle_player_movement(t_game *game, double move_speed)
{
	if (game->input.front && !game->input.back)
	{
		if (game->input.left && !game->input.right)
			ft_move_direction(game, game->player.rotation.x + 45, move_speed);
		else if (game->input.right && !game->input.left)
			ft_move_direction(game, game->player.rotation.x - 45, move_speed);
		else
			ft_move_direction(game, game->player.rotation.x, move_speed);
	}
	if (game->input.back && !game->input.front)
	{
		if (game->input.left && !game->input.right)
			ft_move_direction(game, game->player.rotation.x + 115, move_speed);
		else if (game->input.right && !game->input.left)
			ft_move_direction(game, game->player.rotation.x - 115, move_speed);
		else
			ft_move_direction(game, game->player.rotation.x + 180, move_speed);
	}
	if (game->input.left && !game->input.front && !game->input.back)
		ft_move_direction(game, game->player.rotation.x + 90, move_speed);
	if (game->input.right && !game->input.front && !game->input.back)
		ft_move_direction(game, game->player.rotation.x - 90, move_speed);
}

/**
 * @brief Maneja la rotación del jugador.
 *
 * Esta función estática procesa las entradas de rotación (izquierda, derecha)
 * y actualiza la rotación del jugador con normalización de ángulos.
 *
 * @param game Puntero a la estructura del juego.
 */
static void	ft_handle_player_rotation(t_game *game)
{
	if (game->input.rotate_left)
	{
		game->player.rotation.x += ROTATION_SPEED * game->delta_time;
		game->player.rotation.x = ft_normalize_angle(game->player.rotation.x);
	}
	if (game->input.rotate_right)
	{
		game->player.rotation.x -= ROTATION_SPEED * game->delta_time;
		game->player.rotation.x = ft_normalize_angle(game->player.rotation.x);
	}
}

int ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		if (game->show_menu)
			ft_close_game(0);
		else
			ft_close_game(0);
	}
	if (keycode == P)
	{
		if (!game->show_menu)
			game->show_menu = 1;
	}
	if (game->show_menu)
	{
		if (keycode == SPACE || keycode == 65293)
			game->show_menu = 0;
		return (0);
	}
	if (keycode == M)
        ft_toggle_mouse_capture(game);
	if (keycode == W)
		game->input.front = 1;
	else if (keycode == A)
		game->input.left = 1;
	else if (keycode == S)
		game->input.back = 1;
	else if (keycode == D)
		game->input.right = 1;
	else if (keycode == L)
		game->input.rotate_left = 1;
	else if (keycode == R)
		game->input.rotate_right = 1;
	else if (keycode == LSHIFT)
		game->input.run = 1;
	return (0);
}

int ft_key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->input.front = 0;
	else if (keycode == A)
		game->input.left = 0;
	else if (keycode == S)
		game->input.back = 0;
	else if (keycode == D)
		game->input.right = 0;
	else if (keycode == L)
		game->input.rotate_left = 0;
	else if (keycode == R)
		game->input.rotate_right = 0;
	else if (keycode == LSHIFT)
		game->input.run = 0;
	return (0);
}

void ft_controls(t_game *game)
{
	double move_speed;

	//ft_update_gamepad(game);
	//ft_gamepad_movement(game);
	if (game->input.run)
		move_speed = RUN_SPEED;
	else
		move_speed = MOVE_SPEED;
	
	ft_handle_player_movement(game, move_speed);
	ft_handle_player_rotation(game);
}
