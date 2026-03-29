/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/29 16:55:03 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_check_timer(t_game *game)
{
	if (game->game_state == GAME_PLAYING && ft_get_remaining(game) <= 0)
		game->game_state = GAME_PLAYERS_WIN;
}

void	ft_next_duration(void *game_ptr)
{
	t_game *game = (t_game *)game_ptr;
	if (game->config.duration_index < GAME_DURATIONS_COUNT - 1)
		game->config.duration_index++;
}

void	ft_previous_duration(void *game_ptr)
{
	t_game *game = (t_game *)game_ptr;
	if (game->config.duration_index > 0)
		game->config.duration_index--;
}

static int	append_two_digits(char *buf, int len, int value)
{
	if (value < 10)
		buf[len++] = '0';
	len += ft_sprintf(buf + len, "%d", value);
	return len;
}

void	ft_render_timer_hud(t_game *game)
{
	char str[16];
	int remaining, minutes, seconds, len = 0;
	if (game->game_state == GAME_PLAYERS_WIN)
	{
		mlx_string_put(game->mlx, game->window,
			WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2,
			0xFF00FF00, "PLAYERS WIN!");
		return;
	}
	remaining = ft_get_remaining(game);
	minutes = remaining / 60;
	seconds = remaining % 60;
	len = append_two_digits(str, len, minutes);
	str[len++] = ':';
	len = append_two_digits(str, len, seconds);
	str[len] = '\0';
	mlx_string_put(game->mlx, game->window,
		WINDOW_WIDTH / 2 - 16, 40, 0xFFFFFF00, str);
}
