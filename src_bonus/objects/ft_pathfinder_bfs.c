/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinder_bfs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 01:37:40 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 01:41:32 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Explora el mapa usando BFS desde un nodo inicial hacia el objetivo.
 * @param game estructura del juego con el mapa.
 * @param bfs estructura BFS con la cola y matrices.
 * @param goal coordenada del objetivo en el mapa.
 * @return 1 si se encontró el objetivo, 0 si no hay camino.
 */
static int	ft_bfs_explore(t_game *game, t_bfs *bfs, t_vector_int goal)
{
	t_vector_int	current;
	t_vector_int	next;
	int				dx[4];
	int				dy[4];
	int				i;

	ft_init_directions(dx, dy);
	while (bfs->queue_start < bfs->queue_end && bfs->queue_end < bfs->max_queue)
	{
		current = bfs->queue[bfs->queue_start++];
		if (current.x == goal.x && current.y == goal.y)
			return (1);
		i = -1;
		while (++i < 4)
		{
			next.x = current.x + dx[i];
			next.y = current.y + dy[i];
			if (ft_bfs_is_valid_tile(game, bfs, next))
				if (!ft_bfs_process_neighbor(bfs, current, next))
					return (0);
		}
	}
	return (0);
}

/**
 * @brief Retrocede desde goal hasta start usando la matriz de padres.
 * @param bfs estructura BFS con matriz de padres.
 * @param start punto inicial.
 * @param goal punto objetivo.
 * @param path array donde guardar el recorrido.
 * @return longitud del camino encontrado.
 */
static int	ft_bfs_backtrack_path(t_bfs *bfs, t_vector_int start,
		t_vector_int goal, t_vector_int *path)
{
	t_vector_int	current;
	int				idx;
	int				path_pos;

	path_pos = 0;
	current = goal;
	while (!(current.x == start.x && current.y == start.y) && path_pos < 1023)
	{
		path[path_pos++] = current;
		idx = current.y * bfs->width + current.x;
		if (bfs->parent[idx] == -1)
			break ;
		idx = bfs->parent[current.y * bfs->width + current.x];
		current.y = idx / bfs->width;
		current.x = idx % bfs->width;
	}
	if (path_pos < 1023)
		path[path_pos++] = start;
	return (path_pos);
}

/**
 * @brief Invierte un array de coordenadas.
 * @param path array a invertir.
 * @param path_len longitud del array.
 */
static void	ft_bfs_invert_path(t_vector_int *path, int path_len)
{
	t_vector_int	tmp;
	int				i;

	i = 0;
	while (i < path_len / 2)
	{
		tmp = path[i];
		path[i] = path[path_len - 1 - i];
		path[path_len - 1 - i] = tmp;
		i++;
	}
}

/**
 * @brief Reconstruye el camino desde el objetivo al inicio.
 * @param bfs estructura BFS con la matriz de padres y dimensiones.
 * @param start punto inicial del camino.
 * @param goal punto objetivo del camino.
 * @param path array donde se almacenará la ruta.
 * @param path_len puntero donde se guarda la longitud de la ruta.
 */
static void	ft_bfs_rebuild_path(t_bfs *bfs, t_bfs_request request,
		t_bfs_result result)
{
	*result.path_len = ft_bfs_backtrack_path(bfs, request.start, request.goal,
			result.path);
	ft_bfs_invert_path(result.path, *result.path_len);
}

/**
 * @brief Calcula el camino más corto entre dos puntos usando BFS.
 *

 * Función principal del pathfinding. 
 * Inicializa el BFS con estructuras dinámicas,
 * ejecuta la exploración, y reconstruye la ruta si se alcanza el objetivo.
 * Debug activable con #define DEBUG_PATHFINDER.
 *
 * @param game estructura del juego con estructuras BFS pre-asignadas.
 * @param start coordenadas iniciales en tiles.
 * @param goal coordenadas del objetivo en tiles.
 * @param path array donde se retorna el camino completo.
 * @param path_len longitud del camino encontrado.
 * @return 1 si se encontró camino, 0 si no existe camino.
 */
int	ft_bfs_path(t_game *game, t_bfs_request request, t_bfs_result result)
{
	t_bfs	bfs;

	bfs.queue = game->bfs_queue;
	bfs.parent = game->bfs_parent;
	bfs.visited = game->bfs_visited;
	bfs.max_queue = game->bfs_queue_size;
	ft_bfs_init(&bfs, request.start, game->bfs_visited_width,
		game->bfs_visited_height);
	if (!ft_bfs_explore(game, &bfs, request.goal))
	{
		*result.path_len = 0;
		return (0);
	}
	ft_bfs_rebuild_path(&bfs, request, result);
	return (1);
}
