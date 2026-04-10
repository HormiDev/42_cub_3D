/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:43:53 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_update_players(t_game *game)
{
	ft_check_timer(game);
	if (game->config.n_players == 1)
		ft_one_player(game);
	else if (game->config.n_players == 2)
		ft_two_players(game);
	else
		ft_three_players(game);
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
	ft_snprintf(string_fps, sizeof(string_fps),
		"Fps: %d", (int)(1 / game->delta_time));
	ft_update_gamepad(game);
	ft_gamepad_handle_system_buttons(game);
	ft_gamepad_movement(game);
	if (game->show_menu)
		ft_update_menu(game);
	else if (game->game_state == GAME_ALIEN_WIN)
		ft_draw_game_over_screen(game);
	else if (game->game_state == GAME_PLAYERS_WIN)
		ft_draw_win_screen(game);
	else
	{
		ft_update_players(game);
		mlx_string_put(game->mlx, game->window, 10, 40, 0xffde87, string_fps);
	}
	return (0);
}
