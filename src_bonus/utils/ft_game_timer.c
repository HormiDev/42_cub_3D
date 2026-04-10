/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game_timer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:26:17 by username          #+#    #+#             */
/*   Updated: 2026/04/10 01:14:10 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**

* @brief Construye la cadena del temporizador 
 * en formato "MM SS" desde segundos.
 *
 * Convierte `remaining` en minutos y segundos, y escribe la representación
 * en `str` usando `append_two_digits` para garantizar el ancho de dos dígitos.
 *
 * @param str Buffer donde se escribirá la cadena resultante.
 * @param remaining Segundos restantes totales.
 */

void	get_timer_string(char *str, int remaining)
{
	int	len;
	int	minutes;
	int	seconds;

	len = 0;
	minutes = remaining / 60;
	seconds = remaining % 60;
	len = append_two_digits(str, len, minutes);
	str[len++] = ' ';
	len = append_two_digits(str, len, seconds);
	str[len] = '\0';
}

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
	int				remaining;
	int				scale;
	t_vector_int	pos;

	scale = ft_get_hud_scale(viewport.y);
	if (game->game_state == GAME_PLAYERS_WIN)
	{
		pos.x = offset.x + viewport.x / 2 - (ft_strlen("players win") * 6
				* scale) / 2;
		pos.y = offset.y + viewport.y / 2 - (game->font->height * scale) / 2;
		ft_draw_string_hud(target, game->font, "players win", &pos, scale);
		return ;
	}
	remaining = ft_get_remaining(game);
	get_timer_string(str, remaining);
	pos = ft_get_timer_hud_pos(offset, viewport, scale, ft_strlen(str) * 6
			* scale);
	ft_draw_string_hud(target, game->font, str, &pos, scale);
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
