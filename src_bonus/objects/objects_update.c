/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:25 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/06 01:53:55 by ide-dieg         ###   ########.fr       */
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

static void	ft_set_alien_pos(t_game *game, t_vector2 pos)
{
    if (!game || !game->players[4].active)
        return ;
    game->players[4].position = pos;
}


static void ft_mark_player_areas(t_game *game)
{
	int	i;
    int	x;
    int	y;
    int	diagonal;

    diagonal = (int)MAX_RAY_SIZE;
    i = 0;
    while (i < game->config.n_players)
    {
        if (game->players[i].active && game->players[i].alive)
        {
            y = (int)game->players[i].position.y - diagonal;
            while (y <= (int)game->players[i].position.y + diagonal
                && y >= 0 && y < game->width_height[1])
            {
                x = (int)game->players[i].position.x - diagonal;
                while (x <= (int)game->players[i].position.x + diagonal
                    && x >= 0 && x < game->width_height[0])
                {
                    game->map_transitable_aux[y][x] = '1';
                    x++;
                }
                y++;
            }
        }
        i++;
    }
}


int ft_aviable_positions(t_game *game)
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

static int ft_get_random_position(t_game *game, int indez, t_vector2 *pos)
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
    int i; 
	int j; 
	int avaiable_count;
	int random_idx;
	t_vector2 pos;

	if(!game || !game->map_transitable || !game->map_transitable_aux)
        return ;
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
	if (avaiable_count > 0)
	{
		random_idx = ft_get_time() % avaiable_count;
        ft_get_random_position(game, random_idx, &pos);
	}
	else
	{
		random_idx = ft_get_time() % ft_aviable_positions(game);
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