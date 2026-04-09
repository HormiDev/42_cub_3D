/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flamethrower_hud_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:20 by username          #+#    #+#             */
/*   Updated: 2026/04/10 00:37:41 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static t_texture	*ft_get_flamethrower_frame(t_game *game, t_player_actions *actions)
{
	t_texture	*flame;
	int			frame_index;
	double		elapsed_time;
	double		frame_duration;

	flame = game->flamethrower_frames[0];
	if (!actions->flamethrower_animating)
		return (flame);
	elapsed_time = game->current_time - actions->flamethrower_anim_time;
	frame_duration = 200;
	if (elapsed_time < frame_duration * 3)
	{
		frame_index = (int)(elapsed_time / frame_duration) + 1;
		if (frame_index > 3)
			frame_index = 3;
		if (game->flamethrower_frames[frame_index])
			flame = game->flamethrower_frames[frame_index];
	}
	else
		actions->flamethrower_animating = 0;
	return (flame);
}

void	ft_render_flamethrower(t_game *game, int player_index)
{
	t_texture			*flame;
	t_player_actions	*actions;
	int					size;
	int					max_size;
	int					x;
	int					y;

	actions = &game->actions[player_index];
	flame = ft_get_flamethrower_frame(game, actions);
	if (!flame)
		return ;
	size = (game->render->height * 180) / 100;
	if (size < flame->height)
		size = flame->height;
	max_size = (game->render->height * 200) / 100;
	if (game->render->width < game->render->height)
		max_size = (game->render->width * 200) / 100;
	if (size > max_size)
		size = max_size;
	x = game->render->width - size + (game->render->width / 15);
	y = game->render->height - size + (game->render->height / 2.2);
	ft_draw_image_rgba_scaled(game->render, flame, x, y, size);
}
