#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Encuentra el tile del heatmap con mayor prioridad.
 * @param game estructura del juego con el mapa.
 * @param alien puntero al alien (no utilizado).
 * @param pos puntero para guardar la coordenada encontrada.
 * @return 1 si encontró calor, 0 si no.
 */
static int	ft_find_hottest_reachable_tile(t_game *game, t_player *alien, t_vector_int *pos)
{
	char	best_heat;
	int		y;
	int		x;

	(void)alien;
	best_heat = '0';
	pos->x = -1;
	pos->y = -1;
	y = -1;
	while (++y < game->width_height[1])
	{
		x = -1;
		while (++x < game->width_height[0])
		{
			char tile = game->map_heatmap[y][x];
			if (tile >= '2' && tile <= '4' && tile > best_heat)
			{
				best_heat = tile;
				pos->x = x;
				pos->y = y;
			}
		}
	}
	return (best_heat != '0');
}

/**
 * @brief Mueve el alien a lo largo de la ruta calculada.
 * 
 * Avanza hacia el siguiente waypoint del path. Cuando está "suficientemente
 * cerca" (dist < 0.5), salta automáticamente al siguiente paso sin esperar
 * precisión perfecta. Esto hace que el alien se mueva fluidamente por toda
 * la ruta calculada sin pausas entre pasos intermedios.
 *
 * @param game estructura del juego (para delta_time).
 * @param alien puntero al alien a mover (actualiza su posición).
 */
static void	ft_move_along_path(t_game *game, t_player *alien)
{
	t_vector2	target;
	t_vector2	direction;
	double		dist;
	double		norm;

	if (alien->curr_step >= alien->path_len)
		return ;
	target.x = alien->path[alien->curr_step].x + 0.5;
	target.y = alien->path[alien->curr_step].y + 0.5;
	direction.x = target.x - alien->position.x;
	direction.y = target.y - alien->position.y;
	dist = ft_vector_distance(alien->position, target);
	if (dist < 0.5)
	{
		alien->curr_step++;
		return ;
	}
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
 * @brief Maneja el timeout del retry timer.
 * @param retry_timer puntero al timer.
 * @param last_goal puntero al último objetivo.
 */
static void	ft_patrol_update_retry_timer(double *retry_timer, t_vector_int *last_goal)
{
	*retry_timer += 0.016;
	if (*retry_timer >= 5.0)
	{
		*retry_timer = 0.0;
		last_goal->x = -1;
		last_goal->y = -1;
	}
}

/**
 * @brief Busca nueva ruta si el objetivo cambió.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param goal coordenada objetivo.
 * @param last_goal último objetivo.
 */
static void	ft_patrol_search_path(t_game *game, t_player *alien,
	t_vector_int goal, t_vector_int *last_goal)
{
	t_vector_int	start;

	if (goal.x == last_goal->x && goal.y == last_goal->y)
		return ;
	*last_goal = goal;
	start.x = (int)alien->position.x;
	start.y = (int)alien->position.y;
	ft_bfs_path(game, start, goal, alien->path, &alien->path_len);
}

/**
 * @brief Busca objetivo y calcula ruta si no hay path.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param last_goal puntero al último objetivo.
 */
static void	ft_patrol_find_and_search_goal(t_game *game, t_player *alien,
	t_vector_int *last_goal)
{
	t_vector_int	goal;

	if (alien->path_len != 0)
		return ;
	ft_update_heatmap(game);
	if (!ft_find_hottest_reachable_tile(game, alien, &goal))
		return ;
	ft_patrol_search_path(game, alien, goal, last_goal);
}

/**
 * @brief Mueve el alien y limpia cuando termina.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param last_goal puntero al último objetivo.
 */
static void	ft_patrol_move_and_cleanup(t_game *game, t_player *alien,
	t_vector_int *last_goal)
{
	if (alien->path_len == 0)
		return ;
	ft_move_along_path(game, alien);
	if (alien->curr_step >= alien->path_len)
	{
		alien->path_len = 0;
		alien->curr_step = 0;
		last_goal->x = -1;
		last_goal->y = -1;
	}
}

/**
 * @brief Actualiza el estado PATROL del alien (búsqueda de objetivos).
 * @param game estructura del juego.
 * @param alien puntero al alien a actualizar.
 */
void	ft_alien_patrol_update(t_game *game, t_player *alien)
{
	static t_vector_int	last_goal = {-1, -1};
	static double		retry_timer = 0.0;

	if (!alien || !game)
		return ;
	ft_patrol_update_retry_timer(&retry_timer, &last_goal);
	ft_patrol_find_and_search_goal(game, alien, &last_goal);
	ft_patrol_move_and_cleanup(game, alien, &last_goal);
}
