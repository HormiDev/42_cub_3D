/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:13 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_init_durations(t_game *game)
{
	game->durations_size = 5;
	game->durations = hd_calloc(game->durations_size, sizeof(int));
	game->durations[DURATION_1_MINUTE] = 60;
	game->durations[DURATION_2_MINUTES] = 120;
	game->durations[DURATION_3_MINUTES] = 180;
	game->durations[DURATION_5_MINUTES] = 300;
	game->durations[DURATION_10_MINUTES] = 600;
}

int	get_duration(t_game *game)
{
	if (game->config.duration_index < 0
		|| game->config.duration_index >= game->durations_size)
		return (game->durations[0]);
	return (game->durations[game->config.duration_index]);
}

/**
 * @brief Inicializa el temporizador de la partida.
 *
 * Establece `game->game_start_time` al tiempo actual y fija el estado del juego
 * en `GAME_PLAYING`.
 *
 * @param game Puntero al estado del juego a inicializar.
 */

void	ft_init_timer(t_game *game)
{
	game->game_start_time = ft_get_time();
	game->game_state = GAME_PLAYING;
}

/**
 * @brief Calcula los segundos restantes de la partida.
 *
 * Calcula el tiempo transcurrido en milisegundos desde `game_start_time`, lo
 * convierte a segundos y resta de la duración configurada. Nunca devuelve
 * valores negativos; en ese caso retorna 0.
 *
 * @param game Puntero al estado del juego.
 * @return Segundos restantes (>= 0).
 */

int	ft_get_remaining(t_game *game)
{
	long	elapsed_ms;
	int		elapsed_sec;
	int		remaining;

	elapsed_ms = ft_long_diff(game->game_start_time, ft_get_time());
	elapsed_sec = (int)(elapsed_ms / 1000);
	remaining = get_duration(game) - elapsed_sec;
	if (remaining > 0)
		return (remaining);
	else
		return (0);
}

/**

* @brief Construye la cadena del temporizador 
 * en formato "MM SS" desde segundos.
 *
 * Convierte `remaining` en minutos y segundos, y escribe la representación
 * en `str` usando `append_two_digits` para garantizar el ancho de dos dígitos.
 *
 * @param str Buffer donde se escribirá la cadena resultante.
 * @param remaining Segundos restantes totales.
 */

void	get_timer_string(char *str, int remaining)
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
