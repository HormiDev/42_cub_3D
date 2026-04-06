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
** ft_normalize_axis_value - Normaliza el valor del eje del gamepad
** @raw_value: Valor crudo del eje (-32768 a 32767)
**
** Convierte valores analógicos en digitales: 1, -1 o 0.
** Return: 1 si > 16000, -1 si < -16000, 0 en otro caso
*/
int	ft_normalize_axis_value(int raw_value)
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
void	ft_reset_single_gamepad(t_gamepad *gp)
{
	gp->connected = 0;
	gp->fd = -1;
	gp->a = 0;
	gp->b = 0;
	gp->x = 0;
	gp->y = 0;
	gp->lb = 0;
	gp->rb = 0;
	gp->rt = 0;
	gp->left_stick_x = 0;
	gp->left_stick_y = 0;
	gp->right_stick_x = 0;
	gp->right_stick_y = 0;
	gp->right_stick_click = 0;
	gp->a_pressed = 0;
	gp->b_pressed = 0;
	gp->rt_pressed = 0;
}

/*
** ft_gamepad_has_input - Detecta si hay input activo en el gamepad
** @gp: Puntero al gamepad a verificar
**
** Verifica si algún stick o botón está activo.
** Return: 1 si hay input, 0 si no
*/
int	ft_gamepad_has_input(t_gamepad *gp)
{
	if (gp->left_stick_x != 0 || gp->left_stick_y != 0)
		return (1);
	if (gp->right_stick_x != 0 || gp->right_stick_y != 0)
		return (1);
	if (gp->a || gp->b || gp->x || gp->y)
		return (1);
	if (gp->lb || gp->rb || gp->rt)
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
void	ft_process_button_ab(t_gamepad *gp, struct js_event event)
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
** @game: estructura del juego
** @gp: Puntero al gamepad
** @event: Evento de joystick recibido
**
** Distribuye el procesamiento según el número de botón.
*/
void	ft_process_button_event(t_game *game, t_gamepad *gp,
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
	else if (event.number == 7)
	{
		gp->rt = event.value;
		if (event.value == 1)
			gp->rt_pressed = 1;
	}
	else if (event.number == 9)
		gp->right_stick_click = event.value;
}
