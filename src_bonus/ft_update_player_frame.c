/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_player_frame.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 17:02:22 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_update_player_frame(t_game *game)
{
	int	speed;

	speed = game->player->speed * 500;
	if (game->player->in_movement == 1
		&& game->current_time > game->player->model->last_update_time + (speed
			/ game->player->model->n_frames))
	{
		game->player->model->last_update_time = game->current_time;
		game->player->model->active_frame++;
		if (game->player->model->active_frame > game->player->model->n_frames)
			game->player->model->active_frame = 1;
	}
	else if (game->player->in_movement == -1
		&& game->current_time > game->player->model->last_update_time + (speed
			/ game->player->model->n_frames))
	{
		game->player->model->last_update_time = game->current_time;
		game->player->model->active_frame--;
		if (game->player->model->active_frame < 1)
			game->player->model->active_frame = game->player->model->n_frames;
	}
}
