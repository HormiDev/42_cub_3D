/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:43:53 by username          #+#    #+#             */
/*   Updated: 2026/04/09 18:37:21 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
* @brief Dibuja la pantalla de victoria de los jugadores.
*
* Renderiza la imagen PANTALLA-WIN.xpm escalada como fondo con transparencia,
* y dibuja "players win" centrado.
*
* @param game estructura del juego.
*/

void	ft_draw_win_screen(t_game *game)
{
	t_vector_int	text_pos;
	int				text_len;

	ft_scale_t_image(game->screen_end_img, game->window_img);
	text_len = ft_strlen("players win");
	text_pos.x = game->window_img->width / 2 - (text_len * 6 * 8) / 2;
	text_pos.y = game->window_img->height / 2 - (game->font->height * 8) / 2;
	ft_draw_string_hud(game->window_img, game->font, "players win", &text_pos, 8);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
}

/**
* @brief Dibuja la pantalla de victoria de los jugadores.
*
* Renderiza la imagen PANTALLA-WIN.xpm escalada como fondo con transparencia,
* y dibuja "players win" centrado.
*
* @param game estructura del juego.
*/

void	ft_draw_game_over_screen(t_game *game)
{
	t_vector_int	text_pos;
	int				text_len;

	ft_scale_t_image(game->screen_alien_img, game->window_img);
	text_len = ft_strlen("Game Over");
	text_pos.x = game->window_img->width / 2 - (text_len * 6 * 8) / 2;
	text_pos.y = game->window_img->height / 4 - (game->font->height * 8) / 2;
	ft_draw_string_hud(game->window_img, game->font, "Game Over", &text_pos, 8);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
}

/**
* @brief Calcula el tiempo transcurrido desde el último frame.
* Luego, actualiza el tiempo del último frame y calcula el delta_time.
*/

int	ft_calc_delta_time(t_game *game)
{
	long	time_diff;

	game->current_time = ft_get_time();
	time_diff = ft_long_diff(game->last_frame_time, game->current_time);
	game->delta_time = time_diff / 1000.0;
	if (game->delta_time < (1.0 / (double) MAX_FPS))
		return (0);
	game->last_frame_time = game->current_time;
	return (1);
}
