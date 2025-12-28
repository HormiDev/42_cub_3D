/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:00:00 by ismherna          #+#    #+#             */
/*   Updated: 2025/12/28 23:20:01 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
 * Input manager: alterna entre teclado y gamepad.
 * Solo uno puede estar activo a la vez.
 */

static int	input_kb_has_activity(t_game *game)
{
	return (game->input.raw.kb.kb_front || game->input.raw.kb.kb_back
		|| game->input.raw.kb.kb_left || game->input.raw.kb.kb_right
		|| game->input.raw.kb.kb_rotate_left || game->input.raw.kb.kb_rotate_right
		|| game->input.raw.kb.kb_run);
}

static int	input_gp_has_activity(t_game *game)
{
	return (game->input.raw.gp.gp_front || game->input.raw.gp.gp_back
		|| game->input.raw.gp.gp_left || game->input.raw.gp.gp_right
		|| game->input.raw.gp.gp_rotate_left || game->input.raw.gp.gp_rotate_right
		|| game->input.raw.gp.gp_run);
}

void	input_detect_device(t_game *game)
{
	if (game->input.active_device == INPUT_KEYBOARD)
	{
		if (input_gp_has_activity(game) && !input_kb_has_activity(game))
			game->input.active_device = INPUT_GAMEPAD;
	}
	else
	{
		if (input_kb_has_activity(game) && !input_gp_has_activity(game))
			game->input.active_device = INPUT_KEYBOARD;
	}
}

static void	input_apply_keyboard(t_game *game)
{
	game->input.actions.front = game->input.raw.kb.kb_front;
	game->input.actions.back = game->input.raw.kb.kb_back;
	game->input.actions.left = game->input.raw.kb.kb_left;
	game->input.actions.right = game->input.raw.kb.kb_right;
	game->input.actions.rotate_left = game->input.raw.kb.kb_rotate_left;
	game->input.actions.rotate_right = game->input.raw.kb.kb_rotate_right;
	game->input.actions.run = game->input.raw.kb.kb_run;
}

static void	input_apply_gamepad(t_game *game)
{
	game->input.actions.front = game->input.raw.gp.gp_front;
	game->input.actions.back = game->input.raw.gp.gp_back;
	game->input.actions.left = game->input.raw.gp.gp_left;
	game->input.actions.right = game->input.raw.gp.gp_right;
	game->input.actions.rotate_left = game->input.raw.gp.gp_rotate_left;
	game->input.actions.rotate_right = game->input.raw.gp.gp_rotate_right;
	game->input.actions.run = game->input.raw.gp.gp_run;
}

void	input_merge_sources(t_game *game)
{
	input_detect_device(game);
	if (game->input.active_device == INPUT_KEYBOARD)
		input_apply_keyboard(game);
	else
		input_apply_gamepad(game);
}

void	input_reset_gamepad(t_game *game)
{
	game->input.raw.gp.gp_front = 0;
	game->input.raw.gp.gp_back = 0;
	game->input.raw.gp.gp_left = 0;
	game->input.raw.gp.gp_right = 0;
	game->input.raw.gp.gp_rotate_left = 0;
	game->input.raw.gp.gp_rotate_right = 0;
	game->input.raw.gp.gp_run = 0;
}

int	input_handle_menu_a(t_game *game)
{
	if (!game || !game->show_menu)
		return (-1);
	audio_stop_menu(game);
	game->show_menu = 0;
	return (0);
}

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
	{
		game->show_menu = 1;
		ft_mouse_free(game);
	}
	return (0);
}
