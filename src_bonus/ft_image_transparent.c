/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_transparent.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/12 00:00:00 by ide-dieg         ###   ########.fr       */
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
	return (*(unsigned int *)pixel);
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

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->data + (y * img->size_line + x * (img->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

/**
 * @brief Crea un color en formato ARGB a partir de componentes individuales.
 * 
 * Combina los valores de Alpha, Red, Green y Blue en un solo entero de 32 bits
 * usando desplazamiento de bits.
 * 
 * @param a Componente Alpha (0-255).
 * @param r Componente Red (0-255).
 * @param g Componente Green (0-255).
 * @param b Componente Blue (0-255).
 * @return Color combinado en formato ARGB (unsigned int).
 */
static unsigned int	ft_create_argb(int a, int r, int g, int b)
{
	return ((a << 24) | (r << 16) | (g << 8) | b);
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
static void	ft_blend_alpha(t_img *dst, unsigned int src_color,
				int dst_x, int dst_y)
{
	unsigned int	dst_color;
	int				alpha;
	double			factor;
	int				components[6];
	unsigned int	final_color;

	dst_color = ft_get_pixel_color(dst, dst_x, dst_y);
	alpha = (src_color >> 24) & 0xFF;
	components[0] = (src_color >> 16) & 0xFF;
	components[1] = (src_color >> 8) & 0xFF;
	components[2] = src_color & 0xFF;
	components[3] = (dst_color >> 16) & 0xFF;
	components[4] = (dst_color >> 8) & 0xFF;
	components[5] = dst_color & 0xFF;
	factor = alpha / 255.0;
	components[0] = (int)(components[0] * factor
			+ components[3] * (1.0 - factor));
	components[1] = (int)(components[1] * factor
			+ components[4] * (1.0 - factor));
	components[2] = (int)(components[2] * factor
			+ components[5] * (1.0 - factor));
	final_color = ft_create_argb(255, components[0],
			components[1], components[2]);
	ft_put_pixel_color(dst, dst_x, dst_y, final_color);
}

/**
 * @brief Procesa un pixel individual para renderizado con transparencia.
 * 
 * Calcula las coordenadas de destino, obtiene el color del pixel de origen
 * y decide si copiar directamente (alpha = 255), ignorar (alpha = 0) o
 * aplicar alpha blending (alpha entre 1-254).
 * 
 * @param dst Puntero a la textura de destino.
 * @param src Puntero a la textura de origen.
 * @param x Coordenada X en la imagen de origen.
 * @param y Coordenada Y en la imagen de origen.
 * @param start Array con coordenadas de inicio [start_x, start_y].
 */
static void	ft_process_pixel(t_texture *dst, t_texture *src,
				int x, int y, int start[2])
{
	int				dst_xy[2];
	unsigned int	src_color;
	int				alpha;

	dst_xy[0] = start[0] + x;
	dst_xy[1] = start[1] + y;
	if (dst_xy[0] >= 0 && dst_xy[0] < dst->width
		&& dst_xy[1] >= 0 && dst_xy[1] < dst->height)
	{
		src_color = ft_get_pixel_color(src->img, x, y);
		alpha = (src_color >> 24) & 0xFF;
		if (alpha == 255)
			ft_put_pixel_color(dst->img, dst_xy[0], dst_xy[1], src_color);
		else if (alpha != 0)
			ft_blend_alpha(dst->img, src_color, dst_xy[0], dst_xy[1]);
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
	int	x;
	int	y;
	int	start[2];

	start[0] = start_x;
	start[1] = start_y;
	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			ft_process_pixel(dst, src, x, y, start);
			x++;
		}
		y++;
	}
}
