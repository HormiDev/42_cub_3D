/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:00:00 by ismherna          #+#    #+#             */
/*   Updated: 2025/12/02 00:00:00 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
 * Input manager: alterna entre teclado y gamepad.
 * Solo uno puede estar activo a la vez.
 */

static int	input_kb_has_activity(t_game *game)
{
	return (game->input.kb_front || game->input.kb_back
		|| game->input.kb_left || game->input.kb_right
		|| game->input.kb_rotate_left || game->input.kb_rotate_right
		|| game->input.kb_run);
}

static int	input_gp_has_activity(t_game *game)
{
	return (game->input.gp_front || game->input.gp_back
		|| game->input.gp_left || game->input.gp_right
		|| game->input.gp_rotate_left || game->input.gp_rotate_right
		|| game->input.gp_run);
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
	game->input.front = game->input.kb_front;
	game->input.back = game->input.kb_back;
	game->input.left = game->input.kb_left;
	game->input.right = game->input.kb_right;
	game->input.rotate_left = game->input.kb_rotate_left;
	game->input.rotate_right = game->input.kb_rotate_right;
	game->input.run = game->input.kb_run;
}

static void	input_apply_gamepad(t_game *game)
{
	game->input.front = game->input.gp_front;
	game->input.back = game->input.gp_back;
	game->input.left = game->input.gp_left;
	game->input.right = game->input.gp_right;
	game->input.rotate_left = game->input.gp_rotate_left;
	game->input.rotate_right = game->input.gp_rotate_right;
	game->input.run = game->input.gp_run;
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
	game->input.gp_front = 0;
	game->input.gp_back = 0;
	game->input.gp_left = 0;
	game->input.gp_right = 0;
	game->input.gp_rotate_left = 0;
	game->input.gp_rotate_right = 0;
	game->input.gp_run = 0;
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
		game->show_menu = 1;
	return (0);
}
