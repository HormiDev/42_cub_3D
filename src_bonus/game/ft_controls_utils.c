/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_controls_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:01 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:14:23 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
* @brief Maneja el movimiento del jugador basado en las teclas presionadas.
*
* Esta función estática procesa las entradas de movimiento (adelante, atrás,
izquierda, derecha)
* y determina la dirección y velocidad de movimiento.
*
* @param game estructura del juego.
* @param move_speed Velocidad de movimiento calculada.
*/
int	ft_handle_player_movement(t_game *game, double move_speed, int player_index)
{
	int					moving;
	t_player_actions	*actions;

	actions = &game->actions[player_index];
	moving = ft_move_player_front(game, actions, move_speed, player_index);
	moving |= ft_move_player_back(game, actions, move_speed, player_index);
	moving |= ft_move_player_strafe(game, actions, move_speed, player_index);
	return (moving);
}

int	ft_move_player_front(t_game *game, t_player_actions *actions,
		double move_speed, int player_index)
{
	if (!actions->front || actions->back)
		return (0);
	if (actions->left && !actions->right)
		ft_move_direction(game, game->player->rotation.x + 45, move_speed,
			player_index);
	else if (actions->right && !actions->left)
		ft_move_direction(game, game->player->rotation.x - 45, move_speed,
			player_index);
	else
		ft_move_direction(game, game->player->rotation.x, move_speed,
			player_index);
	return (1);
}

int	ft_move_player_back(t_game *game, t_player_actions *actions,
		double move_speed, int player_index)
{
	if (!actions->back || actions->front)
		return (0);
	if (actions->left && !actions->right)
		ft_move_direction(game, game->player->rotation.x + 115, move_speed,
			player_index);
	else if (actions->right && !actions->left)
		ft_move_direction(game, game->player->rotation.x - 115, move_speed,
			player_index);
	else
		ft_move_direction(game, game->player->rotation.x + 180, move_speed,
			player_index);
	return (1);
}

int	ft_move_player_strafe(t_game *game, t_player_actions *actions,
		double move_speed, int player_index)
{
	if (actions->left && !actions->front && !actions->back)
	{
		ft_move_direction(game, game->player->rotation.x + 90, move_speed,
			player_index);
		return (1);
	}
	if (actions->right && !actions->front && !actions->back)
	{
		ft_move_direction(game, game->player->rotation.x - 90, move_speed,
			player_index);
		return (1);
	}
	return (0);
}

/**
 * @brief Maneja la rotación del jugador.
 *
 * Esta función estática procesa las entradas de rotación (izquierda, derecha)
 * y actualiza la rotación del jugador con normalización de ángulos.
 *
 * @param game estructura del juego.
 */

void	ft_handle_player_rotation(t_game *game, int player_index)
{
	t_player_actions	*actions;

	actions = &game->actions[player_index];
	if (actions->rotate_left)
	{
		game->player->rotation.x += ROTATION_SPEED * game->delta_time;
		game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
	}
	if (actions->rotate_right)
	{
		game->player->rotation.x -= ROTATION_SPEED * game->delta_time;
		game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
	}
}
