/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:17 by username          #+#    #+#             */
/*   Updated: 2026/04/10 01:14:32 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**

* @brief Comprueba el temporizador del juego y
 *  actualiza el estado si llega a 0.
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

	game = (t_game *)game_ptr;
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

int	append_two_digits(char *buf, int len, int value)
{
	if (value < 10)
		buf[len++] = '0';
	len += ft_sprintf(buf + len, "%d", value);
	return (len);
}
