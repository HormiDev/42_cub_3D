/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/29 23:41:05 by ismherna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Dibuja la pantalla de fin de juego (GAME OVER).
 *
 * Renderiza una pantalla negra con un mensaje de derrota cuando el alien
 * ha eliminado a todos los jugadores.
 *
 * @param game estructura del juego.
 */
static void	ft_draw_game_over_screen(t_game *game)
{
	int	center_x;
	int	center_y;

	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
	
	mlx_clear_window(game->mlx, game->window);
	mlx_string_put(game->mlx, game->window, center_x - 200, center_y - 100,
		0xFFFF0000, "GAME OVER");
	mlx_string_put(game->mlx, game->window, center_x - 150, center_y,
		0xFFFFFFFF, "YOU LOST");
	mlx_string_put(game->mlx, game->window, center_x - 250, center_y + 100,
		0xFFFFFF00, "The alien has eliminated all players...");
	mlx_string_put(game->mlx, game->window, center_x - 100, center_y + 200,
		0xFF00FF00, "Press ESC to exit");
}

/**
 * @brief Calcula el tiempo transcurrido desde el último frame.
 * Esta función obtiene el tiempo actual y calcula la diferencia con el tiempo del último frame.
 * Luego, actualiza el tiempo del último frame y calcula el delta_time.
 * @param game estructura del juego que contiene el tiempo del último frame y el delta_time.
 */
int ft_calc_delta_time(t_game *game)
{
	long current_time;
	long time_diff;

	current_time = ft_get_time();
	time_diff = ft_long_diff(game->last_frame_time, current_time);
	game->delta_time = time_diff / 1000.0;
	if (game->delta_time < (1.0 / (double)MAX_FPS))
		return (0);
	game->last_frame_time = current_time;
	return (1);
}

void ft_one_player(t_game *game)
{
	ft_controls(game, 0);
	ft_update_flamethrower_cooldown(&game->actions[0], game->delta_time);
	ft_update_aliens(game);
	ft_update_doors(game);
	ft_calculate_raycasts(game); 
	ft_render_3d(game);
	ft_render_all_sprites(game);
	ft_map2D(game);
	ft_render_timer_hud(game);
	ft_render_flamethrower_hud(game, 0);
	if (game->config.render_height != WINDOW_HEIGHT || game->config.render_width != WINDOW_WIDTH)
	{
		ft_scale_t_image_precalc(game->render, game->window_img, game);
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100);
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
	}
	else
	{
		ft_draw_image_rgba(game->render, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100);
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window, game->render->img, 0, 0);
	}
}

void ft_two_players(t_game *game)
{
	int player_index;

	player_index = 0;
	while (player_index < 2)
	{
		game->player = &game->players[player_index];
		ft_controls(game, player_index);
		ft_update_flamethrower_cooldown(&game->actions[player_index], game->delta_time);
		ft_update_doors(game);
		ft_calculate_raycasts(game); 
		ft_render_3d(game);
		ft_render_all_sprites(game);
		ft_map2D(game);
		ft_render_timer_hud(game);
		ft_render_flamethrower_hud(game, player_index);
		ft_scale_t_image_precalc_two(game->render, game->window_img, game, player_index);
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2 * (player_index)));
		player_index++;
	}
	game->player = &game->players[0];
	ft_update_aliens(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
}

void ft_three_players(t_game *game)
{
	int player_index;

	player_index = 0;
	while (player_index < game->config.n_players)
	{
		game->player = &game->players[player_index];
		ft_controls(game, player_index);
		ft_update_flamethrower_cooldown(&game->actions[player_index], game->delta_time);
		ft_update_doors(game);
		ft_calculate_raycasts(game); 
		ft_render_3d(game);
		ft_render_all_sprites(game);
		ft_map2D(game);
		ft_render_timer_hud(game);
		ft_render_flamethrower_hud(game, player_index);
		ft_scale_t_image_precalc_three(game->render, game->window_img, game, player_index);
		if (player_index == 0)
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100);
		else if (player_index == 1)
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2));
		else if (player_index == 2)
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100 + (WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100);
		else
			ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100 + (WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2));
		player_index++;
	}
	game->player = &game->players[0];
	ft_update_aliens(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
}

/**
 * @brief Actualiza el estado del juego y renderiza la escena.
 * Esta función se llama en cada frame del juego. Calcula el tiempo delta,
 * maneja los movimientos del jugador, limpia la ventana, realiza raycasts
 * y renderiza la escena 3D. Finalmente, dibuja el mapa y actualiza la ventana.
 * @param param estructura del juego que contiene toda la información necesaria.
 * @return 0 para indicar que la actualización se realizó correctamente.
 */
static int	ft_should_show_door_prompt(t_game *game)
{
	t_vector_int	door_tile;
	t_door			*door;
	double			dx;
	double			dy;
	double			distance;

	if (!game || !game->player)
		return (0);
	if (!ft_raycast_door_hit(game, game->player->rotation.x, 4.0,
			&door_tile))
		return (0);
	door = ft_get_door_at(game, door_tile.x, door_tile.y);
	if (!door)
		return (0);
	dx = game->player->position.x - (door->position.x + 0.5);
	dy = game->player->position.y - (door->position.y + 0.5);
	distance = ft_sqrt(dx * dx + dy * dy);
	if (distance > door->trigger_distance)
		return (0);
	return (1);
}

int ft_update(void *param)
{
	t_game 	*game = (t_game *)param;
	char	string_fps[32];

	if (!ft_calc_delta_time(game))
		return (0);
	ft_sprintf(string_fps, "Fps: %d", (int)(1 / game->delta_time));
	ft_update_gamepad(game);
	ft_gamepad_movement(game);
	if (game->show_menu)
		ft_update_menu(game);
	else if (game->game_state == GAME_ALIEN_WIN)
	{
		ft_draw_game_over_screen(game);
	}
	else
	{
		ft_check_timer(game);
		if (game->game_state != GAME_PLAYERS_WIN)
		{
			if (game->config.n_players == 1)
				ft_one_player(game);
			else if (game->config.n_players == 2)
				ft_two_players(game);
			else
				ft_three_players(game);
		}
		mlx_string_put(game->mlx, game->window, 10, 40, 0xffde87, string_fps);
		if (ft_should_show_door_prompt(game))
			mlx_string_put(game->mlx, game->window,
				WINDOW_WIDTH / 2 - 70, WINDOW_HEIGHT - 40,
				0xFFFFFF00, "Press E or A");
		ft_render_timer_hud(game);
		ft_debug_alien(game);
	}
	return (0);
}
