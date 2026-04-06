/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 00:00:00 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/06 23:17:01 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

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
