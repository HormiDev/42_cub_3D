/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:13 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/02 16:36:38 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Devuelve la duración (en segundos) asociada a un índice.
 *
 * Usa una tabla estática con las duraciones permitidas y aplica saturación
 * en los límites: si `idx` es menor que 0 devuelve la primera duración, y si
 * es mayor o igual a `GAME_DURATIONS_COUNT` devuelve la última.
 *
 * @param idx Índice en la tabla de duraciones.
 * @return Duración en segundos correspondiente al índice.
 */
static int	get_duration(int idx)
{
	static const int durations[GAME_DURATIONS_COUNT] = {60, 120, 180, 300, 600};
	if (idx < 0)
		return durations[0];
	if (idx >= GAME_DURATIONS_COUNT)
		return durations[GAME_DURATIONS_COUNT - 1];
	return durations[idx];
}

/**
 * @brief Obtiene la duración de la partida en segundos según la configuración.
 *
 * Consulta `game->config.duration_index` y devuelve el valor en segundos
 * obtenido de `get_duration`.
 *
 * @param game Puntero al estado del juego.
 * @return Duración en segundos.
 */
int	ft_get_duration_seconds(t_game *game)
{
	return get_duration(game->config.duration_index);
}

/**
 * @brief Obtiene la duración de la partida en minutos según la configuración.
 *
 * Devuelve la duración (segundos) dividida por 60 para representar minutos.
 *
 * @param game Puntero al estado del juego.
 * @return Duración en minutos.
 */
int	ft_get_duration_minutes(t_game *game)
{
	return get_duration(game->config.duration_index) / 60;
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
	long elapsed_ms = ft_long_diff(game->game_start_time, ft_get_time());
	int elapsed_sec = (int)(elapsed_ms / 1000);
	int remaining = get_duration(game->config.duration_index) - elapsed_sec;
	if (remaining > 0)
		return remaining;
	else
		return 0;
}