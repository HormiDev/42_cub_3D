/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/07 13:21:26 by nirmata          ###   ########.fr       */
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
static int	ft_handle_player_movement(t_game *game, double move_speed, int player_index)
{
	int		moving;
	t_player_actions *actions;

	moving = 0;
	actions = &game->actions[player_index];
	
	if (actions->front && !actions->back)
	{
		if (actions->left && !actions->right)
			ft_move_direction(game, game->player->rotation.x + 45, move_speed);
		else if (actions->right && !actions->left)
			ft_move_direction(game, game->player->rotation.x - 45, move_speed);
		else
			ft_move_direction(game, game->player->rotation.x, move_speed);
		moving = 1; 
	}
	if (actions->back && !actions->front)
	{
		if (actions->left && !actions->right)
			ft_move_direction(game, game->player->rotation.x + 115, move_speed);
		else if (actions->right && !actions->left)
			ft_move_direction(game, game->player->rotation.x - 115, move_speed);
		else
			ft_move_direction(game, game->player->rotation.x + 180, move_speed);
		moving = 1; 
	}
	if (actions->left && !actions->front && !actions->back) 
    {
        ft_move_direction(game, game->player->rotation.x + 90, move_speed);
        moving = 1;
    }
    if (actions->right && !actions->front && !actions->back)
    {
        ft_move_direction(game, game->player->rotation.x - 90, move_speed);
        moving = 1;
    }
	return (moving); 
}

/**
 * @brief Maneja la rotación del jugador.
 *
 * Esta función estática procesa las entradas de rotación (izquierda, derecha)
 * y actualiza la rotación del jugador con normalización de ángulos.
 *
 * @param game Puntero a la estructura del juego.
 */
static void	ft_handle_player_rotation(t_game *game, int player_index)
{
	t_player_actions *actions;

	actions = &game->actions[player_index];
	
	if (actions->rotate_left)
	{
		game->player->rotation.x += ROTATION_SPEED * game->delta_time;
		game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
	}
	if (actions->rotate_right)
	{
		game->player->rotation.x -= ROTATION_SPEED * game->delta_time;
		game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
	}
}

int ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		input_handle_menu_b(game);
	if (game->show_menu)
	{
		if (keycode == SPACE || keycode == E)
			input_handle_menu_a(game);
		return (0);
	}
	if (keycode == M)
		ft_mouse_capture(game);
	if (game->kb_player < 0 || game->kb_player >= MAX_GAMEPADS)
		return (0);
	if (keycode == W)
		game->actions[game->kb_player].front = 1;
	else if (keycode == A)
		game->actions[game->kb_player].left = 1;
	else if (keycode == S)
		game->actions[game->kb_player].back = 1;
	else if (keycode == D)
		game->actions[game->kb_player].right = 1;
	else if (keycode == L)
		game->actions[game->kb_player].rotate_left = 1;
	else if (keycode == R)
		game->actions[game->kb_player].rotate_right = 1;
	else if (keycode == LSHIFT)
		game->actions[game->kb_player].run = 1;
	return (0);
}

int ft_key_release(int keycode, t_game *game)
{
	if (game->kb_player < 0 || game->kb_player >= MAX_GAMEPADS)
		return (0);
	if (keycode == W)
		game->actions[game->kb_player].front = 0;
	else if (keycode == A)
		game->actions[game->kb_player].left = 0;
	else if (keycode == S)
		game->actions[game->kb_player].back = 0;
	else if (keycode == D)
		game->actions[game->kb_player].right = 0;
	else if (keycode == L)
		game->actions[game->kb_player].rotate_left = 0;
	else if (keycode == R)
		game->actions[game->kb_player].rotate_right = 0;
	else if (keycode == LSHIFT)
		game->actions[game->kb_player].run = 0;
	return (0);
}

void ft_controls(t_game *game, int player_index)
{
	double	move_speed;
	int		is_moving;
	t_player_actions *actions;

	actions = &game->actions[player_index];
	
	if (actions->run)
		move_speed = RUN_SPEED;
	else
		move_speed = MOVE_SPEED;
	is_moving = ft_handle_player_movement(game, move_speed, player_index);
	ft_handle_player_rotation(game, player_index);
	if (is_moving)
		audio_play_steps(game, AUDIO_WALK);
}
