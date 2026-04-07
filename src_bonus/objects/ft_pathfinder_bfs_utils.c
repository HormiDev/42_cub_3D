#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Inicializa las estructuras del BFS con memoria dinámica.
 * 
 * Usa los punteros pre-asignados en la estructura t_bfs del juego.
 * Las matrices ya están asignadas dinámicamente durante el parse del mapa.
 *
 * @param bfs estructura del BFS a inicializar.
 * @param start nodo inicial de la búsqueda.
 * @param width ancho del mapa.
 * @param height alto del mapa.
 */
void	ft_bfs_init(t_bfs *bfs, t_vector_int start, int width, int height)
{
	int	i;

	i = 0;
	bfs->queue_start = 0;
	bfs->queue_end = 1;
	bfs->width = width;
	bfs->height = height;
	bfs->queue[0] = start;
	ft_memset(bfs->parent, -1, sizeof(int) * width * height);
	i = -1;
	while (++i < height)
		ft_memset(bfs->visited[i], 0, sizeof(int) * width);
	bfs->visited[start.y][start.x] = 1;
}

/**
 * @brief Valida si un tile es visitable en el BFS.
 * @param game estructura del juego.
 * @param bfs estructura BFS.
 * @param next coordenada a validar.
 * @return 1 si es válido, 0 si no.
 */
int	ft_bfs_is_valid_tile(t_game *game, t_bfs *bfs, t_vector_int next)
{
	if (next.x < 0 || next.x >= bfs->width || next.y < 0 || next.y >= bfs->height)
		return (0);
	if (bfs->visited[next.y][next.x])
		return (0);
	if (ft_is_wall_or_closed_door(game, next.x, next.y))
		return (0);
	return (1);
}

/**
 * @brief Procesa un vecino en el BFS.
 * @param bfs estructura BFS.
 * @param current nodo actual.
 * @param next nodo vecino a procesar.
 * @return 1 si se agregó a la cola, 0 si hay overflow.
 */
int	ft_bfs_process_neighbor(t_bfs *bfs, t_vector_int current, t_vector_int next)
{
	if (bfs->queue_end >= bfs->max_queue)
		return (0);
	bfs->visited[next.y][next.x] = 1;
	bfs->queue[bfs->queue_end] = next;
	bfs->parent[next.y * bfs->width + next.x] = current.y * bfs->width + current.x;
	bfs->queue_end++;
	return (1);
}

/**
 * @brief Inicializa los arrays de direcciones.
 * @param dx array de desplazamiento en X.
 * @param dy array de desplazamiento en Y.
 */
void	ft_init_directions(int *dx, int *dy)
{
	dx[0] = 1;
	dx[1] = -1;
	dx[2] = 0;
	dx[3] = 0;
	dy[0] = 0;
	dy[1] = 0;
	dy[2] = 1;
	dy[3] = -1;
}