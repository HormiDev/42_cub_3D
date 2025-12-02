/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:00:00 by ismherna          #+#    #+#             */
/*   Updated: 2025/12/02 00:00:00 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/*
 * Audio manager centralizado.
 * Gestiona todos los sonidos del juego con control de estado.
 */

static int	audio_is_playing(pid_t pid)
{
	int	status;

	if (pid <= 0)
		return (0);
	if (waitpid(pid, &status, WNOHANG) == 0)
		return (1);
	return (0);
}

int	audio_play(t_game *game, const char *path, pid_t *pid_out)
{
	if (!path || !game)
		return (-1);
	*pid_out = ft_play_audio(path, game->env);
	return (*pid_out);
}

int	audio_stop(pid_t *pid)
{
	int	ret;

	if (*pid <= 0)
		return (-1);
	ret = ft_stop_audio(*pid);
	*pid = -1;
	return (ret);
}

int	audio_play_steps(t_game *game, const char *path)
{
	if (audio_is_playing(game->steps_audio_pid))
		return (game->steps_audio_pid);
	return (audio_play(game, path, &game->steps_audio_pid));
}

int	audio_stop_steps(t_game *game)
{
	return (audio_stop(&game->steps_audio_pid));
}

int	audio_play_menu(t_game *game, const char *path)
{
	if (audio_is_playing(game->menu.menu_music_pid))
		return (game->menu.menu_music_pid);
	return (audio_play(game, path, &game->menu.menu_music_pid));
}

int	audio_stop_menu(t_game *game)
{
	return (audio_stop(&game->menu.menu_music_pid));
}
