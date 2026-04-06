/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/15 18:08:47 by ismherna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
** ft_process_axis_event - Procesa eventos de ejes del gamepad
** @gp: Puntero al gamepad
** @event: Evento de joystick recibido
**
** Actualiza los valores de los sticks analógicos normalizados.
*/
void	ft_process_axis_event(t_gamepad *gp, struct js_event event)
{
	int	new_rt;

	if (event.number == 0)
		gp->left_stick_x = ft_normalize_axis_value(event.value);
	else if (event.number == 1)
		gp->left_stick_y = ft_normalize_axis_value(event.value);
	else if (event.number == 3)
		gp->right_stick_x = ft_normalize_axis_value(event.value);
	else if (event.number == 4)
		gp->right_stick_y = ft_normalize_axis_value(event.value);
	else if (event.number == 5)
	{
		new_rt = (event.value > 16000);
		if (new_rt && !gp->rt)
			gp->rt_pressed = 1;
		gp->rt = new_rt;
	}
}

/*
** ft_process_gamepad_event - Distribuye eventos del gamepad
** @game: estructura del juego
** @gp: Puntero al gamepad
** @event: Evento de joystick recibido
**
** Enruta el evento según su tipo (botón o eje).
*/
void	ft_process_gamepad_event(t_game *game, t_gamepad *gp,
	struct js_event event)
{
	unsigned char	type;

	type = event.type & ~JS_EVENT_INIT;
	if (type == JS_EVENT_BUTTON)
		ft_process_button_event(game, gp, event);
	else if (type == JS_EVENT_AXIS)
		ft_process_axis_event(gp, event);
}

/*
** ft_process_menu_buttons - Procesa botones A/B en el menú
** @game: estructura del juego
** @i: Índice del gamepad
**
** Maneja las acciones de aceptar (A) y cancelar (B) en el menú.
*/
void	ft_process_menu_buttons(t_game *game, int i)
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

/*
** ft_gamepad_menu_input_for_all - Procesa input de todos los gamepads
** @game: estructura del juego
**
** Revisa todos los gamepads conectados y procesa sus botones de menú.
*/
void	ft_gamepad_menu_input_for_all(t_game *game)
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

/*
** ft_try_open_gamepad_at - Intenta abrir un gamepad en una ruta
** @game: estructura del juego
** @path: Ruta del dispositivo a abrir
** @slot: Slot donde guardar el gamepad (0-3)
**
** Return: 1 si se abrió correctamente, 0 si falló
*/
int	ft_try_open_gamepad_at(t_game *game, const char *path, int slot)
{
	int	fd;

	fd = hd_open(path, O_RDONLY | O_NONBLOCK);
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