/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_update.c                                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/09 13:43:53 by username         #+#    #+#              */
/*   Updated: 2026/04/09 16:31:40 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>            +#+  +:+
+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/29 23:41:05 by ismherna          ###   ########.fr       */
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

static void	ft_draw_win_screen(t_game *game)
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

static void	ft_draw_game_over_screen(t_game *game)
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

void	ft_one_player(t_game *game)
{
	ft_controls(game, 0);
	ft_update_flamethrower_cooldown(&game->actions[0], game->delta_time);
	ft_update_heatmap(game);
	ft_update_aliens(game);
	ft_update_doors(game);
	ft_calculate_raycasts(game);
	ft_render_3d(game);
	ft_render_all_sprites(game);
	ft_map2d(game);
	ft_render_flamethrower_sprite(game, 0);
	if (game->config.render_height != WINDOW_HEIGHT
			|| game->config.render_width != WINDOW_WIDTH)
	{
		ft_scale_t_image_precalc(game->render, game->window_img, game);
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100,
			WINDOW_HEIGHT / 100);
		ft_render_timer_hud(game);
		ft_render_flamethrower_hud(game, 0);
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window, game->window_img->img,
			0, 0);
	}
	else
	{
		ft_draw_image_rgba(game->render, game->minimap, WINDOW_WIDTH / 100,
			WINDOW_HEIGHT / 100);
		ft_render_timer_hud(game);
		ft_render_flamethrower_hud(game, 0);
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window, game->render->img, 0,
			0);
	}
}

void	ft_two_players(t_game *game)
{
	int				player_index;
	int				offset_x;
	int				offset_y;
	t_vector_int	viewport;

	player_index = 0;
	viewport.x = game->window_img->width;
	viewport.y = game->window_img->height / 2;
	while (player_index < 2)
	{
		game->player = &game->players[player_index];
		ft_controls(game, player_index);
		ft_update_flamethrower_cooldown(&game->actions[player_index],
			game->delta_time);
		ft_update_doors(game);
		ft_calculate_raycasts(game);
		ft_render_3d(game);
		ft_render_all_sprites(game);
		ft_map2d(game);
		ft_render_flamethrower_sprite(game, player_index);
		ft_scale_t_image_precalc_two(game->render, game->window_img, game,
			player_index);
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100,
			WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2 * (player_index)));
		offset_x = 0;
		offset_y = viewport.y * player_index;
		ft_render_timer_hud_viewport(game, game->window_img,
			offset_x, offset_y, viewport);
		ft_render_flamethrower_hud_viewport(game, player_index,
			game->window_img, offset_x, offset_y, viewport);
		player_index++;
	}
	game->player = &game->players[0];
	ft_update_heatmap(game);
	ft_update_aliens(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0,
		0);
}

void	ft_three_players(t_game *game)
{
	int				player_index;
	int				offset_x;
	int				offset_y;
	t_vector_int	viewport;

	player_index = 0;
	viewport.x = game->window_img->width / 2;
	viewport.y = game->window_img->height / 2;
	while (player_index < game->config.n_players)
	{
		game->player = &game->players[player_index];
		ft_controls(game, player_index);
		ft_update_flamethrower_cooldown(&game->actions[player_index],
			game->delta_time);
		ft_update_doors(game);
		ft_calculate_raycasts(game);
		ft_render_3d(game);
		ft_render_all_sprites(game);
		ft_map2d(game);
		ft_render_flamethrower_sprite(game, player_index);
		ft_scale_t_image_precalc_three(game->render, game->window_img, game,
			player_index);
		if (player_index == 0)
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH
			/ 100, WINDOW_HEIGHT / 100);
		else if (player_index == 1)
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH
			/ 100, WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2));
		else if (player_index == 2)
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH
			/ 100 + (WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100);
		else
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH
			/ 100 + (WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT
			/ 2));
		offset_x = 0;
		offset_y = 0;
		if (player_index == 1)
			offset_y = viewport.y;
		else if (player_index == 2)
			offset_x = viewport.x;
		else if (player_index == 3)
		{
			offset_x = viewport.x;
			offset_y = viewport.y;
		}
		ft_render_timer_hud_viewport(game, game->window_img,
			offset_x, offset_y, viewport);
		ft_render_flamethrower_hud_viewport(game, player_index,
			game->window_img, offset_x, offset_y, viewport);
		player_index++;
	}
	game->player = &game->players[0];
	ft_update_heatmap(game);
	ft_update_aliens(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0,
		0);
}

/**
* @brief Actualiza el estado del juego y renderiza la escena.
* Esta función se llama en cada frame del juego. Calcula el tiempo delta,
* maneja los movimientos del jugador, limpia la ventana, realiza raycasts
* y renderiza la escena 3D. Finalmente, dibuja el mapa y actualiza la ventana.
* @param param estructura del juego que contiene toda la información necesaria.
* @return 0 para indicar que la actualización se realizó correctamente.
*/

int	ft_update(void *param)
{
	t_game	*game;
	char	string_fps[32];

	game = (t_game *) param;
	if (!ft_calc_delta_time(game))
		return (0);
	ft_snprintf(string_fps, sizeof(string_fps), "Fps: %d", (int)(1 / game->delta_time));
	//ft_update_gamepad(game);
	//ft_gamepad_handle_system_buttons(game);
	//ft_gamepad_movement(game);
	if (game->show_menu)
		ft_update_menu(game);
	else if (game->game_state == GAME_ALIEN_WIN)
		ft_draw_game_over_screen(game);
	else if (game->game_state == GAME_PLAYERS_WIN)
		ft_draw_win_screen(game);
	else
	{
		ft_check_timer(game);
		if (game->config.n_players == 1)
			ft_one_player(game);
		else if (game->config.n_players == 2)
			ft_two_players(game);
		else
			ft_three_players(game);
		mlx_string_put(game->mlx, game->window, 10, 40, 0xffde87, string_fps);
	}
	return (0);
}
