/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:17 by username          #+#    #+#             */
/*   Updated: 2026/04/08 18:10:41 by ide-dieg         ###   ########.fr       */
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
	char			str[16];
	int				remaining;
	int				timer_width;
	t_vector_int	pos;

	if (game->game_state == GAME_PLAYERS_WIN)
	{
		pos.x = WINDOW_WIDTH / 4 - 33;
		pos.y = WINDOW_HEIGHT / 2;
		ft_draw_string_hud(game->render, game->font,
			"players win", &pos, 2);
		return ;
	}
	remaining = ft_get_remaining(game);
	get_timer_string(str, remaining);
	timer_width = 6 * 4;
	pos.x = game->render->width / 2 - timer_width - 10;
	pos.y = 10;
	ft_draw_string_hud(game->render, game->font, str, &pos, 2);
}
