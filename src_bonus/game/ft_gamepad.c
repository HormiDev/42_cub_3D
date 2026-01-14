/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gamepad.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/07 13:21:45 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub_3d_bonus.h"
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

/*
** ft_normalize_axis_value - Normaliza el valor del eje del gamepad
** @raw_value: Valor crudo del eje (-32768 a 32767)
**
** Convierte valores analógicos en digitales: 1, -1 o 0.
** Return: 1 si > 16000, -1 si < -16000, 0 en otro caso
*/
static int	ft_normalize_axis_value(int raw_value)
{
	if (raw_value > 16000)
		return (1);
	else if (raw_value < -16000)
		return (-1);
	return (0);
}

/*
** ft_reset_single_gamepad - Resetea el estado de un gamepad
** @gp: Puntero al gamepad a resetear
**
** Pone todos los valores del gamepad a su estado inicial.
*/
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

/*
** ft_gamepad_has_input - Detecta si hay input activo en el gamepad
** @gp: Puntero al gamepad a verificar
**
** Verifica si algún stick o botón está activo.
** Return: 1 si hay input, 0 si no
*/
static int	ft_gamepad_has_input(t_gamepad *gp)
{
	if (gp->left_stick_x != 0 || gp->left_stick_y != 0)
		return (1);
	if (gp->right_stick_x != 0 || gp->right_stick_y != 0)
		return (1);
	if (gp->a || gp->b || gp->x || gp->y)
		return (1);
	if (gp->lb || gp->rb)
		return (1);
	return (0);
}

/*
** ft_process_button_ab - Procesa los botones A y B del gamepad
** @gp: Puntero al gamepad
** @event: Evento de joystick recibido
**
** Actualiza el estado de los botones A (0) y B (1).
*/
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

/*
** ft_process_button_event - Procesa eventos de botones del gamepad
** @game: Puntero a la estructura del juego
** @gp: Puntero al gamepad
** @event: Evento de joystick recibido
**
** Distribuye el procesamiento según el número de botón.
*/
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

/*
** ft_process_axis_event - Procesa eventos de ejes del gamepad
** @gp: Puntero al gamepad
** @event: Evento de joystick recibido
**
** Actualiza los valores de los sticks analógicos normalizados.
*/
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

/*
** ft_process_gamepad_event - Distribuye eventos del gamepad
** @game: Puntero a la estructura del juego
** @gp: Puntero al gamepad
** @event: Evento de joystick recibido
**
** Enruta el evento según su tipo (botón o eje).
*/
static void	ft_process_gamepad_event(t_game *game, t_gamepad *gp,
	struct js_event event)
{
	if (event.type == JS_EVENT_BUTTON)
		ft_process_button_event(game, gp, event);
	else if (event.type == JS_EVENT_AXIS)
		ft_process_axis_event(gp, event);
}

/*
** ft_process_menu_buttons - Procesa botones A/B en el menú
** @game: Puntero a la estructura del juego
** @i: Índice del gamepad
**
** Maneja las acciones de aceptar (A) y cancelar (B) en el menú.
*/
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

/*
** ft_gamepad_menu_input_for_all - Procesa input de todos los gamepads
** @game: Puntero a la estructura del juego
**
** Revisa todos los gamepads conectados y procesa sus botones de menú.
*/
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

/*
** ft_try_open_gamepad_at - Intenta abrir un gamepad en una ruta
** @game: Puntero a la estructura del juego
** @path: Ruta del dispositivo a abrir
** @slot: Slot donde guardar el gamepad (0-3)
**
** Return: 1 si se abrió correctamente, 0 si falló
*/
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

/*
** ft_init_gamepad_paths - Inicializa los gamepads buscando en rutas
** @game: Puntero a la estructura del juego
**
** Busca gamepads en las rutas /dev/input/js* y /dev/input/event*.
*/
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

/*
** ft_init_gamepad - Inicializa el sistema de gamepads
** @game: Puntero a la estructura del juego
**
** Resetea todos los gamepads y busca dispositivos conectados.
*/
void	ft_init_gamepad(t_game *game)
{
	int	i;

	game->gamepad_count = 0;
	game->waiting_for_gamepads = 0;
	game->kb_player = 0;
	i = 0;
	while (i < MAX_GAMEPADS)
	{
		ft_reset_single_gamepad(&game->gamepads[i]);
		i++;
	}
	ft_init_gamepad_paths(game);
	if (game->gamepad_count == 0)
		ft_printf("Info: No gamepad detected "
			"(keyboard controls active)\n");
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
}

/*
** ft_free_gamepad - Libera recursos de los gamepads
** @game: Puntero a la estructura del juego
**
** Cierra todos los file descriptors y resetea el estado.
*/
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

/*
** ft_recount_gamepads - Recuenta gamepads conectados
** @game: Puntero a la estructura del juego
**
** Actualiza el contador de gamepads conectados.
*/
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

/*
** ft_handle_gamepad_error - Maneja errores de lectura del gamepad
** @game: Puntero a la estructura del juego
** @slot: Slot del gamepad con error
**
** Cierra y resetea el gamepad que tuvo un error de lectura.
*/
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

/*
** ft_read_gamepad_events - Lee eventos del gamepad
** @game: Puntero a la estructura del juego
** @i: Índice del gamepad a leer
**
** Lee todos los eventos pendientes del gamepad y los procesa.
*/
static void	ft_read_gamepad_events(t_game *game, int i)
{
	struct js_event	event;
	ssize_t			bytes;

	/*
	 * Evita estados "pegados": algunos mandos/drivers pueden perder el
	 * último evento (value=0) al soltar el stick. Como el juego usa un
	 * estado persistente, reseteamos ejes cada tick y aplicamos lo leído.
	 */
	game->gamepads[i].left_stick_x = 0;
	game->gamepads[i].left_stick_y = 0;
	game->gamepads[i].right_stick_x = 0;
	game->gamepads[i].right_stick_y = 0;

	bytes = read(game->gamepads[i].fd, &event, sizeof(event));
	while (bytes > 0)
	{
		ft_process_gamepad_event(game, &game->gamepads[i], event);
		bytes = read(game->gamepads[i].fd, &event, sizeof(event));
	}
	if (bytes == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
		ft_handle_gamepad_error(game, i);
}

/*
** ft_update_gamepad - Actualiza el estado de todos los gamepads
** @game: Puntero a la estructura del juego
**
** Lee eventos de todos los gamepads conectados.
*/
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

/*
** ft_set_player_movement - Aplica movimiento del stick al jugador
** @act: Acciones del jugador a modificar
** @gp: Gamepad del que leer el input
**
** Traduce el stick izquierdo a acciones de movimiento.
*/
static void	ft_set_player_movement(t_player_actions *act, t_gamepad *gp)
{
	if (gp->left_stick_y == -1)
		act->front = 1;
	else if (gp->left_stick_y == 1)
		act->back = 1;
	if (gp->left_stick_x == -1)
		act->left = 1;
	else if (gp->left_stick_x == 1)
		act->right = 1;
	if (gp->right_stick_click)
		act->run = 1;
}

/*
** ft_set_player_rotation - Aplica rotación del stick al jugador
** @act: Acciones del jugador a modificar
** @gp: Gamepad del que leer el input
**
** Traduce el stick derecho y bumpers a rotación.
*/
static void	ft_set_player_rotation(t_player_actions *act, t_gamepad *gp)
{
	if (gp->right_stick_x == -1 || gp->lb)
		act->rotate_left = 1;
	else if (gp->right_stick_x == 1 || gp->rb)
		act->rotate_right = 1;
}

/*
** ft_gamepad_apply_to_player - Aplica input del gamepad al jugador
** @game: Puntero a la estructura del juego
** @gp: Gamepad del que leer
** @player_idx: Índice del jugador a actualizar
**
** Traduce el input del gamepad a acciones del jugador.
*/
static void	ft_gamepad_apply_to_player(t_game *game, t_gamepad *gp,
	int player_idx)
{
	if (player_idx >= game->config.n_players)
		return ;
	ft_set_player_movement(&game->actions[player_idx], gp);
	ft_set_player_rotation(&game->actions[player_idx], gp);
	game->devices[player_idx] = INPUT_GAMEPAD;
}

/*
** ft_apply_player0_input - Maneja input del jugador 0
** @game: Puntero a la estructura del juego
**
** Aplica gamepad si hay input activo, sino deja teclado.
*/
static void	ft_apply_player0_input(t_game *game)
{
	if (game->gamepads[0].connected
		&& ft_gamepad_has_input(&game->gamepads[0]))
	{
		input_reset_actions(game, 0);
		ft_gamepad_apply_to_player(game, &game->gamepads[0], 0);
		game->devices[0] = INPUT_GAMEPAD;
		game->kb_player = -1;
	}
	else
	{
		game->devices[0] = INPUT_KEYBOARD;
		game->kb_player = 0;
	}
}

/*
** ft_apply_other_players - Maneja input de jugadores 1-3
** @game: Puntero a la estructura del juego
**
** Requieren gamepad obligatoriamente.
*/
static void	ft_apply_other_players(t_game *game)
{
	int	i;

	i = 1;
	while (i < game->config.n_players && i < MAX_GAMEPADS)
	{
		if (i < game->gamepad_count && game->gamepads[i].connected)
		{
			input_reset_actions(game, i);
			ft_gamepad_apply_to_player(game, &game->gamepads[i], i);
		}
		i++;
	}
}

/*
** ft_gamepad_movement - Actualiza acciones según gamepads/teclado
** @game: Puntero a la estructura del juego
**
** Distribuye el input: player 0 puede usar teclado o gamepad,
** players 1-3 requieren gamepad.
*/
void	ft_gamepad_movement(t_game *game)
{
	if (game->show_menu)
	{
		if (game->gamepad_count > 0)
			ft_gamepad_menu_input_for_all(game);
		return ;
	}
	ft_apply_player0_input(game);
	ft_apply_other_players(game);
	if (game->config.n_players > 1
		&& game->gamepad_count < game->config.n_players)
		game->waiting_for_gamepads = 1;
	else
		game->waiting_for_gamepads = 0;
}
