/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:25 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/02 19:39:19 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Actualiza el estado del alien según su distancia al jugador.
 */
void	ft_update_aliens(t_game *game)
{
	t_player	*alien;
	double		distance;

	if (!game->players[4].active)
		return ;
	alien = &game->players[4];
	distance = ft_vector_distance(game->player->position, alien->position);
	if (distance <= alien->chase_distance)
		alien->state = ALIEN_CHASE;
	else
		alien->state = ALIEN_IDLE;
}

/**
 * @brief Cuenta puntos caminables ('0') en el mapa transitable.
 *
 * Recorre todo el mapa_transitable contando cuántos puntos están marcados
 * como '0' (espacios abiertos donde se puede respawnear).
 *
 * @param game estructura del juego con el mapa transitable.
 * @return cantidad total de puntos caminables.
 */
static int	ft_count_points(t_game *game)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (game->map_transitable[i])
	{
		j = 0;
		while (game->map_transitable[i][j])
		{
			if (game->map_transitable[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

/**
 * @brief Obtiene la posición del n-ésimo punto caminable.
 *
 * Busca en el mapa_transitable el punto número 'index' que tenga valor '0'
 * y devuelve sus coordenadas (i, j) convertidas a posición del mundo (x+0.5, y+0.5).
 *
 * @param game estructura del juego.
 * @param index número del punto a buscar (0-basado).
 * @param pos puntero donde guardar las coordenadas encontradas.
 * @return 1 si encontró el punto, 0 si no existe.
 */
static int	ft_get_point(t_game *game, int index, t_vector2 *pos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (game->map_transitable[i])
	{
		j = 0;
		while (game->map_transitable[i][j])
		{
			if (game->map_transitable[i][j] == '0')
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

	if (!game || !game->map || !game->map_transitable)
		return ;
	count = ft_count_points(game);
	if (count == 0)
		return ;
	min_dist = 4.0 + (rand() % 7);
	random_idx = rand() % count;
	if (ft_get_point(game, random_idx, &pos))
	{
		if (ft_far_from_players(game, pos, min_dist))
		{
			ft_set_alien_pos(game, pos);
			return ;
		}
	}
	random_idx = rand() % count;
	if (ft_get_point(game, random_idx, &pos))
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
