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

static void	ft_process_button_event(t_game *game, struct js_event event)
{
	if (event.number == 0)
	{
		game->gamepad.a = event.value;
		if (event.value == 1)
			game->gamepad.a_pressed = 1;
	}
	else if (event.number == 1)
	{
		game->gamepad.b = event.value;
		if (event.value == 1)
			game->gamepad.b_pressed = 1;
	}
	else if (event.number == 2)
		game->gamepad.x = event.value;
	else if (event.number == 3)
		game->gamepad.y = event.value;
	else if (event.number == 4)
		game->gamepad.lb = event.value;
	else if (event.number == 5)
		game->gamepad.rb = event.value;
	else if (event.number == 9)
		game->gamepad.right_stick_click = event.value;
}

static void	ft_process_axis_event(t_game *game, struct js_event event)
{
	if (event.number == 0)
		game->gamepad.left_stick_x = ft_normalize_axis_value(event.value);
	else if (event.number == 1)
		game->gamepad.left_stick_y = ft_normalize_axis_value(event.value);
	else if (event.number == 3)
		game->gamepad.right_stick_x = ft_normalize_axis_value(event.value);
	else if (event.number == 4)
		game->gamepad.right_stick_y = ft_normalize_axis_value(event.value);
}

static void	ft_process_gamepad_event(t_game *game, struct js_event event)
{
	if (event.type == JS_EVENT_BUTTON)
		ft_process_button_event(game, event);
	else if (event.type == JS_EVENT_AXIS)
		ft_process_axis_event(game, event);
}

static void	ft_reset_gamepad_state(t_game *game)
{
	game->gamepad.connected = 0;
	game->gamepad.fd = -1;
	game->gamepad.a = 0;
	game->gamepad.b = 0;
	game->gamepad.x = 0;
	game->gamepad.y = 0;
	game->gamepad.lb = 0;
	game->gamepad.rb = 0;
	game->gamepad.left_stick_x = 0;
	game->gamepad.left_stick_y = 0;
	game->gamepad.right_stick_x = 0;
	game->gamepad.right_stick_y = 0;
	game->gamepad.right_stick_click = 0;
	game->gamepad.a_pressed = 0;
	game->gamepad.b_pressed = 0;
}

static int	ft_try_open_gamepad(t_game *game, const char *path)
{
	game->gamepad.fd = open(path, O_RDONLY | O_NONBLOCK);
	if (game->gamepad.fd != -1)
	{
		game->gamepad.connected = 1;
		ft_printf("Gamepad found at %s\n", path);
		return (1);
	}
	return (0);
}

void	ft_init_gamepad(t_game *game)
{
	const char	*paths[7];
	int			i;

	ft_reset_gamepad_state(game);
	paths[0] = "/dev/input/js0";
	paths[1] = "/dev/input/js1";
	paths[2] = "/dev/input/event0";
	paths[3] = "/dev/input/event1";
	paths[4] = "/dev/input/event2";
	paths[5] = "/dev/input/event3";
	paths[6] = NULL;
	i = 0;
	while (paths[i])
	{
		if (ft_try_open_gamepad(game, paths[i]))
			return ;
		i++;
	}
	ft_printf("Info: No gamepad detected (keyboard controls active)\n");
}

void	ft_free_gamepad(t_game *game)
{
	if (game->gamepad.fd != -1)
	{
		close(game->gamepad.fd);
		game->gamepad.fd = -1;
	}
	game->gamepad.connected = 0;
}

static void	ft_handle_gamepad_error(t_game *game)
{
	game->gamepad.connected = 0;
	if (game->gamepad.fd != -1)
	{
		close(game->gamepad.fd);
		game->gamepad.fd = -1;
	}
}

void	ft_update_gamepad(t_game *game)
{
	struct js_event	event;
	ssize_t			bytes;

	if (!game->gamepad.connected || game->gamepad.fd == -1)
		return ;
	bytes = read(game->gamepad.fd, &event, sizeof(event));
	while (bytes > 0)
	{
		ft_process_gamepad_event(game, event);
		bytes = read(game->gamepad.fd, &event, sizeof(event));
	}
	if (bytes == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
		ft_handle_gamepad_error(game);
}

static void	ft_gamepad_move_input(t_game *game)
{
	if (game->gamepad.left_stick_y == -1)
		game->input.raw.gp.gp_front = 1;
	else if (game->gamepad.left_stick_y == 1)
		game->input.raw.gp.gp_back = 1;
	if (game->gamepad.left_stick_x == -1)
		game->input.raw.gp.gp_left = 1;
	else if (game->gamepad.left_stick_x == 1)
		game->input.raw.gp.gp_right = 1;
	if (game->gamepad.right_stick_click)
		game->input.raw.gp.gp_run = 1;
}

static void	ft_gamepad_rotation(t_game *game)
{
	if (game->gamepad.right_stick_x == -1 || game->gamepad.lb)
		game->input.raw.gp.gp_rotate_left = 1;
	else if (game->gamepad.right_stick_x == 1 || game->gamepad.rb)
		game->input.raw.gp.gp_rotate_right = 1;
}

static void	ft_gamepad_menu_input(t_game *game)
{
	if (game->gamepad.a_pressed)
	{
		input_handle_menu_a(game);
		game->gamepad.a_pressed = 0;
	}
	if (game->gamepad.b_pressed)
	{
		input_handle_menu_b(game);
		game->gamepad.b_pressed = 0;
	}
}

void	ft_gamepad_movement(t_game *game)
{
	input_reset_gamepad(game);
	if (!game->gamepad.connected)
		return ;
	if (game->show_menu)
	{
		ft_gamepad_menu_input(game);
		return ;
	}
	if (game->gamepad.b_pressed)
	{
		input_handle_menu_b(game);
		game->gamepad.b_pressed = 0;
	}
	ft_gamepad_move_input(game);
	ft_gamepad_rotation(game);
}
