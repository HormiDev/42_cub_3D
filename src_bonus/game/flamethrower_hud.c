/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flamethrower_hud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:20 by username          #+#    #+#             */
/*   Updated: 2026/04/13 01:15:14 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	ft_get_hud_scale(int viewport_height)
{
	int	scale;

	scale = viewport_height / (WINDOW_HEIGHT / 2);
	if (scale < 2)
		scale = 2;
	return (scale);
}

static void	ft_draw_flamethrower_charges(t_game *game,
		t_player_actions *actions, t_hud_draw *hud)
{
	char			str[32];
	t_string_ctx	ctx;

	ft_sprintf(str, "CHARGES:%d / %d", actions->flamethrower_charges,
		game->config.charges);
	ctx.dst = hud->target;
	ctx.font = game->font;
	ctx.scale = hud->scale;
	ctx.pos = hud->pos;
	ft_draw_string_hud(ctx.dst, ctx.font, str, &ctx);
}

static void	ft_draw_flamethrower_cooldown(t_game *game,
		t_player_actions *actions, t_hud_draw *hud)
{
	char			str[32];
	t_string_ctx	ctx;

	if (actions->flamethrower_cooldown_remaining <= 0)
		return ;
	ft_sprintf(str, "COOLDOWN:%ds",
		(int)actions->flamethrower_cooldown_remaining);
	ctx.dst = hud->target;
	ctx.font = game->font;
	ctx.scale = hud->scale;
	ctx.pos = hud->pos;
	ft_draw_string_hud(ctx.dst, ctx.font, str, &ctx);
}

void	ft_flamethrower_hud(t_game *game, int player_index, t_texture *target,
		t_vector_int pos_offset)
{
	t_player_actions	*actions;
	t_hud_draw			hud;
	t_vector_int		pos;

	actions = &game->actions[player_index];
	hud.target = target;
	hud.scale = ft_get_hud_scale(target->height);
	pos.x = pos_offset.x + target->width - (target->width / 1.01);
	pos.y = pos_offset.y + target->height / 4.5;
	hud.pos = pos;
	ft_draw_flamethrower_charges(game, actions, &hud);
	pos.y += hud.scale * 18;
	hud.pos = pos;
	ft_draw_flamethrower_cooldown(game, actions, &hud);
}

void	ft_render_flamethrower_hud(t_game *game, int player_index)
{
	t_texture		*target;
	t_vector_int	pos_offset;

	target = game->render;
	if (game->config.n_players == 1
		&& (game->config.render_height != WINDOW_HEIGHT
			|| game->config.render_width != WINDOW_WIDTH))
		target = game->window_img;
	pos_offset.x = 0;
	pos_offset.y = 0;
	ft_flamethrower_hud(game, player_index, target, pos_offset);
}
