/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_transparent_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 03:50:41 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_init_clipping(t_vector_int *src_range, t_vector_int *dst_start,
		t_texture *src, t_vector_int start)
{
	src_range->x = 0;
	src_range->y = src->width - 1;
	dst_start->x = start.x;
	dst_start->y = start.y;
}

void	ft_clip_horizontal(t_clip_context ctx, int start_x)
{
	if (start_x < 0)
	{
		ctx.src_range->x = -start_x;
		ctx.dst_start->x = 0;
	}
	if (start_x + ctx.src->width > ctx.dst->width)
		ctx.src_range->y = ctx.dst->width - start_x - 1;
}

t_vector_int	ft_clip_vertical(t_texture *dst, t_texture *src, int start_y)
{
	t_vector_int	y_range;

	y_range.x = 0;
	y_range.y = src->height - 1;
	if (start_y < 0)
		y_range.x = -start_y;
	if (start_y + src->height > dst->height)
		y_range.y = dst->height - start_y - 1;
	return (y_range);
}

void	ft_blend_pixel(unsigned int *dst_ptr, unsigned int src_color, int alpha,
		t_vector_int pos)
{
	unsigned int	dst_color;

	if (alpha == 255)
		dst_ptr[pos.y] = src_color;
	else if (alpha > 0)
	{
		dst_color = dst_ptr[pos.y];
		ft_mix_rgba(&dst_color, &src_color, alpha);
		dst_ptr[pos.y] = dst_color;
	}
}

void	ft_process_line(t_process_line_ctx ctx, t_vector_int y)
{
	unsigned int	*src_ptr;
	unsigned int	*dst_ptr;
	t_vector_int	pos;
	unsigned int	src_color;
	int				alpha;

	src_ptr = (unsigned int *)(ctx.src->img->data + y.x
			* ctx.src->img->size_line);
	dst_ptr = (unsigned int *)(ctx.dst->img->data + y.y
			* ctx.dst->img->size_line);
	pos.x = ctx.x_range.x;
	pos.y = ctx.dst_start.x;
	while (pos.x <= ctx.x_range.y)
	{
		src_color = src_ptr[pos.x];
		if ((src_color & 0xFFFFFF) != 0xFFFFFF && src_color != 0x00000000)
		{
			alpha = (src_color >> 24) & 0xFF;
			if (alpha == 0)
				alpha = 255;
			ft_blend_pixel(dst_ptr, src_color, alpha, pos);
		}
		pos.x++;
		pos.y++;
	}
}
