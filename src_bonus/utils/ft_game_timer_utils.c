/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/29 16:55:22 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	get_duration(int idx)
{
	static const int durations[GAME_DURATIONS_COUNT] = {60, 120, 180, 300, 600};
	if (idx < 0)
		return durations[0];
	if (idx >= GAME_DURATIONS_COUNT)
		return durations[GAME_DURATIONS_COUNT - 1];
	return durations[idx];
}

int	ft_get_duration_seconds(t_game *game)
{
	return get_duration(game->config.duration_index);
}

int	ft_get_duration_minutes(t_game *game)
{
	return get_duration(game->config.duration_index) / 60;
}

void	ft_init_timer(t_game *game)
{
	game->game_start_time = ft_get_time();
	game->game_state = GAME_PLAYING;
}

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