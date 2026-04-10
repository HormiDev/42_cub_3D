/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:25 by username          #+#    #+#             */
/*   Updated: 2026/04/10 01:42:51 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 *
 * @brief Calcula la distancia mínima del alien a todos los jugadores.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @return puntero al jugador más cercano visible.
 */

static t_player	*ft_check_objetive(t_game *game, t_player *alien)
{
	double		distance;
	double		player_dist;
	int			i;
	t_player	*objetive;

	distance = 999999.0;
	objetive = 0;
	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive)
		{
			player_dist = ft_vector_distance(alien->position,
					game->players[i].position);
			if (player_dist < MAX_RAY_SIZE && player_dist < distance
				&& ft_is_player_visible(game, alien, &game->players[i],
					player_dist))
			{
				distance = player_dist;
				objetive = &game->players[i];
			}
		}
		i++;
	}
	return (objetive);
}

/**
 * @brief Actualiza el estado y velocidad del alien.
 * @param alien puntero al alien.
 * @param distance distancia al jugador más cercano.
 * @param last_state puntero al estado anterior.
 */
static void	ft_try_play_alien_spot_scream(t_game *game, t_player *alien,
		int has_objetive)
{
	static long	last_scream_time;
	long		now;

	if (!has_objetive)
	{
		alien->chase_sound_played = 0;
		return ;
	}
	if (alien->chase_sound_played)
		return ;
	now = game->current_time;
	if (now <= 0)
		now = ft_get_time();
	if (last_scream_time != 0 && ft_long_diff(last_scream_time, now) < 1200)
		return ;
	if (game->audio_manager)
		audio_manager_send(game->audio_manager, "music&sounds/alien-grito.wav");
	last_scream_time = now;
	alien->chase_sound_played = 1;
}

static void	ft_update_alien_state_and_speed(t_game *game, t_player *alien,
		t_player *objetive)
{
	if (objetive)
	{
		ft_try_play_alien_spot_scream(game, alien, 1);
		alien->state = ALIEN_CHASE;
		alien->speed = ALIEN_SPEED_ATTACK;
		alien->path_len = 0;
	}
	else
	{
		ft_try_play_alien_spot_scream(game, alien, 0);
		alien->state = ALIEN_PATROL;
		alien->speed = ALIEN_SPEED_PATROL;
	}
}

/**
 * @brief Ejecuta el comportamiento del alien según su estado.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 */

static void	ft_execute_alien_behavior(t_game *game, t_player *alien)
{
	game->map_heatmap[(int)alien->position.y][(int)alien->position.x] = 0;
	if (alien->state == ALIEN_CHASE)
		ft_chase_player(game, alien);
	else
		ft_alien_patrol_update(game, alien);
}

/**
 * @brief Actualiza el estado del alien según su distancia al jugador.
 *
 * Verifica colisiones con jugadores, actualiza el estado del alien,
 * ejecuta la lógica de persecución/patrulla y verifica fin del juego.
 */

void	ft_update_aliens(t_game *game)
{
	t_player	*alien;
	t_player	*objetive;

	if (!game || !game->players[4].active)
		return ;
	alien = &game->players[4];
	objetive = ft_check_objetive(game, alien);
	if (alien->model->last_update_time < game->current_time + 1000
		/ alien->model->n_frames)
	{
		alien->model->last_update_time = game->current_time;
		alien->model->active_frame++;
		if (alien->model->active_frame > alien->model->n_frames)
			alien->model->active_frame = 1;
	}
	ft_update_alien_state_and_speed(game, alien, objetive);
	ft_execute_alien_behavior(game, alien);
	ft_check_alien_collision(game);
	ft_check_game_end(game);
}
