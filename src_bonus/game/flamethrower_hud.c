/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flamethrower_hud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:20 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:03:54 by ismherna         ###   ########.fr       */
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
	char	str[32];

	ft_sprintf(str, "CHARGES:%d / %d", actions->flamethrower_charges,
		game->config.charges);
	ft_draw_string_hud(hud->target, game->font, str, &hud->pos, hud->scale);
}

static void	ft_draw_flamethrower_cooldown(t_game *game,
		t_player_actions *actions, t_hud_draw *hud)
{
	char	str[32];

	if (actions->flamethrower_cooldown_remaining <= 0)
		return ;
	ft_sprintf(str, "COOLDOWN:%ds",
		(int)actions->flamethrower_cooldown_remaining);
	ft_draw_string_hud(hud->target, game->font, str, &hud->pos, hud->scale);
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
	pos.x = pos_offset.x + target->width - (target->width / 4);
	pos.y = pos_offset.y + target->height / 20;
	hud.pos = pos;
	ft_draw_flamethrower_charges(game, actions, &hud);
	pos.y = pos_offset.y + target->height / 12;
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
