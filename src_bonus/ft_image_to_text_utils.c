/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_to_text_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:34 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_copy_pixel_scaled(unsigned int *dst_ptr, unsigned int color,
		int *px, int scale)
{
	int	x_scale;

	x_scale = 0;
	while (x_scale < scale)
	{
		dst_ptr[*px] = color;
		x_scale++;
		(*px)++;
	}
}

void	ft_font_process_line(t_font_ctx *ctx, t_vector_int *pos, int src_y)
{
	unsigned int	*src_ptr;
	unsigned int	*dst_ptr;
	unsigned int	src_color;
	int				x;
	int				px;

	src_ptr
		= (unsigned int *)(ctx->src->img->data
			+ src_y * ctx->src->img->size_line);
	dst_ptr
		= (unsigned int *)(ctx->dst->img->data
			+ pos->y * ctx->dst->img->size_line);
	x = 0;
	px = pos->x;
	while (x < 5)
	{
		src_color = src_ptr[ctx->src_x + x];
		if (src_color > 0x00FFFFFF)
			ft_copy_pixel_scaled(dst_ptr, src_color, &px, ctx->scale);
		else
			px += ctx->scale;
		x++;
	}
}

int	ft_check_char_bounds(t_hud_draw *draw)
{
	if (draw->pos.x >= draw->target->width
		|| draw->pos.y >= draw->target->height)
		return (0);
	if (draw->pos.x + 5 < 0 || draw->pos.y + draw->target->height < 0)
		return (0);
	return (1);
}
