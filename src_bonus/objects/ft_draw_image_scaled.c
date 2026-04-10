/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_image_scaled.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:22:24 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:01:28 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_draw_scaled_mist_row(t_game *game, t_texture *src,
		t_scaled_state *state, t_scaled_draw row_draw)
{
	t_scaled_scan	scan;

	ft_scaled_mist_scan_init(&scan, src, state, row_draw);
	ft_scaled_mist_scan_draw(&scan, game, src, state);
}

void	ft_scaled_mist_scan_init(t_scaled_scan *scan, t_texture *src,
		t_scaled_state *state, t_scaled_draw row_draw)
{
	scan->mist_color = MIST_COLOR;
	scan->distance = row_draw.distance;
	scan->mist_mix = 255 * row_draw.distance / MAX_RAY_SIZE;
	scan->dst_pos.y = row_draw.pos.y;
	scan->src_pos.y = (int)(state->start_src.y + (scan->dst_pos.y
				- state->start_dst.y) * state->src_iter.y);
	if (scan->src_pos.y >= src->height)
		scan->src_pos.y = src->height - 1;
	scan->dst_pos.x = state->start_dst_x;
	scan->src_f.x = state->start_src_x;
	scan->src_pos.x = (int)scan->src_f.x;
}

void	ft_scaled_mist_scan_draw(t_scaled_scan *scan, t_game *game,
		t_texture *src, t_scaled_state *state)
{
	scan->raycast_iter = -scan->dst_pos.x + game->config.render_width - 1;
	while (scan->dst_pos.x <= state->end_dst.x)
	{
		if (scan->distance <= game->raycasts[scan->raycast_iter].distance
			&& src->cmx[scan->src_pos.y][scan->src_pos.x] > 0x00FFFFFF)
		{
			game->render->cmx[scan->dst_pos.y][scan->dst_pos.x]
				= src->cmx[scan->src_pos.y][scan->src_pos.x];
			ft_mix_rgba(&game->render->cmx[scan->dst_pos.y][scan->dst_pos.x],
				&scan->mist_color, scan->mist_mix);
		}
		scan->raycast_iter--;
		scan->dst_pos.x++;
		scan->src_f.x += state->src_iter.x;
		scan->src_pos.x = (int)scan->src_f.x;
		if (scan->src_pos.x >= src->width)
			scan->src_pos.x = src->width - 1;
	}
}

void	ft_draw_image_rgba_scaled(t_texture *dst, t_texture *src,
		t_scaled_draw draw)
{
	t_scaled_state	state;
	t_vector_int	dst_size;

	if (!dst || !src || draw.src_size <= 0)
		return ;
	ft_scaled_state_init(&state, src, draw);
	dst_size.x = dst->width;
	dst_size.y = dst->height;
	ft_scaled_state_clip(&state, src, dst_size);
	if (state.start_dst.x > state.end_dst.x
		|| state.start_dst.y > state.end_dst.y)
		return ;
	ft_draw_scaled_basic(dst, src, &state);
}

void	ft_draw_image_rgba_scaled_plus(t_game *game, t_texture *src,
		t_scaled_draw draw)
{
	t_scaled_state	state;
	t_vector_int	dst_size;

	if (!game || !game->render || !src || draw.src_size <= 0)
		return ;
	ft_scaled_state_init(&state, src, draw);
	dst_size.x = game->render->width;
	dst_size.y = game->render->height;
	ft_scaled_state_clip(&state, src, dst_size);
	if (state.start_dst.x > state.end_dst.x
		|| state.start_dst.y > state.end_dst.y)
		return ;
	ft_draw_scaled_mist(game, src, &state, draw.distance);
}
