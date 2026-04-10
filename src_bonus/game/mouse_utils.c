/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:56:43 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 02:25:35 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_mouse_menu_move(int x, int y, t_game *game)
{
	game->mouse_xy[0] = x;
	game->mouse_xy[1] = y;
	if (game->show_menu == 1)
		ft_hober_buttons(game, &game->menu);
	else if (game->show_menu == 2)
		ft_hober_buttons(game, &game->menu_settings);
	return (0);
}

void	ft_mouse_apply_rotation(t_game *game, int delta_x)
{
	if (game->config.n_players > 1)
	{
		game->players[game->kb_player].rotation.x -= delta_x * MOUSE_SENSITIVITY
			* game->delta_time;
		game->players[game->kb_player].rotation.x
			= ft_normalize_angle(game->players[game->kb_player].rotation.x);
	}
	else
	{
		game->player->rotation.x -= delta_x * MOUSE_SENSITIVITY
			* game->delta_time;
		game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
	}
}

/**
 * @brief Maneja el movimiento del ratón y actualiza la rotación del jugador.
 *
 * con las coordenadas de la ventana,
	invertimos la dirección del movimiento para una
 * experiencia de control más intuitiva.
 *
 * @param x Posición horizontal del ratón en la ventana.
 * @param y Posición vertical del ratón en la ventana (no se utiliza).
 * @param game estructura del juego.
 * @return Siempre devuelve 0 (requerido por la API de minilibx).
 */
int	ft_mouse_move(int x, int y, t_game *game)
{
	int	center_x;
	int	center_y;
	int	delta_x;

	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
	(void)y;
	if (!game->mouse_captured)
		return (ft_mouse_menu_move(x, y, game));
	if (game->kb_player < 0 || game->kb_player >= MAX_GAMEPADS)
		return (0);
	delta_x = x - center_x;
	ft_mouse_apply_rotation(game, delta_x);
	mlx_mouse_move(game->mlx, game->window, center_x, center_y);
	return (0);
}

void	ft_mouse_free(t_game *game)
{
	game->mouse_captured = 0;
	mlx_mouse_move(game->mlx, game->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT
		/ 2);
	mlx_mouse_show(game->mlx, game->window);
}
