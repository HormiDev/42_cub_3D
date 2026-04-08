/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:25 by username          #+#    #+#             */
/*   Updated: 2026/04/08 13:15:08 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
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
			player_dist = ft_vector_distance(alien->position, game->players[i].position);
			if (player_dist < MAX_RAY_SIZE && player_dist < distance && ft_is_player_visible(game, alien, &game->players[i], player_dist))
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
static void	ft_update_alien_state_and_speed(t_player *alien, t_player *objetive)
{
	if (objetive)
	{
		alien->state = ALIEN_CHASE;
		alien->speed = ALIEN_SPEED_ATTACK;
		alien->path_len = 0;
	}
	else
	{
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
	game->map_heatmap[(int) alien->position.y][(int) alien->position.x] = 0;
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
	ft_update_alien_state_and_speed(alien, objetive);
	ft_execute_alien_behavior(game, alien);
	ft_check_alien_collision(game);
	ft_check_game_end(game);
}

static void	ft_set_alien_pos(t_game *game, t_vector2 pos)
{
	t_player	*alien;

	alien = &game->players[4];
	alien->position.x = pos.x;
	alien->position.y = pos.y;
	alien->active = 1;
	alien->state = ALIEN_IDLE;
}

static void	ft_mark_exclusion_area(t_game *game, t_vector2 center, int radius)
{
	int	start_x;
	int	end_x;
	int	start_y;
	int	end_y;
	int	x;
	int	y;

	start_x = (int) center.x - radius;
	end_x = (int) center.x + radius;
	start_y = (int) center.y - radius;
	end_y = (int) center.y + radius;
	if (start_x < 0)
		start_x = 0;
	if (start_y < 0)
		start_y = 0;
	if (end_x >= game->width_height[0])
		end_x = game->width_height[0] - 1;
	if (end_y >= game->width_height[1])
		end_y = game->width_height[1] - 1;
	y = start_y;
	while (y <= end_y)
	{
		x = start_x;
		while (x <= end_x)
		{
			game->map_transitable_aux[y][x] = '1';
			x++;
		}
		y++;
	}
}

static void	ft_mark_player_areas(t_game *game)
{
	int	i;
	int	radius;

	radius = (int)(MAX_RAY_SIZE * 1.5);
	if (game->player && game->player->alive)
		ft_mark_exclusion_area(game, game->player->position, radius);
	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive)
			ft_mark_exclusion_area(game, game->players[i].position, radius);
		i++;
	}
	if (game->players[4].active)
		ft_mark_exclusion_area(game, game->players[4].position, (int) MAX_RAY_SIZE);
}

int	ft_aviable_positions(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map_transitable_aux[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static int	ft_get_random_position(t_game *game, int indez, t_vector2 *pos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map_transitable_aux[i][j] == '0')
			{
				if (count == indez)
				{
					pos->x = j + 0.5;
					pos->y = i + 0.5;
					return (1);
				}
				count++;
			}
			j++;
		}
		i++;
	}
	return (0);
}

/**
* @brief Respawnea el alien en una posición segura dentro del mapa transitable.
*
* Intenta encontrar un punto caminable que NO esté dentro del área de exclusión
* (MAX_RAY_SIZE) de ningún jugador. Si lo consigue, coloca el alien ahí.
* Si después de un intento no encuentra posición válida, coloca el alien en
* un punto caminable completamente aleatorio como fallback.
*
* @param game estructura del juego con el mapa y jugadores.
*/

void	ft_respawn_alien(t_game *game)
{
	int			i;
	int			j;
	int			avaiable_count;
	int			random_idx;
	long		seed;
	t_vector2	pos;

	if (!game || !game->map_transitable || !game->map_transitable_aux)
		return ;
	pos = game->players[4].position;
	i = 0;
	while (i < game->width_height[1])
	{
		j = 0;
		while (j < game->width_height[0])
		{
			game->map_transitable_aux[i][j] = game->map_transitable[i][j];
			j++;
		}
		i++;
	}
	ft_mark_player_areas(game);
	avaiable_count = ft_aviable_positions(game);
	if (avaiable_count <= 0)
	{
		i = 0;
		while (i < game->width_height[1])
		{
			j = 0;
			while (j < game->width_height[0])
			{
				game->map_transitable_aux[i][j] = game->map_transitable[i][j];
				j++;
			}
			i++;
		}
		avaiable_count = ft_aviable_positions(game);
	}
	if (avaiable_count <= 0)
		return ;
	seed = game->current_time;
	if (seed <= 0)
		seed = ft_get_time();
	random_idx = (int)(seed % avaiable_count);
	if (!ft_get_random_position(game, random_idx, &pos))
	{
		random_idx = 0;
		ft_get_random_position(game, random_idx, &pos);
	}
	ft_set_alien_pos(game, pos);
}

/**
* @brief Actualiza las distancias de render de todos los jugadores.
*/

void	ft_update_render_distances(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (game->players[i].active)
			game->players[i].render_distance = ft_vector_distance(
			game->player->position, game->players[i].position);
		i++;
	}
}
