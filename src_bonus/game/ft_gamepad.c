/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/17 17:03:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub_3d_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

static int	ft_normalize_axis_value(int raw_value)
{
    if (raw_value > 16000)
        return (1);
    else if (raw_value < -16000)
        return (-1);
    return (0);
}

static void	ft_reset_single_gamepad(t_gamepad *gp)
{
    gp->connected = 0;
    gp->fd = -1;
    gp->a = 0;
    gp->b = 0;
    gp->x = 0;
    gp->y = 0;
    gp->lb = 0;
    gp->rb = 0;
    gp->left_stick_x = 0;
    gp->left_stick_y = 0;
    gp->right_stick_x = 0;
    gp->right_stick_y = 0;
    gp->right_stick_click = 0;
    gp->a_pressed = 0;
    gp->b_pressed = 0;
}

static void	ft_process_button_ab(t_gamepad *gp, struct js_event event)
{
	if (event.number == 0)
	{
		gp->a = event.value;
		if (event.value == 1)
			gp->a_pressed = 1;
	}
	else if (event.number == 1)
	{
		gp->b = event.value;
		if (event.value == 1)
			gp->b_pressed = 1;
	}
}

static void	ft_process_button_event(t_game *game, t_gamepad *gp,
	struct js_event event)
{
	(void)game;
	ft_process_button_ab(gp, event);
	if (event.number == 2)
		gp->x = event.value;
	else if (event.number == 3)
		gp->y = event.value;
	else if (event.number == 4)
		gp->lb = event.value;
	else if (event.number == 5)
		gp->rb = event.value;
	else if (event.number == 9)
		gp->right_stick_click = event.value;
}

static void	ft_process_axis_event(t_gamepad *gp, struct js_event event)
{
    if (event.number == 0)
        gp->left_stick_x = ft_normalize_axis_value(event.value);
    else if (event.number == 1)
        gp->left_stick_y = ft_normalize_axis_value(event.value);
    else if (event.number == 3)
        gp->right_stick_x = ft_normalize_axis_value(event.value);
    else if (event.number == 4)
        gp->right_stick_y = ft_normalize_axis_value(event.value);
}

static void	ft_process_gamepad_event(t_game *game, t_gamepad *gp,
	struct js_event event)
{
	if (event.type == JS_EVENT_BUTTON)
		ft_process_button_event(game, gp, event);
	else if (event.type == JS_EVENT_AXIS)
		ft_process_axis_event(gp, event);
}

static int	ft_try_open_gamepad_at(t_game *game, const char *path, int slot)
{
	int	fd;

	fd = ft_open_fd_lst(1, (char *)path, O_RDONLY | O_NONBLOCK);
	if (fd != -1)
	{
		game->gamepads[slot].fd = fd;
		game->gamepads[slot].connected = 1;
		game->gamepad_count++;
		ft_printf("Gamepad %d found at %s\n", slot + 1, path);
		return (1);
	}
	return (0);
}

static void	ft_init_gamepad_paths(t_game *game)
{
	const char	*paths[] = {"/dev/input/js0", "/dev/input/js1",
		"/dev/input/js2", "/dev/input/js3",
		"/dev/input/event0", "/dev/input/event1",
		"/dev/input/event2", "/dev/input/event3", NULL};
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

void	ft_init_gamepad(t_game *game)
{
	int	i;

	game->gamepad_count = 0;
	game->waiting_for_gamepads = 0;
	i = 0;
	while (i < MAX_GAMEPADS)
	{
		ft_reset_single_gamepad(&game->gamepads[i]);
		i++;
	}
	ft_init_gamepad_paths(game);
	if (game->gamepad_count == 0)
		ft_printf("Info: No gamepad detected (keyboard controls active)\n");
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
}

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

static void	ft_recount_gamepads(t_game *game)
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

static void	ft_handle_gamepad_error(t_game *game, int slot)
{
	if (game->gamepads[slot].fd != -1)
		close(game->gamepads[slot].fd);
	ft_reset_single_gamepad(&game->gamepads[slot]);
	ft_recount_gamepads(game);
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
}

static void	ft_read_gamepad_events(t_game *game, int i)
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

static void	ft_set_player_movement(t_player_input *pinput, t_gamepad *gp)
{
	if (gp->left_stick_y == -1)
		pinput->gp.gp_front = 1;
	else if (gp->left_stick_y == 1)
		pinput->gp.gp_back = 1;
	if (gp->left_stick_x == -1)
		pinput->gp.gp_left = 1;
	else if (gp->left_stick_x == 1)
		pinput->gp.gp_right = 1;
	if (gp->right_stick_click)
		pinput->gp.gp_run = 1;
}

static void	ft_set_player_rotation(t_player_input *pinput, t_gamepad *gp)
{
	if (gp->right_stick_x == -1 || gp->lb)
		pinput->gp.gp_rotate_left = 1;
	else if (gp->right_stick_x == 1 || gp->rb)
		pinput->gp.gp_rotate_right = 1;
}

static void	ft_reset_player_input(t_player_input *pinput)
{
	pinput->gp.gp_front = 0;
	pinput->gp.gp_back = 0;
	pinput->gp.gp_left = 0;
	pinput->gp.gp_right = 0;
	pinput->gp.gp_rotate_left = 0;
	pinput->gp.gp_rotate_right = 0;
	pinput->gp.gp_run = 0;
}

static void	ft_copy_actions_to_player(t_player_input *pinput, int player_idx)
{
	pinput->actions.front = pinput->gp.gp_front;
	pinput->actions.back = pinput->gp.gp_back;
	pinput->actions.left = pinput->gp.gp_left;
	pinput->actions.right = pinput->gp.gp_right;
	pinput->actions.rotate_left = pinput->gp.gp_rotate_left;
	pinput->actions.rotate_right = pinput->gp.gp_rotate_right;
	pinput->actions.run = pinput->gp.gp_run;
	pinput->active_device = INPUT_GAMEPAD;
	pinput->gamepad_index = player_idx;
}

static void	ft_gamepad_apply_to_player(t_game *game, t_gamepad *gp,
	int player_idx)
{
	t_player_input	*pinput;

	if (player_idx >= game->config.n_players)
		return ;
	pinput = &game->input.player_inputs[player_idx];
	ft_reset_player_input(pinput);
	ft_set_player_movement(pinput, gp);
	ft_set_player_rotation(pinput, gp);
	ft_copy_actions_to_player(pinput, player_idx);
}

static void	ft_gamepad_apply_to_input(t_game *game, t_gamepad *gp)
{
	if (gp->left_stick_y == -1)
		game->input.raw.gp.gp_front = 1;
	else if (gp->left_stick_y == 1)
		game->input.raw.gp.gp_back = 1;
	if (gp->left_stick_x == -1)
		game->input.raw.gp.gp_left = 1;
	else if (gp->left_stick_x == 1)
		game->input.raw.gp.gp_right = 1;
	if (gp->right_stick_click)
		game->input.raw.gp.gp_run = 1;
	if (gp->right_stick_x == -1 || gp->lb)
		game->input.raw.gp.gp_rotate_left = 1;
	else if (gp->right_stick_x == 1 || gp->rb)
		game->input.raw.gp.gp_rotate_right = 1;
}

static void	ft_process_menu_buttons(t_game *game, int i)
{
	if (game->gamepads[i].a_pressed)
	{
		input_handle_menu_a(game);
		game->gamepads[i].a_pressed = 0;
	}
	if (game->gamepads[i].b_pressed)
	{
		input_handle_menu_b(game);
		game->gamepads[i].b_pressed = 0;
	}
}

static void	ft_gamepad_menu_input_for_all(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_GAMEPADS)
	{
		if (game->gamepads[i].connected)
			ft_process_menu_buttons(game, i);
		i++;
	}
}

static void	ft_apply_multiplayer_gamepads(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->gamepad_count && i < MAX_GAMEPADS)
	{
		if (game->gamepads[i].connected)
			ft_gamepad_apply_to_player(game, &game->gamepads[i], i);
		i++;
	}
}

void	ft_gamepad_movement(t_game *game)
{
	input_reset_gamepad(game);
	if (game->gamepad_count == 0)
		return ;
	if (game->show_menu)
	{
		ft_gamepad_menu_input_for_all(game);
		return ;
	}
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
	else
		game->waiting_for_gamepads = 0;
	if (game->config.n_players == 1)
	{
		if (game->gamepads[0].connected)
			ft_gamepad_apply_to_input(game, &game->gamepads[0]);
	}
	else
		ft_apply_multiplayer_gamepads(game);
}
