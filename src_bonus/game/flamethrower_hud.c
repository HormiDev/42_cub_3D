/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   flamethrower_hud.c                                :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/02 16:22:20 by username         #+#    #+#              */
/*   Updated: 2026/04/09 16:34:11 by username        ###   ########.fr        */
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

void	ft_render_flamethrower_sprite(t_game *game, int player_index)
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

static int	ft_get_hud_scale(int viewport_height)
{
	int	scale;

	scale = viewport_height / (WINDOW_HEIGHT / 2);
	if (scale < 2)
		scale = 2;
	return (scale);
}

static void ft_draw_flamethrower_charges(t_game * game,
	t_player_actions	*actions, t_texture *target, t_vector_int pos, int scale)
{
	char	str[32];

	ft_sprintf(str, "CHARGES:%d / %d", actions->flamethrower_charges,
		game->config.charges);
	ft_draw_string_hud(target, game->font, str, &pos, scale);
}

static void ft_draw_flamethrower_cooldown(t_game * game,
	t_player_actions	*actions, t_texture *target, t_vector_int pos, int scale)
{
	char	str[32];

	if (actions->flamethrower_cooldown_remaining <= 0)
		return ;
	ft_sprintf(str, "COOLDOWN:%ds", (int) actions->flamethrower_cooldown_remaining);
	ft_draw_string_hud(target, game->font, str, &pos, scale);
}

void ft_render_flamethrower_hud_viewport(t_game * game, int player_index,
	t_texture	*target, int offset_x, int offset_y, t_vector_int viewport)
{
	t_player_actions	*actions;
	t_vector_int		pos;
	int					scale;

	actions = &game->actions[player_index];
	scale = ft_get_hud_scale(viewport.y);
	pos.x = offset_x + viewport.x - (viewport.x / 4);
	pos.y = offset_y + viewport.y / 20;
	ft_draw_flamethrower_charges(game, actions, target, pos, scale);
	pos.y = offset_y + viewport.y / 12;
	ft_draw_flamethrower_cooldown(game, actions, target, pos, scale);
}

void	ft_render_flamethrower_hud(t_game *game, int player_index)
{
	t_texture		*target;
	t_vector_int	viewport;

	target = game->render;
	if (game->config.n_players == 1
			&& (game->config.render_height != WINDOW_HEIGHT
		|| game->config.render_width != WINDOW_WIDTH))
	target = game->window_img;
	viewport.x = target->width;
	viewport.y = target->height;
	ft_render_flamethrower_hud_viewport(game, player_index, target, 0, 0,
		viewport);
}
