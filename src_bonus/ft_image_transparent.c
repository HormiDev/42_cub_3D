/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_transparent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/19 23:57:33 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Inicializa los rangos de clipping con valores por defecto.
 * 
 * @param src_range Rango visible en origen.
 * @param dst_start Posicion inicial en destino.
 * @param src Textura origen.
 * @param start Posicion inicial solicitada.
 */
static void	ft_init_clipping(t_vector_int *src_range, t_vector_int *dst_start,
		t_texture *src, t_vector_int start)
{
	src_range->x = 0;
	src_range->y = src->width - 1;
	dst_start->x = start.x;
	dst_start->y = start.y;
}

/**
 * @brief Aplica clipping horizontal.
 * 
 * @param src_range Rango visible en origen (x=inicio, y=fin).
 * @param dst_start Posicion inicial en destino.
 * @param dst Textura destino.
 * @param src Textura origen.
 * @param start_x Posicion X inicial solicitada.
 */
static void	ft_clip_horizontal(t_vector_int *src_range,
		t_vector_int *dst_start, t_texture *dst, t_texture *src, int start_x)
{
	if (start_x < 0)
	{
		src_range->x = -start_x;
		dst_start->x = 0;
	}
	if (start_x + src->width > dst->width)
		src_range->y = dst->width - start_x - 1;
}

/**
 * @brief Aplica clipping vertical y devuelve rango Y visible.
 * 
 * @param dst Textura destino.
 * @param src Textura origen.
 * @param start_y Posicion Y inicial en destino.
 * @return t_vector_int Rango Y visible (x=inicio, y=fin) en origen.
 */
static t_vector_int	ft_clip_vertical(t_texture *dst,
		t_texture *src, int start_y)
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

/**
 * @brief Mezcla un pixel con alpha blending.
 * 
 * @param dst_ptr Puntero a pixel destino.
 * @param src_color Color origen.
 * @param alpha Valor alpha (0-255).
 * @param pos Posicion del pixel.
 */
static void	ft_blend_pixel(unsigned int *dst_ptr, unsigned int src_color,
		int alpha, t_vector_int pos)
{
	unsigned int	dst_color;

	if (alpha == 255)
		dst_ptr[pos.y] = src_color;
	else if (alpha > 0)
	{
		dst_color = dst_ptr[pos.y];
		ft_mix_color_alpha(&dst_color, &src_color, alpha);
		dst_ptr[pos.y] = dst_color;
	}
}

/**
 * @brief Procesa una linea de imagen con transparencia.
 * 
 * @param dst Textura destino.
 * @param src Textura origen.
 * @param x_range Rango X visible (x=inicio, y=fin).
 * @param dst_start Posicion inicial en destino.
 * @param y Coordenadas Y (x=origen, y=destino).
 */
static void	ft_process_line(t_texture *dst, t_texture *src,
		t_vector_int x_range, t_vector_int dst_start, t_vector_int y)
{
	unsigned int	*src_ptr;
	unsigned int	*dst_ptr;
	t_vector_int	pos;
	unsigned int	src_color;
	int				alpha;

	src_ptr = (unsigned int *)(src->img->data + y.x * src->img->size_line);
	dst_ptr = (unsigned int *)(dst->img->data + y.y * dst->img->size_line);
	pos.x = x_range.x;
	pos.y = dst_start.x;
	while (pos.x <= x_range.y)
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

/**
 * @brief Dibuja una imagen con transparencia sobre otra imagen.
 * 
 * @param dst Textura destino donde se dibujara.
 * @param src Textura origen con canal alpha.
 * @param start_x Coordenada X inicial en destino.
 * @param start_y Coordenada Y inicial en destino.
 */
void	ft_draw_image_rgba(t_texture *dst, t_texture *src,
			int start_x, int start_y)
{
	t_vector_int	x_range;
	t_vector_int	y_range;
	t_vector_int	dst_start;
	t_vector_int	y;

	ft_init_clipping(&x_range, &dst_start, src,
		(t_vector_int){start_x, start_y});
	ft_clip_horizontal(&x_range, &dst_start, dst, src, start_x);
	y_range = ft_clip_vertical(dst, src, start_y);
	if (y_range.x > y_range.y || x_range.x > x_range.y)
		return;
	y.x = y_range.x;
	y.y = start_y;
	if (start_y < 0)
		y.y = 0;
	while (y.x <= y_range.y)
	{
		ft_process_line(dst, src, x_range, dst_start, y);
		y.x++;
		y.y++;
	}
}
