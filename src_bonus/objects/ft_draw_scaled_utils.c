/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_scaled_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:22:24 by username          #+#    #+#             */
/*   Updated: 2026/04/10 01:59:30 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_scaled_state_init(t_scaled_state *state, t_texture *src,
		t_scaled_draw draw)
{
	state->start_dst = draw.pos;
	state->end_dst.x = draw.pos.x + draw.src_size - 1;
	state->end_dst.y = draw.pos.y + draw.src_size - 1;
	state->start_src.x = 0;
	state->start_src.y = 0;
	state->src_iter.x = (float)src->width / (float)draw.src_size;
	state->src_iter.y = (float)src->height / (float)draw.src_size;
	state->src_size = draw.src_size;
}

void	ft_scaled_state_clip(t_scaled_state *state, t_texture *src,
		t_vector_int dst_size)
{
	if (state->start_dst.x < 0)
	{
		state->start_src.x = -(float)state->start_dst.x / (float)state->src_size
			* src->width;
		state->start_dst.x = 0;
	}
	if (state->start_dst.y < 0)
	{
		state->start_src.y = -(float)state->start_dst.y / (float)state->src_size
			* src->height;
		state->start_dst.y = 0;
	}
	if (state->end_dst.x >= dst_size.x)
		state->end_dst.x = dst_size.x - 1;
	if (state->end_dst.y >= dst_size.y)
		state->end_dst.y = dst_size.y - 1;
	state->start_dst_x = state->start_dst.x;
	state->start_src_x = state->start_src.x;
}

void	ft_draw_scaled_basic(t_texture *dst, t_texture *src,
		t_scaled_state *state)
{
	t_vector_int	row;

	row.y = 0;
	row.x = state->start_dst.y;
	while (row.x <= state->end_dst.y)
	{
		ft_draw_scaled_basic_row(dst, src, state, row);
		row.x++;
	}
}

void	ft_draw_scaled_basic_row(t_texture *dst, t_texture *src,
		t_scaled_state *state, t_vector_int row)
{
	t_vector_int	dst_pos;
	t_vector2		src_f;
	t_vector_int	src_pos;

	dst_pos.y = row.x;
	src_pos.y = (int)(state->start_src.y + (dst_pos.y - state->start_dst.y)
			* state->src_iter.y);
	if (src_pos.y >= src->height)
		src_pos.y = src->height - 1;
	dst_pos.x = state->start_dst_x;
	src_f.x = state->start_src_x;
	src_pos.x = (int)src_f.x;
	while (dst_pos.x <= state->end_dst.x)
	{
		if ((src->cmx[src_pos.y][src_pos.x] >> 24) != 0)
			dst->cmx[dst_pos.y][dst_pos.x] = src->cmx[src_pos.y][src_pos.x];
		dst_pos.x++;
		src_f.x += state->src_iter.x;
		src_pos.x = (int)src_f.x;
		if (src_pos.x >= src->width)
			src_pos.x = src->width - 1;
	}
}

void	ft_draw_scaled_mist(t_game *game, t_texture *src, t_scaled_state *state,
		double distance)
{
	t_scaled_draw	row_draw;

	row_draw.pos.x = 0;
	row_draw.pos.y = state->start_dst.y;
	row_draw.src_size = 0;
	row_draw.distance = distance;
	while (row_draw.pos.y <= state->end_dst.y)
	{
		ft_draw_scaled_mist_row(game, src, state, row_draw);
		row_draw.pos.y++;
	}
}
