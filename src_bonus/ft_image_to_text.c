/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_to_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:34 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/02 16:36:37 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Procesa una línea horizontal de la fuente y la copia al destino.
 *
 * Itera 5 píxeles a partir de `src_x` de la línea `src_y` en `src` y los
 * mezcla en `dst` en la posición `dst_x`, `dst_y`, respetando el canal alfa.
 * Si el píxel fuente es totalmente transparente (color 0x00000000) se
 * omite. Para valores intermedios de alfa se usa `ft_mix_color_alpha`.
 *
 * @param dst Textura destino donde se escriben los píxeles.
 * @param src Textura de la fuente origen.
 * @param src_x Coordenada X inicial en `src` (en píxeles).
 * @param dst_x Coordenada X inicial en `dst` (en píxeles).
 * @param dst_y Coordenada Y en `dst` donde se copiará la línea.
 * @param src_y Coordenada Y en `src` de la línea a copiar.
 */
static void	ft_font_process_line(t_texture *dst, t_texture *src,
	int src_x, t_vector_int *pos, int src_y, int scale)
{
	unsigned int	*src_ptr;
	unsigned int	*dst_ptr;
	unsigned int	src_color;
	int				x;
	int				x_scale;
	int				px;

	src_ptr = (unsigned int *)(src->img->data + src_y * src->img->size_line);
	dst_ptr = (unsigned int *)(dst->img->data + pos->y * dst->img->size_line);
	x = 0;
	px = pos->x;
	while (x < 5)
	{
		src_color = src_ptr[src_x + x];
		x_scale = 0;
		if (src_color != 0x00000000)
		{
			while (x_scale < scale)
			{
				dst_ptr[px] = src_color;
				x_scale++;
				px++;
			}
		}
		else
			px += scale;
		x++;
	}
}

/**
 * @brief Dibuja un carácter indexado desde la textura de fuente en `dst`.
 *
 * Calcula la posición de origen en `font` (carácter de 5xfont->height con
 * separación de 1 píxel) y llama a `ft_font_process_line` para cada fila.
 * Realiza comprobaciones de límites para evitar escrituras fuera del búfer.
 *
 * @param dst Textura destino.
 * @param font Textura que contiene la fuente.
 * @param idx Índice del carácter en la tabla de la fuente (0..).
 * @param dst_x Coordenada X en `dst` donde dibujar el carácter.
 * @param dst_y Coordenada Y en `dst` donde dibujar el carácter.
 */
static void	ft_draw_char(t_texture *dst, t_texture *font,
				int idx, t_vector_int *pos, int scale)
{
	int				src_x;
	int				y;
	int				i_scale;
	t_vector_int	new_pos;

	if (idx < 0 || pos->x >= dst->width || pos->y >= dst->height)
	    return ;
	if (pos->x + 5 < 0 || pos->y + font->height < 0)
	    return ;
	src_x = 1 + idx * 6;
	y = 0;
	i_scale = 0;
	new_pos.x = pos->x;
	new_pos.y = pos->y;
	while (y < font->height)
	{
		if (pos->y + y >= 0 && new_pos.y + y < dst->height)
			ft_font_process_line(dst, font, src_x, &new_pos, y, scale);
		i_scale++;
		new_pos.y++;
		if (i_scale >= scale)
		{
			i_scale = 0;
			y++;
		}
	}
}

/**
 * @brief Convierte un carácter ASCII simple a un índice de la tabla de fuente.
 *
 * Soporta letras y dígitos. Devuelve -1 para
 * caracteres no soportados (por ejemplo símbolos o espacio).
 *
 * @param c Carácter a convertir.
 * @return Índice en la tabla de la fuente, o -1 si no está soportado.
 */
static int	ft_char_to_index(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a');
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= '0' && c <= '9')
		return (26 + (c - '0'));
	return (-1);
}

/**
 * @brief Dibuja una cadena horizontal usando la textura de fuente.
 *
 * Recorre `str` y dibuja cada carácter con `ft_draw_char`, avanzando 6 píxeles
 * por carácter (5 píxeles de ancho + 1 de separación). No dibuja espacios.
 *
 * @param dst Textura destino.
 * @param font Textura de la fuente.
 * @param str Cadena NUL-terminada a dibujar.
 * @param x Coordenada X inicial en `dst`.
 * @param y Coordenada Y inicial en `dst`.
 */
void	ft_draw_string_hud(t_texture *dst, t_texture *font,
			const char *str, t_vector_int *pos, int scale)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			ft_draw_char(dst, font, ft_char_to_index(str[i]), pos, scale);
		pos->x += 6 * scale;
		i++;
	}
}