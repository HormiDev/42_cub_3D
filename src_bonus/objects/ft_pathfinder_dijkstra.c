#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Verifica si un tile es transitable (no es pared).
 * 
 * @param game estructura del juego.
 * @param tx posición X en tiles.
 * @param ty posición Y en tiles.
 * @return 1 si es transitable, 0 si es pared o fuera de límites.
 */
static int	ft_is_walkable(t_game *game, int tx, int ty)
{
	if (tx < 0 || tx >= game->width_height[0])
		return (0);
	if (ty < 0 || ty >= game->width_height[1])
		return (0);
	return (game->map_original[ty][tx] != '1');
}

/**
 * @brief Inicializa la matriz de distancias.
 * 
 * Marca todas las casillas con -1 (sin visitar). Los puntos de calor ('2','3','4')
 * se marcan con 0 como punto de partida para el wavefront.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien.
 */
static void	ft_init_dist_matrix(t_game *game, t_player *alien)
{
	t_vector_int	pos;

	pos.y = -1;
	while (++pos.y < game->width_height[1])
	{
		pos.x = -1;
		while (++pos.x < game->width_height[0])
		{
			alien->dist[pos.y][pos.x] = -1;
			if (game->map_original[pos.y][pos.x] >= '2' && game->map_original[pos.y][pos.x] <= '4')
				alien->dist[pos.y][pos.x] = 0;
		}
	}
}

/**
 * @brief Propaga distancias usando wavefront iterativo.
 * 
 * Itera sobre el mapa: para cada casilla con distancia conocida, expande a sus
 * 4 vecinos (arriba, abajo, izq, der). Si el vecino no está visitado (-1),
 * lo marca con dist+1. Repite hasta que no haya cambios.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien.
 */
static void	ft_propagate_distances(t_game *game, t_player *alien)
{
	const int	dx[4] = {1, -1, 0, 0};
	const int	dy[4] = {0, 0, 1, -1};
	t_vector_int	pos;
	int			changed;
	int			n;

	changed = 1;
	while (changed)
	{
		changed = 0;
		pos.y = -1;
		while (++pos.y < game->width_height[1])
		{
			pos.x = -1;
			while (++pos.x < game->width_height[0])
			{
				if (alien->dist[pos.y][pos.x] >= 0 && ft_is_walkable(game, pos.x, pos.y))
				{
					n = -1;
					while (++n < 4)
					{
						if (ft_is_walkable(game, pos.x + dx[n], pos.y + dy[n]))
						{
							if (alien->dist[pos.y + dy[n]][pos.x + dx[n]] == -1)
							{
								alien->dist[pos.y + dy[n]][pos.x + dx[n]] = alien->dist[pos.y][pos.x] + 1;
								changed = 1;
							}
						}
					}
				}
			}
		}
	}
}

/**
 * @brief Rellena la matriz de distancias usando wavefront iterativo.
 * 
 * Combina inicialización y propagación para generar el mapa de distancias
 * desde todos los puntos de calor del heatmap.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien con su matriz dist.
 */
void	ft_map_dist(t_game *game, t_player *alien)
{
	ft_init_dist_matrix(game, alien);
	ft_propagate_distances(game, alien);
}

/**
 * @brief Busca el vecino con menor distancia en los 4 tiles adyacentes.
 * 
 * Revisa arriba, abajo, izq, der. Si encuentra un vecino con distancia menor,
 * actualiza pos y retorna la nueva distancia. Si no hay mejora, retorna -1.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param pos puntero a posición (se modifica si encuentra mejor vecino).
 * @return -1 si no hay mejora, o nueva distancia.
 */
static int	ft_find_best_neighbor(t_game *game, t_player *alien, t_vector_int *pos)
{
	const int	dx[4] = {1, -1, 0, 0};
	const int	dy[4] = {0, 0, 1, -1};
	int			best_dist;
	int			n;

	best_dist = alien->dist[pos->y][pos->x];
	n = -1;
	while (++n < 4)
	{
		if (ft_is_walkable(game, pos->x + dx[n], pos->y + dy[n])
			&& alien->dist[pos->y + dy[n]][pos->x + dx[n]] >= 0)
		{
			if (alien->dist[pos->y + dy[n]][pos->x + dx[n]] < best_dist)
			{
				best_dist = alien->dist[pos->y + dy[n]][pos->x + dx[n]];
				pos->x = pos->x + dx[n];
				pos->y = pos->y + dy[n];
			}
		}
	}
	if (best_dist == alien->dist[pos->y][pos->x])
		return (-1);
	return (best_dist);
}

/**
 * @brief Construye un path retrocediendo por la matriz de distancias.
 * 
 * Comienza en la posición actual del alien. En cada iteración, busca el vecino
 * con menor distancia (sigue el gradiente hacia el calor). Agrega cada paso
 * al path hasta llegar a distancia 0 o alcanzar el máximo de 255 pasos.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien con dist y path.
 */
void	ft_build_path(t_game *game, t_player *alien)
{
	t_vector_int	pos;

	pos.x = (int)alien->position.x;
	pos.y = (int)alien->position.y;
	alien->path_len = 0;
	alien->curr_step = 0;
	while (alien->dist[pos.y][pos.x] > 0 && alien->path_len < 255)
	{
		if (ft_find_best_neighbor(game, alien, &pos) == -1)
			break ;
		alien->path[alien->path_len].x = pos.x;
		alien->path[alien->path_len].y = pos.y;
		alien->path_len++;
	}
}
