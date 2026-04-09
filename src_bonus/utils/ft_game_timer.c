/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_game_timer.c                                   :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/02 16:26:17 by username         #+#    #+#              */
/*   Updated: 2026/04/09 16:34:06 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
* @brief Comprueba el temporizador del juego y actualiza el estado si llega a 0.
*
* Si el juego está en curso (`GAME_PLAYING`) y el tiempo restante es menor o
* igual a 0, cambia `game->game_state` a `GAME_PLAYERS_WIN`.
*
* @param game Puntero al estado del juego.
*/

void	ft_check_timer(t_game *game)
{
	if (game->game_state == GAME_PLAYING && ft_get_remaining(game) <= 0)
		game->game_state = GAME_PLAYERS_WIN;
}

/**
* @brief Ajusta el índice de duración del juego según la dirección.
*
* Incrementa o decrementa `game->config.duration_index` dentro de los límites
* definidos por `GAME_DURATIONS_COUNT`.
*
* @param game_ptr Puntero genérico al `t_game` (se castea internamente).
* @param direction Valor positivo para aumentar, negativo para disminuir.
*/

void	ft_change_duration(void *game_ptr, int direction)
{
	t_game	*game;

	game = (t_game *) game_ptr;
	if (direction > 0 && game->config.duration_index < GAME_DURATIONS_COUNT - 1)
		game->config.duration_index++;
	else if (direction < 0 && game->config.duration_index > 0)
		game->config.duration_index--;
}

/**
* @brief Añade un valor como dos dígitos al buffer
*
* Escribe en `buf` a partir de la posición `len` el `value` como texto
* al menos dos dígitos (p. ej. 03, 12).
*
* @param buf Buffer destino donde se escribe la representación.
* @param len Posición inicial en el buffer donde comenzar a escribir.
* @param value Valor numérico a formatear (por ejemplo minutos o segundos).
* @return Nueva longitud del buffer tras escribir los dígitos.
*/

static int	append_two_digits(char *buf, int len, int value)
{
	if (value < 10)
		buf[len++] = '0';
	len += ft_sprintf(buf + len, "%d", value);
	return (len);
}

/**
* @brief Construye la cadena del temporizador en formato "MM SS" desde segundos.
*
* Convierte `remaining` en minutos y segundos, y escribe la representación
* en `str` usando `append_two_digits` para garantizar el ancho de dos dígitos.
*
* @param str Buffer donde se escribirá la cadena resultante.
* @param remaining Segundos restantes totales.
*/

static void	get_timer_string(char *str, int remaining)
{
	int	len;
	int	minutes;
	int	seconds;

	len = 0;
	minutes = remaining / 60;
	seconds = remaining % 60;
	len = append_two_digits(str, len, minutes);
	str[len++] = ' ';
	len = append_two_digits(str, len, seconds);
	str[len] = '\0';
}

static int	ft_get_hud_scale(int viewport_height)
{
	int	scale;

	scale = viewport_height / (WINDOW_HEIGHT / 2);
	if (scale < 2)
		scale = 2;
	return (scale);
}

void ft_render_timer_hud_viewport(t_game * game, t_texture * target,
	int	offset_x, int offset_y, t_vector_int viewport)
{
	char			str[16];
	int				remaining;
	int				timer_width;
	int				text_len;
	int				scale;
	t_vector_int	pos;

	scale = ft_get_hud_scale(viewport.y);
	if (game->game_state == GAME_PLAYERS_WIN)
	{
		text_len = ft_strlen("players win");
		pos.x = offset_x + viewport.x / 2 - (text_len * 6 * scale) / 2;
		pos.y = offset_y + viewport.y / 2 - (game->font->height * scale) / 2;
		ft_draw_string_hud(target, game->font, "players win", &pos, scale);
		return ;
	}
	remaining = ft_get_remaining(game);
	get_timer_string(str, remaining);
	timer_width = ft_strlen(str) * 6 * scale;
	pos.x = offset_x + viewport.x / 2 - timer_width - (10 * scale);
	pos.y = offset_y + (10 * scale);
	ft_draw_string_hud(target, game->font, str, &pos, scale);
}

/**
* @brief Renderiza el HUD del temporizador en pantalla.
*
* Si el estado del juego es `GAME_PLAYERS_WIN`, muestra el mensaje de victoria.
* En caso contrario obtiene el tiempo restante, construye la cadena y la dibuja
* en la esquina superior derecha de la ventana.
*
* @param game Puntero al estado del juego usado para obtener render.
*/

void	ft_render_timer_hud(t_game *game)
{
	t_texture		*target;
	t_vector_int	viewport;

	target = game->render;
	if (game->config.n_players == 1
			&& (game->config.render_height != WINDOW_HEIGHT
		|| game->config.render_width != WINDOW_WIDTH))
	target = game->window_img;
	viewport.x = target->width;
	viewport.y = target->height;
	ft_render_timer_hud_viewport(game, target, 0, 0, viewport);
}
