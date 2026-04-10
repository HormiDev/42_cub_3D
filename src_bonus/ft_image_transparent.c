/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_transparent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 03:50:15 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static void	ft_process_image_lines(t_process_line_ctx ctx,
		t_vector_int y_range, int start_y)
{
	t_vector_int	y;

	y.x = y_range.x;
	y.y = start_y;
	if (start_y < 0)
		y.y = 0;
	while (y.x <= y_range.y)
	{
		ft_process_line(ctx, y);
		y.x++;
		y.y++;
	}
}

void	ft_draw_image_rgba(t_texture *dst, t_texture *src, int start_x,
		int start_y)
{
	t_vector_int		x_range;
	t_vector_int		y_range;
	t_vector_int		dst_start;
	t_clip_context		clip_ctx;

	ft_init_clipping(&x_range, &dst_start, src, (t_vector_int){start_x,
		start_y});
	clip_ctx = (t_clip_context){&x_range, &dst_start, dst, src};
	ft_clip_horizontal(clip_ctx, start_x);
	y_range = ft_clip_vertical(dst, src, start_y);
	if (y_range.x > y_range.y || x_range.x > x_range.y)
		return ;
	ft_process_image_lines((t_process_line_ctx){dst, src, x_range, dst_start},
		y_range, start_y);
}
