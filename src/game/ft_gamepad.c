/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/10 09:48:04 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"
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

static void	ft_process_gamepad_event(t_game *game, struct js_event event)
{
	if (event.type == JS_EVENT_BUTTON)
	{
		if (event.number == 0) // A
			game->gamepad.a = event.value;
		else if (event.number == 1) // B
			game->gamepad.b = event.value;
		else if (event.number == 2) // X
			game->gamepad.x = event.value;
		else if (event.number == 3) // Y
			game->gamepad.y = event.value;
		else if (event.number == 4) // LB
			game->gamepad.lb = event.value;
		else if (event.number == 5) // RB
			game->gamepad.rb = event.value;
	}
	else if (event.type == JS_EVENT_AXIS)
	{
		if (event.number == 0) // Stick izquierdo X
			game->gamepad.left_stick_x = ft_normalize_axis_value(event.value);
		else if (event.number == 1) // Stick izquierdo Y
			game->gamepad.left_stick_y = ft_normalize_axis_value(event.value);
		else if (event.number == 3) // Stick derecho X
			game->gamepad.right_stick_x = ft_normalize_axis_value(event.value);
		else if (event.number == 4) // Stick derecho Y
			game->gamepad.right_stick_y = ft_normalize_axis_value(event.value);
	}
}

void	ft_init_gamepad(t_game *game)
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

	const char *gamepad_paths[] = {
		"/dev/input/js0",
		"/dev/input/js1",
		"/dev/input/event0",
		"/dev/input/event1",
		"/dev/input/event2",
		"/dev/input/event3",
		NULL
	};
	
	int i = 0;
	while (gamepad_paths[i] && game->gamepad.fd == -1)
	{
		game->gamepad.fd = open(gamepad_paths[i], O_RDONLY | O_NONBLOCK);
		if (game->gamepad.fd != -1)
		{
			game->gamepad.connected = 1;
			ft_printf("Gamepad found at %s\n", gamepad_paths[i]);
			return;
		}
		i++;
	}
	
	// Modo sin gamepad (silencioso para WSL)
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

void	ft_update_gamepad(t_game *game)
{
	struct js_event event;
	ssize_t bytes;

	if (!game->gamepad.connected || game->gamepad.fd == -1)
		return ;

	// Leer todos los eventos disponibles sin bloquear
	while ((bytes = read(game->gamepad.fd, &event, sizeof(event))) > 0)
	{
		ft_process_gamepad_event(game, event);
	}
	
	// Si hay error de lectura que no sea EAGAIN/EWOULDBLOCK, desconectar silenciosamente
	if (bytes == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
	{
		game->gamepad.connected = 0;
		if (game->gamepad.fd != -1)
		{
			close(game->gamepad.fd);
			game->gamepad.fd = -1;
		}
	}
}

void	ft_gamepad_movement(t_game *game)
{
	// Si hay gamepad conectado, usarlo
	if (game->gamepad.connected)
	{
		game->input.front = 0;
		game->input.back = 0;
		game->input.left = 0;
		game->input.right = 0;
		
		// Movimiento con stick izquierdo
		if (game->gamepad.left_stick_y == -1) // Stick arriba (forward)
			game->input.front = 1;
		else if (game->gamepad.left_stick_y == 1) // Stick abajo (backward)
			game->input.back = 1;
		if (game->gamepad.left_stick_x == -1) // Stick izquierda
			game->input.left = 1;
		else if (game->gamepad.left_stick_x == 1) // Stick derecha
			game->input.right = 1;

		// Rotación con stick derecho o botones LB/RB
		if (game->gamepad.right_stick_x == -1 || game->gamepad.lb)
		{
			game->player.rotation.x += ROTATION_SPEED * game->delta_time;
			if (game->player.rotation.x >= 360.0)
				game->player.rotation.x -= 360.0;
		}
		else if (game->gamepad.right_stick_x == 1 || game->gamepad.rb)
		{
			game->player.rotation.x -= ROTATION_SPEED * game->delta_time;
			if (game->player.rotation.x < 0.0)
				game->player.rotation.x += 360.0;
		}
	}
}
