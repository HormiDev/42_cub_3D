/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/18 01:26:58 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Calcula el tiempo transcurrido desde el último frame.
 * Esta función obtiene el tiempo actual y calcula la diferencia con el tiempo del último frame.
 * Luego, actualiza el tiempo del último frame y calcula el delta_time.
 * @param game Puntero a la estructura del juego que contiene el tiempo del último frame y el delta_time.
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
	//printf("Fps: %d\n", (int)(1 / game->delta_time));
	ft_update_doors(game);
	ft_update_aliens(game);
	ft_calculate_raycasts(game); 
	ft_render_3d(game);
	ft_render_aliens(game);
	if (game->config.render_height != WINDOW_HEIGHT || game->config.render_width != WINDOW_WIDTH)
	{
		ft_scale_t_image_precalc(game->render, game->window_img, game);
		ft_draw_transparent_image(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100);
		//ft_scale_t_image(game->render, game->window_img);
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
	}
	else
	{
		ft_draw_transparent_image(game->render, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100);
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
		/* code */
		game->player = &game->players[player_index];
		ft_update_doors(game);
		ft_update_aliens(game);
		ft_calculate_raycasts(game); 
		ft_render_3d(game);
		ft_render_aliens(game);
		ft_map2D(game);
		//ft_printf("Player %d Fps: %d\n", player_index + 1, (int)(1 / game->delta_time));
		ft_scale_t_image_precalc_two(game->render, game->window_img, game, player_index);
		ft_draw_transparent_image(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2 * (player_index)));
		//ft_printf("Scaled image for player %d\n", player_index + 1);
		//ft_scale_t_image(game->render, game->window_img);
		player_index++;
	}
	game->player = &game->players[0];
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
}

void ft_three_players(t_game *game)
{
	int player_index;

	player_index = 0;
	while (player_index < game->config.n_players)
	{
		/* code */
		game->player = &game->players[player_index];
		ft_update_doors(game);
		ft_update_aliens(game);
		ft_calculate_raycasts(game); 
		ft_render_3d(game);
		ft_render_aliens(game);
		ft_map2D(game);
		//ft_printf("Player %d Fps: %d\n", player_index + 1, (int)(1 / game->delta_time));
		ft_scale_t_image_precalc_three(game->render, game->window_img, game, player_index);
		if (player_index == 0)
			ft_draw_transparent_image(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100);
		else if (player_index == 1)
			ft_draw_transparent_image(game->window_img, game->minimap, WINDOW_WIDTH / 100, WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2));
		else if (player_index == 2)
			ft_draw_transparent_image(game->window_img, game->minimap, WINDOW_WIDTH / 100 + (WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100);
		else
			ft_draw_transparent_image(game->window_img, game->minimap, WINDOW_WIDTH / 100 + (WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2));
		//ft_printf("Scaled image for player %d\n", player_index + 1);
		//ft_scale_t_image(game->render, game->window_img);
		player_index++;
	}
	game->player = &game->players[0];
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
}

/**
 * @brief Actualiza el estado del juego y renderiza la escena.
 * Esta función se llama en cada frame del juego. Calcula el tiempo delta,
 * maneja los movimientos del jugador, limpia la ventana, realiza raycasts
 * y renderiza la escena 3D. Finalmente, dibuja el mapa y actualiza la ventana.
 * @param param Puntero a la estructura del juego que contiene toda la información necesaria.
 * @return 0 para indicar que la actualización se realizó correctamente.
 */
int ft_update(void *param)
{
	t_game 	*game = (t_game *)param;
	char	string_fps[32];

	if (!ft_calc_delta_time(game))
		return (0);
	ft_sprintf(string_fps, "Fps: %d", (int)(1 / game->delta_time));
	ft_controls(game);
	if (game->show_menu)
		ft_update_menu(game);
	else if (game->config.n_players == 1)
		ft_one_player(game);
	else if (game->config.n_players == 2)
		ft_two_players(game);
	else
		ft_three_players(game);
	mlx_string_put(game->mlx, game->window, 10, 40, 0xffde87, string_fps);
	return (0);
}
