/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_image_scaled.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 01:22:24 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/01 21:32:41 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Dibuja una imagen con transparencia sobre otra imagen.
 * 
 * @param dst Textura destino donde se dibujara.
 * @param src Textura origen con canal alpha.
 * @param start_x Coordenada X inicial en destino.
 * @param start_y Coordenada Y inicial en destino.
 */
void	ft_draw_image_rgba_scaled(t_texture *dst, t_texture *src,
			int pos_x, int pos_y, int src_size)
{
	t_vector_int	start_dst;
	t_vector_int	end_dst;
	t_vector2		start_src;
	t_vector_int	end_src;


	start_dst.x = pos_x;
	start_dst.y = pos_y;
	end_dst.x = start_dst.x + src_size - 1;
	end_dst.y = start_dst.y + src_size - 1;

	if (start_dst.x >= 0)
		start_src.x = 0;
	else
	{
		start_src.x = -(float)start_dst.x / (float)src_size * src->width;
		start_dst.x = 0;
	}
	if (start_dst.y >= 0)
		start_src.y = 0;
	else
	{
		start_src.y = -(float)start_dst.y / (float)src_size * src->height;
		start_dst.y = 0;
	}
	if (end_dst.x < dst->width)
		end_src.x = src->width - 1;
	else
	{
		end_src.x = -((end_dst.x - dst->width) / src_size * src->width) + src->width;
		end_dst.x = dst->width - 1;
	}
	if (end_dst.y < dst->height)
		end_src.y = src->height - 1;
	else
	{
		end_src.y = -((end_dst.y - dst->height) / src_size * src->height) + src->height;
		end_dst.y = dst->height - 1;
	}

	int tmp_start_dst_x;
	(void)end_src;
	tmp_start_dst_x = start_dst.x;
	float tmp_start_src_x;
	tmp_start_src_x = start_src.x;
	t_vector_int src_pos;
	t_vector2 src_iter;
	//int	tmp_start_dst_y;
	//tmp_start_dst_y = start_dst.y;

	src_pos.y = (int)start_src.y;

	src_iter.x = (float)src->width / (float)src_size;
	src_iter.y = (float)src->height / (float)src_size;

	while (start_dst.y <= end_dst.y)
	{
		start_dst.x = tmp_start_dst_x;
		start_src.x = tmp_start_src_x;
		src_pos.x = start_src.x;
		while (start_dst.x <= end_dst.x)
		{	if (src->colors_matrix[src_pos.y][src_pos.x] << 24)
				dst->colors_matrix[start_dst.y][start_dst.x] = src->colors_matrix[src_pos.y][src_pos.x];
			start_dst.x++;
			start_src.x += src_iter.x;
			//start_src.x = (float)src->width / (float)src_size * (float)(start_dst.x - tmp_start_dst_x);
			src_pos.x = (int)start_src.x;
			if (src_pos.x >= src->width)
				src_pos.x = src->width - 1;
		}
		start_dst.y++;
		start_src.y += src_iter.y;
		//start_src.y = (float)src->height / (float)src_size * (float)(start_dst.y - tmp_start_dst_y);
		src_pos.y = (int)start_src.y;
		if (src_pos.y >= src->height)
			src_pos.y = src->height - 1;
	}
}


void	ft_draw_image_rgba_scaled_plus(t_texture *dst, t_texture *src,
			int pos_x, int pos_y, int src_size, double distance)
{
	t_vector_int	start_dst;
	t_vector_int	end_dst;
	t_vector2		start_src;
	t_vector_int	end_src;


	start_dst.x = pos_x;
	start_dst.y = pos_y;
	end_dst.x = start_dst.x + src_size - 1;
	end_dst.y = start_dst.y + src_size - 1;

	if (start_dst.x >= 0)
		start_src.x = 0;
	else
	{
		start_src.x = -(float)start_dst.x / (float)src_size * src->width;
		start_dst.x = 0;
	}
	if (start_dst.y >= 0)
		start_src.y = 0;
	else
	{
		start_src.y = -(float)start_dst.y / (float)src_size * src->height;
		start_dst.y = 0;
	}
	if (end_dst.x < dst->width)
		end_src.x = src->width - 1;
	else
	{
		end_src.x = -((end_dst.x - dst->width) / src_size * src->width) + src->width;
		end_dst.x = dst->width - 1;
	}
	if (end_dst.y < dst->height)
		end_src.y = src->height - 1;
	else
	{
		end_src.y = -((end_dst.y - dst->height) / src_size * src->height) + src->height;
		end_dst.y = dst->height - 1;
	}

	int tmp_start_dst_x;
	(void)end_src;
	tmp_start_dst_x = start_dst.x;
	float tmp_start_src_x;
	tmp_start_src_x = start_src.x;
	t_vector_int src_pos;
	t_vector2 src_iter;
	//int	tmp_start_dst_y;
	//tmp_start_dst_y = start_dst.y;
	unsigned int mist_color = MIST_COLOR;
	int mist_mix = 255 * distance / MAX_RAY_SIZE;

	src_pos.y = (int)start_src.y;

	src_iter.x = (float)src->width / (float)src_size;
	src_iter.y = (float)src->height / (float)src_size;

	while (start_dst.y <= end_dst.y)
	{
		start_dst.x = tmp_start_dst_x;
		start_src.x = tmp_start_src_x;
		src_pos.x = start_src.x;
		while (start_dst.x <= end_dst.x)
		{	if (src->colors_matrix[src_pos.y][src_pos.x] << 24)
			{
				dst->colors_matrix[start_dst.y][start_dst.x] = src->colors_matrix[src_pos.y][src_pos.x];
				ft_mix_color_alpha(&dst->colors_matrix[start_dst.y][start_dst.x], &mist_color, mist_mix);
			}
			start_dst.x++;
			start_src.x += src_iter.x;
			//start_src.x = (float)src->width / (float)src_size * (float)(start_dst.x - tmp_start_dst_x);
			src_pos.x = (int)start_src.x;
			if (src_pos.x >= src->width)
				src_pos.x = src->width - 1;
		}
		start_dst.y++;
		start_src.y += src_iter.y;
		//start_src.y = (float)src->height / (float)src_size * (float)(start_dst.y - tmp_start_dst_y);
		src_pos.y = (int)start_src.y;
		if (src_pos.y >= src->height)
			src_pos.y = src->height - 1;
	}
}