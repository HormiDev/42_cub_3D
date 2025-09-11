/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 17:57:25 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/09/11 17:29:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Calcula el tiempo transcurrido desde el último frame.
 * Esta función obtiene el tiempo actual y calcula la diferencia con el tiempo del último frame.
 * Luego, actualiza el tiempo del último frame y calcula el delta_time.
 * @param game Puntero a la estructura del juego que contiene el tiempo del último frame y el delta_time.
 */
void ft_calc_delta_time(t_game *game)
{
	long current_time;
	long time_diff;

	current_time = ft_get_time();
	time_diff = ft_long_diff(game->last_frame_time, current_time);
	game->delta_time = time_diff / 1000.0;
	game->last_frame_time = current_time;
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

	ft_calc_delta_time(game);
	//printf("Fps: %d\n", (int)(1 / game->delta_time));
	ft_sprintf(string_fps, "Fps: %d", (int)(1 / game->delta_time));
	ft_controls(game);
	ft_calculate_raycasts(game); 
	ft_render_3d(game);
	mlx_clear_window(game->mlx, game->window);
	if (RENDER_HEIGHT != WINDOW_HEIGHT || RENDER_WIDTH != WINDOW_WIDTH)
	{
		ft_scale_t_image_precalc(game->render, game->window_img, game);
		mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
		mlx_string_put(game->mlx, game->window, 10, 40, 0xffde87, string_fps);
	}
	else
		mlx_put_image_to_window(game->mlx, game->window, game->render->img, 0, 0);
	mlx_string_put(game->mlx, game->window, 10, 40, 0xffde87, string_fps);
	//ft_map2D(game);
	return (0);
}
