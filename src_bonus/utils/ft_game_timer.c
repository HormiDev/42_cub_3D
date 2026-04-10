/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:17 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_get_hud_scale(int viewport_height)
{
	int	scale;

	scale = viewport_height / (WINDOW_HEIGHT / 2);
	if (scale < 2)
		scale = 2;
	return (scale);
}

t_vector_int	ft_get_timer_hud_pos(t_vector_int offset,
		t_vector_int viewport, int scale, int text_width)
{
	t_vector_int	pos;

	pos.x = offset.x + viewport.x / 2 - text_width - (10 * scale);
	pos.y = offset.y + (10 * scale);
	return (pos);
}

void	ft_render_timer_hud_viewport(t_game *game, t_texture *target,
		t_vector_int offset, t_vector_int viewport)
{
	char			str[16];
	t_vector_int	vals;
	t_string_ctx	ctx;

	vals.y = ft_get_hud_scale(viewport.y);
	vals.x = ft_get_remaining(game);
	if (game->game_state == GAME_PLAYERS_WIN)
	{
		ctx.dst = target;
		ctx.font = game->font;
		ctx.scale = vals.y;
		ctx.pos = (t_vector_int){offset.x + viewport.x / 2
			- (ft_strlen("players win") * 6 * vals.y) / 2,
			offset.y + viewport.y / 2
			- (game->font->height * vals.y) / 2};
		ft_draw_string_hud(ctx.dst, ctx.font, "players win", &ctx);
		return ;
	}
	get_timer_string(str, vals.x);
	ctx.dst = target;
	ctx.font = game->font;
	ctx.scale = vals.y;
	ctx.pos = ft_get_timer_hud_pos(offset, viewport, vals.y,
			ft_strlen(str) * 6 * vals.y);
	ft_draw_string_hud(ctx.dst, ctx.font, str, &ctx);
}

/**
 * @brief Renderiza el HUD del temporizador en pantalla.
 *
 * Si el estado del juego es `GAME_PLAYERS_WIN`, muestra el mensaje de victoria.
 * En caso contrario obtiene el tiempo restante, construye la cadena y la dibuja
 * en la esquina superior derecha de la ventana.
 *
 * @param game Puntero al estado del juego usado para obtener render.
 */

void	ft_render_timer_hud(t_game *game)
{
	t_texture		*target;
	t_vector_int	viewport;

	target = game->render;
	if (game->config.n_players == 1
		&& (game->config.render_height != WINDOW_HEIGHT
			|| game->config.render_width != WINDOW_WIDTH))
		target = game->window_img;
	viewport.x = target->width;
	viewport.y = target->height;
	ft_render_timer_hud_viewport(game, target, (t_vector_int){0, 0}, viewport);
}
