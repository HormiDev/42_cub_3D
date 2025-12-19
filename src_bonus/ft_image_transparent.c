/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_transparent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/18 22:27:04 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Obtiene el color de un pixel en las coordenadas especificadas.
 * 
 * Calcula la direccion de memoria del pixel en la imagen usando las
 * coordenadas (x, y) y retorna el valor del color almacenado.
 * 
 * @param img Puntero a la estructura de imagen de MLX.
 * @param x Coordenada X del pixel.
 * @param y Coordenada Y del pixel.
 * @return Color del pixel en formato ARGB (unsigned int).
 */
static unsigned int	ft_get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;

	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	if (img->bpp == 32)
		return (*(unsigned int *)pixel);
	/* fallback: read bytes manually (assume little-endian) */
	{
		unsigned char *p = (unsigned char *)pixel;
		unsigned int c = 0;
		int bytes = img->bpp / 8;
		int i = 0;
		while (i < bytes && i < 4)
		{
			c |= ((unsigned int)p[i]) << (i * 8);
			i++;
		}
		return c;
	}
}

/**
 * @brief Establece el color de un pixel en las coordenadas especificadas.
 * 
 * Verifica que las coordenadas esten dentro de los limites de la imagen
 * y escribe el color en la posicion de memoria correspondiente.
 * 
 * @param img Puntero a la estructura de imagen de MLX.
 * @param x Coordenada X del pixel.
 * @param y Coordenada Y del pixel.
 * @param color Color a establecer en formato ARGB (unsigned int).
 */
static void	ft_put_pixel_color(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;
	pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
	if (img->bpp == 32)
	{
		*(unsigned int *)pixel = color;
		return;
	}
	{
		unsigned char *p = (unsigned char *)pixel;
		int bytes = img->bpp / 8;
		int i = 0;
		while (i < bytes && i < 4)
		{
			p[i] = (color >> (i * 8)) & 0xFF;
			i++;
		}
	}
}

/**
 * @brief Aplica alpha blending entre dos colores.
 * 
 * Mezcla el color de origen (src_color) con el color de destino usando
 * la formula de alpha blending: resultado = src * alpha + dst * (1 - alpha).
 * El color resultante se escribe en la imagen de destino.
 * 
 * @param dst Puntero a la imagen de destino.
 * @param src_color Color de origen con canal alpha en formato ARGB.
 * @param dst_x Coordenada X en la imagen de destino.
 * @param dst_y Coordenada Y en la imagen de destino.
 */
static void ft_blend_alpha(t_img *dst, unsigned int src_color,
                           int dst_x, int dst_y)
{
    unsigned int	dst_color;
	int				alpha; 

    dst_color = ft_get_pixel_color(dst, dst_x, dst_y);
    alpha = (src_color >> 24) & 0xFF;
    if (alpha == 0)
        return;
    if (alpha == 255)
    {
        ft_put_pixel_color(dst, dst_x, dst_y, src_color);
        return;
    }
    ft_mix_color_alpha(&dst_color, &src_color, alpha);
    ft_put_pixel_color(dst, dst_x, dst_y, dst_color);
}

/**
 * @brief Calcula el rango visible de pixeles en una fila.
 * 
 * Determina las coordenadas de origen y destino visibles despues de clipping.
 * 
 * @param sx0 Puntero a inicio X en origen.
 * @param sx1 Puntero a fin X en origen.
 * @param dx0 Puntero a inicio X en destino.
 * @param dst Puntero a textura destino.
 * @param src Puntero a textura origen.
 * @param dst_start_x Inicio X en destino.
 * @param dst_y Y en destino.
 */
static void	ft_compute_visible_range(int *sx0, int *sx1, int *dx0,
		t_texture *dst, t_texture *src, int dst_start_x, int dst_y)
{
	int	src_w;
	int	dst_w;
	int	dx1;

	src_w = src->width;
	dst_w = dst->width;
	*sx0 = 0;
	*sx1 = src_w - 1;
	*dx0 = dst_start_x;
	dx1 = dst_start_x + src_w - 1;
	if (dst_y < 0 || dst_y >= dst->height)
	{
		*sx0 = src_w;
		*sx1 = -1;
		return;
	}
	if (dx1 < 0 || *dx0 >= dst_w)
	{
		*sx0 = src_w;
		*sx1 = -1;
		return;
	}
	if (*dx0 < 0)
	{
		*sx0 = -*dx0;
		*dx0 = 0;
	}
	if (dx1 >= dst_w)
		*sx1 -= (dx1 - (dst_w - 1));
}

/**
 * @brief Procesa una fila visible usando iteradores.
 * 
 * Itera sobre los pixeles visibles, aplicando transparencia.
 * 
 * @param dst Puntero a textura destino.
 * @param src Puntero a textura origen.
 * @param sx0 Inicio X en origen.
 * @param sx1 Fin X en origen.
 * @param dx0 Inicio X en destino.
 * @param dst_y Y en destino.
 * @param src_y Y en origen.
 */
static void	ft_process_visible_row(t_texture *dst, t_texture *src,
		int sx0, int sx1, int dx0, int dst_y, int src_y)
{
	int				i;
	int				dst_x;
	unsigned int	src_color;
	int				alpha;

	i = sx0;
	dst_x = dx0;
	while (i <= sx1)
	{
		src_color = ft_get_pixel_color(src->img, i, src_y);
		if ((src_color & 0xFFFFFF) == 0xFFFFFF)
		{
			i++;
			dst_x++;
			continue;
		}
		alpha = (src_color >> 24) & 0xFF;
		if (alpha == 0)
		{
			i++;
			dst_x++;
			continue;
		}
		if (alpha == 255)
			ft_put_pixel_color(dst->img, dst_x, dst_y, src_color);
		else
			ft_blend_alpha(dst->img, src_color, dst_x, dst_y);
		i++;
		dst_x++;
	}
}

/**
 * @brief Dibuja una imagen con transparencia sobre otra imagen.
 * 
 * Recorre todos los pixeles de la imagen de origen y los dibuja sobre
 * la imagen de destino comenzando en las coordenadas (start_x, start_y).
 * Respeta el canal alpha de cada pixel, permitiendo transparencia total,
 * opacidad completa o semi-transparencia con alpha blending.
 * 
 * @param dst Puntero a la textura de destino donde se dibujara.
 * @param src Puntero a la textura de origen con canal alpha.
 * @param start_x Coordenada X inicial en la imagen de destino.
 * @param start_y Coordenada Y inicial en la imagen de destino.
 */
void	ft_draw_transparent_image(t_texture *dst, t_texture *src,
			int start_x, int start_y)
{
	int	y;
	int	sx0;
	int	sx1;
	int	dx0;

	y = 0;
	while (y < src->height)
	{
		ft_compute_visible_range(&sx0, &sx1, &dx0, dst, src, start_x, start_y + y);
		if (sx0 <= sx1)
			ft_process_visible_row(dst, src, sx0, sx1, dx0, start_y + y, y);
		y++;
	}
}
