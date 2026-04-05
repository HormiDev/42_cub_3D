/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:25 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/05 14:42:34 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Calcula la distancia mínima del alien a todos los jugadores.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @return distancia mínima encontrada.
 */
static double	ft_update_alien_distance(t_game *game, t_player *alien)
{
	double	distance;
	double	player_dist;
	int		i;

	distance = 999.0;
	if (game->player && game->player->alive)
		distance = ft_vector_distance(alien->position, game->player->position);
	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive)
		{
			player_dist = ft_vector_distance(alien->position, game->players[i].position);
			if (player_dist < distance)
				distance = player_dist;
		}
		i++;
	}
	return (distance);
}

/**
 * @brief Actualiza el estado y velocidad del alien.
 * @param alien puntero al alien.
 * @param distance distancia al jugador más cercano.
 * @param last_state puntero al estado anterior.
 */
static void	ft_update_alien_state_and_speed(t_player *alien, double distance,
	t_alien_state *last_state)
{
	if (distance <= alien->chase_distance)
		alien->state = ALIEN_CHASE;
	else
		alien->state = ALIEN_PATROL;
	if (alien->state != *last_state)
	{
		if (alien->state == ALIEN_CHASE)
			alien->speed = 3.5;
		else
			alien->speed = 1.5;
		*last_state = alien->state;
	}
}

/**
 * @brief Ejecuta el comportamiento del alien según su estado.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 */
static void	ft_execute_alien_behavior(t_game *game, t_player *alien)
{
	if (alien->state == ALIEN_CHASE)
		ft_alien_chase_update(game, alien);
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
	t_player			*alien;
	double				distance;
	static t_alien_state	last_state = -1;

	if (!game || !game->players[4].active)
		return ;
	alien = &game->players[4];
	distance = ft_update_alien_distance(game, alien);
	ft_update_alien_state_and_speed(alien, distance, &last_state);
	ft_execute_alien_behavior(game, alien);
	ft_check_alien_collision(game);
	ft_check_game_end(game);
}

/**
 * @brief Cuenta puntos caminables ('0') en el mapa_original.
 */
static int	ft_count_walkable_points(t_game *game)
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
			if (game->map_original[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

/**
 * @brief Obtiene la posición del n-ésimo punto caminable en map_original.
 */
static int	ft_get_walkable_point(t_game *game, int index, t_vector2 *pos)
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
			if (game->map_original[i][j] == '0')
			{
				if (count == index)
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
 * @brief Valida que un punto esté lo suficientemente lejos de todos los jugadores.
 *
 * Itera sobre todos los jugadores activos y comprueba si la distancia desde
 * la posición dada es mayor o igual a min_distance. Si algún jugador está
 * demasiado cerca, retorna 0 (inválido).
 *
 * @param game estructura del juego.
 * @param pos posición a validar.
 * @param min_distance distancia mínima requerida a los jugadores.
 * @return 1 si está lejos de todos, 0 si alguno está cerca.
 */
static int	ft_far_from_players(t_game *game, t_vector2 pos, double min_distance)
{
	int	k;

	k = 0;
	while (k < game->config.n_players)
	{
		if (ft_vector_distance(game->players[k].position, pos) < min_distance)
			return (0);
		k++;
	}
	return (1);
}

/**
 * @brief Actualiza la posición del alien y recarga su textura en el juego.
 *
 * Asigna las coordenadas nuevas al alien (índice 4 en el array de jugadores),
 * actualiza su orientación inicial a 0 radianes, marca como vivo y recarga
 * la textura desde cero para garantizar que aparezca correctamente en pantalla.
 *
 * @param game estructura del juego donde se actualiza el alien.
 * @param pos nuevas coordenadas (x, y) para el alien.
 */
static void	ft_set_alien_pos(t_game *game, t_vector2 pos)
{
	t_player	*alien;

	alien = &game->players[4];
	alien->position.x = pos.x;
	alien->position.y = pos.y;
	alien->active = 1;
	alien->state = ALIEN_IDLE;
}

/**
 * @brief Respawnea el alien en una posición segura aleatororia del mapa.
 *
 * Primero calcula cuántos puntos caminables existen. Luego intenta colocar
 * al alien a una distancia entre 4 y 10 unidades de los jugadores (rango de 
 * 'spawn seguro'). Si eso no es posible después de un intento, coloca al alien
 * en un punto caminable completamente aleatorio como fallback.
 *
 * @param game estructura del juego con el mapa y jugadores.
 */
void	ft_respawn_alien(t_game *game)
{
	int			count;
	int			random_idx;
	t_vector2	pos;
	double		min_dist;

	if (!game || !game->map_original)
		return ;
	count = ft_count_walkable_points(game);
	if (count == 0)
		return ;
	min_dist = 4.0 + (rand() % 7);
	random_idx = rand() % count;
	if (ft_get_walkable_point(game, random_idx, &pos))
	{
		if (ft_far_from_players(game, pos, min_dist))
		{
			ft_set_alien_pos(game, pos);
			return ;
		}
	}
	random_idx = rand() % count;
	if (ft_get_walkable_point(game, random_idx, &pos))
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