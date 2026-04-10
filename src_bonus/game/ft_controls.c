/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:01 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_handle_system_keys(int keycode, t_game *game)
{
	if (keycode == ESC)
		input_handle_menu_b(game);
	if (game->show_menu)
	{
		if (keycode == SPACE || keycode == E)
			input_handle_menu_a(game);
		return (1);
	}
	if (keycode == M)
		ft_mouse_capture(game);
	return (0);
}

void	ft_set_key_action(int keycode, t_player_actions *actions, t_game *game,
		int player_index)
{
	if (keycode == W)
		actions->front = 1;
	else if (keycode == A)
		actions->left = 1;
	else if (keycode == S)
		actions->back = 1;
	else if (keycode == D)
		actions->right = 1;
	else if (keycode == L)
		actions->rotate_left = 1;
	else if (keycode == R)
		actions->rotate_right = 1;
	else if (keycode == LSHIFT)
		actions->run = 1;
	else if (keycode == F)
		flamethrower(game, player_index);
	else if (keycode == E)
		actions->interact = 1;
}

int	ft_key_press(int keycode, t_game *game)
{
	t_player_actions	*actions;

	if (ft_handle_system_keys(keycode, game))
		return (0);
	if (game->kb_player < 0 || game->kb_player >= MAX_GAMEPADS)
		return (0);
	actions = &game->actions[game->kb_player];
	ft_set_key_action(keycode, actions, game, game->kb_player);
	return (0);
}

int	ft_key_release(int keycode, t_game *game)
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

void	ft_controls(t_game *game, int player_index)
{
	double				move_speed;
	t_player_actions	*actions;

	actions = &game->actions[player_index];
	game->actions[player_index].walk = 0;
	if (actions->run)
		move_speed = RUN_SPEED;
	else
		move_speed = MOVE_SPEED;
	(void)ft_handle_player_movement(game, move_speed, player_index);
	ft_handle_player_rotation(game, player_index);
	if (actions->interact)
	{
		ft_try_toggle_door(game);
		actions->interact = 0;
	}
}
