#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Busca el calor más fuerte en el heatmap (prioridad: '2' > '3' > '4').
 * 
 * OPTIMIZADO: Una sola pasada por el mapa. Guarda la posición con máxima
 * prioridad ('2' > '3' > '4'). Sin estructuras extra, eficiente O(n).
 * Si no encuentra nada, retorna (-1, -1).
 *
 * @param game estructura del juego.
 * @param pos puntero donde guardar la posición encontrada.
 * @return 1 si encontró calor, 0 si no hay rastro.
 */
static int	ft_find_hottest_tile(t_game *game, t_vector_int *pos)
{
	t_vector_int	best_pos;
	char			best_heat;
	t_vector_int	curr;

	best_heat = '0';
	best_pos.x = -1;
	best_pos.y = -1;
	curr.y = -1;
	while (++curr.y < game->width_height[1])
	{
		curr.x = -1;
		while (++curr.x < game->width_height[0])
		{
			if (game->map_original[curr.y][curr.x] >= '2'
				&& game->map_original[curr.y][curr.x] <= '4')
			{
				if (game->map_original[curr.y][curr.x] > best_heat)
				{
					best_heat = game->map_original[curr.y][curr.x];
					best_pos.x = curr.x;
					best_pos.y = curr.y;
				}
			}
		}
	}
	pos->x = best_pos.x;
	pos->y = best_pos.y;
	return (best_heat != '0');
}

/**
 * @brief Mueve el alien un paso del path hacia el objetivo.
 * 
 * Calcula vector desde posición actual al siguiente paso del path.
 * Lo normaliza y aplica velocidad constante. Si llega (dist < 0.1),
 * avanza al siguiente paso del path.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien a mover.
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
	if (dist < 0.1)
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
 * @brief Actualiza el estado PATROL del alien.
 * 
 * Solo se ejecuta cuando NO hay línea directa al jugador.
 * 1. Actualiza heatmap con posición actual del jugador.
 * 2. Si no hay path: busca calor y genera ruta con Dijkstra.
 * 3. Si tiene path: se mueve y limpia al terminar.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien.
 */
void	ft_alien_patrol_update(t_game *game, t_player *alien)
{
	t_vector_int	hottest;

	if (!alien || !game)
		return ;
	ft_update_heatmap(game, 0);
	if (alien->path_len == 0)
	{
		if (ft_find_hottest_tile(game, &hottest))
		{
			alien->last_heatmap_pos.x = hottest.x;
			alien->last_heatmap_pos.y = hottest.y;
			ft_map_dist(game, alien);
			ft_build_path(game, alien);
		}
	}
	if (alien->path_len > 0)
	{
		ft_move_along_path(game, alien);
		if (alien->curr_step >= alien->path_len)
		{
			if (alien->last_heatmap_pos.x >= 0 && alien->last_heatmap_pos.y >= 0)
				game->map_original[alien->last_heatmap_pos.y][alien->last_heatmap_pos.x] = '0';
			alien->path_len = 0;
		}
	}
}
