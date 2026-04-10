/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_to_text.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:34 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static void	ft_draw_char_lines(t_font_ctx *ctx, t_vector_int *pos)
{
	int				y;
	int				i_scale;
	t_vector_int	new_pos;

	y = 0;
	i_scale = 0;
	new_pos = *pos;
	while (y < ctx->src->height)
	{
		if (pos->y + y >= 0 && new_pos.y + y < ctx->dst->height)
			ft_font_process_line(ctx, &new_pos, y);
		i_scale++;
		new_pos.y++;
		if (i_scale >= ctx->scale)
		{
			i_scale = 0;
			y++;
		}
	}
}

static void	ft_draw_char(t_hud_draw *draw, int idx, t_texture *font)
{
	t_font_ctx	ctx;

	if (idx < 0 || !ft_check_char_bounds(draw))
		return ;
	ctx.dst = draw->target;
	ctx.src = font;
	ctx.scale = draw->scale;
	ctx.src_x = 1 + idx * 6;
	ft_draw_char_lines(&ctx, &draw->pos);
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

static void	ft_draw_string_loop(t_string_ctx *ctx, const char *str)
{
	t_hud_draw	draw;
	int			i;

	draw.target = ctx->dst;
	draw.scale = ctx->scale;
	draw.pos = ctx->pos;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			ft_draw_char(&draw, ft_char_to_index(str[i]), ctx->font);
		draw.pos.x += 6 * draw.scale;
		i++;
	}
	ctx->pos = draw.pos;
}

void	ft_draw_string_hud(t_texture *dst, t_texture *font,
		const char *str, t_string_ctx *ctx)
{
	ctx->dst = dst;
	ctx->font = font;
	ft_draw_string_loop(ctx, str);
}
