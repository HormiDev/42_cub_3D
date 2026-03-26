/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/15 18:23:39 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static const int	g_durations[GAME_DURATIONS_COUNT] = {60, 120, 180, 300, 600};

/**
 * @brief Devuelve la duracion en segundos segun el indice actual.
 */
int	ft_get_duration_seconds(t_game *game)
{
	return (g_durations[game->config.duration_index]);
}

/**
 * @brief Devuelve la duracion en minutos segun el indice actual.
 * Util para mostrar en el menu de configuracion.
 */
int	ft_get_duration_minutes(t_game *game)
{
	return (g_durations[game->config.duration_index] / 60);
}

/**
 * @brief Inicia el temporizador de partida.
 * Guarda el tiempo actual y pone el estado de juego en GAME_PLAYING.
 * Debe llamarse justo cuando la partida arranca (show_menu pasa a 0).
 */
void	ft_init_timer(t_game *game)
{
	game->game_start_time = ft_get_time();
	game->game_state = GAME_PLAYING;
}

/**
 * @brief Devuelve los segundos restantes de partida.
 * Retorna 0 si el tiempo ya ha vencido.
 */
int	ft_get_remaining(t_game *game)
{
	long	elapsed_ms;
	int		elapsed_sec;
	int		remaining;

	elapsed_ms = ft_long_diff(game->game_start_time, ft_get_time());
	elapsed_sec = (int)(elapsed_ms / 1000);
	remaining = ft_get_duration_seconds(game) - elapsed_sec;
	if (remaining < 0)
		return (0);
	return (remaining);
}

/**
 * @brief Comprueba si el temporizador ha llegado a 0.
 * Si es asi, cambia el estado a GAME_PLAYERS_WIN.
 * Debe llamarse una vez por frame en ft_update().
 */
void	ft_check_timer(t_game *game)
{
	if (game->game_state != GAME_PLAYING)
		return ;
	if (ft_get_remaining(game) <= 0)
		game->game_state = GAME_PLAYERS_WIN;
}

/**
 * @brief Avanza al siguiente tiempo de partida predefinido.
 */
void	ft_next_duration(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (game->config.duration_index >= GAME_DURATIONS_COUNT - 1)
		return ;
	game->config.duration_index++;
}

/**
 * @brief Retrocede al tiempo de partida predefinido anterior.
 */
void	ft_previous_duration(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (game->config.duration_index <= 0)
		return ;
	game->config.duration_index--;
}

static int	append_two_digits(char *buf, int len, int value)
{
	if (value < 10)
	{
		buf[len++] = '0';
		len += ft_sprintf(buf + len, "%d", value);
		return (len);
	}
	len += ft_sprintf(buf + len, "%d", value);
	return (len);
}


/**
 * @brief Dibuja el temporizador restante en pantalla en formato MM:SS.
 * Usa mlx_string_put centrado en la parte superior de la ventana.
 * Si la partida ha terminado muestra el mensaje de victoria.
 */
void	ft_render_timer_hud(t_game *game)
{
	char	str[16];
	int		remaining;
	int		minutes;
	int		seconds;

	if (game->game_state == GAME_PLAYERS_WIN)
	{
		mlx_string_put(game->mlx, game->window,
			WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2,
			0xFF00FF00, "PLAYERS WIN!");
		return ;
	}
	remaining = ft_get_remaining(game);
	minutes = remaining / 60;
	seconds = remaining % 60;
	int	len = 0;
	len = append_two_digits(str, len, minutes);
	str[len++] = ':';
	len = append_two_digits(str, len, seconds);
	str[len] = '\0';
	mlx_string_put(game->mlx, game->window,
		WINDOW_WIDTH / 2 - 16, 40, 0xFFFFFF00, str);
}
