#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Encuentra el jugador vivo más cercano al alien.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param closest puntero para guardar al jugador más cercano.
 * @return distancia al más cercano o -1 si no hay vivos.
 */
static double	ft_find_closest_player(t_game *game, t_player *alien, t_player **closest)
{
	double		min_dist;
	double		dist;
	int			i;

	min_dist = 999.0;
	*closest = NULL;
	if (game->player && game->player->alive)
	{
		min_dist = ft_vector_distance(alien->position, game->player->position);
		*closest = game->player;
	}
	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive)
		{
			dist = ft_vector_distance(alien->position, game->players[i].position);
			if (dist < min_dist)
			{
				min_dist = dist;
				*closest = &game->players[i];
			}
		}
		i++;
	}
	return (*closest ? min_dist : -1);
}

/**
 * @brief Verifica si el alien puede ver al jugador.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param target puntero al jugador objetivo.
 * @return 1 si distancia < alien->chase_distance, 0 si no.
 */
static int	ft_has_line_of_sight(t_game *game, t_player *alien, t_player *target)
{
	double		dist;

	if (!game || !target || !alien)
		return (0);
	dist = ft_vector_distance(alien->position, target->position);
	return (dist < alien->chase_distance);
}

/**
 * @brief Persigue al jugador en línea recta.
 * @param game estructura del juego.
 * @param alien puntero al alien a mover.
 * @param target jugador a perseguir.
 */
static void	ft_move_toward_player(t_game *game, t_player *alien, t_player *target)
{
	t_vector2	direction;
	double		norm;

	if (!target)
		return ;
	direction.x = target->position.x - alien->position.x;
	direction.y = target->position.y - alien->position.y;
	norm = ft_sqrt(direction.x * direction.x + direction.y * direction.y);
	if (norm > 0.001)
	{
		direction.x /= norm;
		direction.y /= norm;
	}
	alien->position.x += direction.x * alien->speed * game->delta_time;
	alien->position.y += direction.y * alien->speed * game->delta_time;
}

/**
 * @brief Actualiza el estado CHASE del alien.
 * @param game estructura del juego.
 * @param alien puntero al alien a actualizar.
 */
void	ft_alien_chase_update(t_game *game, t_player *alien)
{
	double		dist;
	t_player	*target;

	if (!alien || !game)
		return ;
	dist = ft_find_closest_player(game, alien, &target);
	if (dist < 0 || !target)
	{
		alien->state = ALIEN_PATROL;
		alien->path_len = 0;
		return ;
	}
	if (!ft_has_line_of_sight(game, alien, target))
	{
		alien->state = ALIEN_PATROL;
		alien->path_len = 0;
		return ;
	}
	alien->path_len = 0;
	ft_move_toward_player(game, alien, target);
}
