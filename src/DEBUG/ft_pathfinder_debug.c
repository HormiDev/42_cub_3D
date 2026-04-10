/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinder_debug.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 15:00:00 by nirmata          #+#    #+#             */
/*   Updated: 2026/04/05 15:00:00 by nirmata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Visualiza el mapa original en salida de debug.
 *
 * Imprime el mapa completo usando caracteres especiales:
 * - █ para muros (rojo)
 * - espacios para celdas vacías
 * - caracteres especiales (D, N, etc.) para elementos del mapa
 *
 * @param game estructura del juego.
 */
void	ft_debug_print_map(t_game *game)
{
	int	x;
	int	y;

	ft_dprintf(1, "\n%s========== MAPA ORIGINAL ==========%s\n", YELLOW, RESET);
	y = -1;
	while (++y < game->width_height[1])
	{
		x = -1;
		while (++x < game->width_height[0])
		{
			if (game->map_heatmap[y][x] == '1')
				ft_dprintf(1, "%s█%s", RED, RESET);
			else if (game->map_heatmap[y][x] == '0')
				ft_dprintf(1, " ");
			else
				ft_dprintf(1, "%c", game->map_heatmap[y][x]);
		}
		ft_dprintf(1, "\n");
	}
	ft_dprintf(1, "%s====================================%s\n\n", YELLOW,
		RESET);
}

/**
 * @brief Visualiza los nodos visitados durante la búsqueda BFS.
 *
 * Imprime el mapa mostrando:
 * - █ para muros (rojo)
 * - 0 para nodos visitados (verde)
 * - espacios para nodos no explorados
 *
 * @param game estructura del juego.
 * @param visited matriz de nodos visitados (máx 128x64).
 */
void	ft_debug_print_visited(t_game *game, int visited[128][64])
{
	int	x;
	int	y;

	ft_dprintf(1, "%s========== NODOS VISITADOS ========%s\n", CYAN, RESET);
	y = -1;
	while (++y < game->width_height[1])
	{
		x = -1;
		while (++x < game->width_height[0])
		{
			if (game->map_heatmap[y][x] == '1')
				ft_dprintf(1, "%s█%s", RED, RESET);
			else if (visited[y][x])
				ft_dprintf(1, "%s0%s", GREEN, RESET);
			else
				ft_dprintf(1, " ");
		}
		ft_dprintf(1, "\n");
	}
	ft_dprintf(1, "%s====================================%s\n\n", CYAN, RESET);
}

/**
 * @brief Visualiza la ruta calculada por el BFS.
 *
 * Imprime el mapa mostrando:
 * - S para punto de inicio (verde)
 * - G para objetivo (amarillo)
 * - 0 para pasos de la ruta (magenta)
 * - █ para muros (rojo)
 * - espacios para celdas no visitadas
 *
 * @param game estructura del juego.
 * @param path array de pasos de la ruta.
 * @param path_len longitud de la ruta.
 * @param start punto de inicio.
 * @param goal punto objetivo.
 */
void	ft_debug_print_path(t_game *game, t_vector_int *path, int path_len,
		t_vector_int start, t_vector_int goal)
{
	int	x;
	int	y;
	int	i;
	int	is_path;

	ft_dprintf(1, "%s========== RUTA ENCONTRADA ========%s\n", MAGENTA, RESET);
	y = -1;
	while (++y < game->width_height[1])
	{
		x = -1;
		while (++x < game->width_height[0])
		{
			is_path = 0;
			i = -1;
			while (++i < path_len)
			{
				if (path[i].x == x && path[i].y == y)
					is_path = 1;
			}
			if (game->map_heatmap[y][x] == '1')
				ft_dprintf(1, "%s█%s", RED, RESET);
			else if (x == start.x && y == start.y)
				ft_dprintf(1, "%sS%s", GREEN, RESET);
			else if (x == goal.x && y == goal.y)
				ft_dprintf(1, "%sG%s", YELLOW, RESET);
			else if (is_path)
				ft_dprintf(1, "%%s", MAGENTA, RESET);
			else
				ft_dprintf(1, " ");
		}
		ft_dprintf(1, "\n");
	}
	ft_dprintf(1, "%s====================================%s\n", MAGENTA, RESET);
	ft_dprintf(1, "S=Start | G=Goal | 0=Path | █=Wall\n");
	ft_dprintf(1, "Path length: %d\n\n", path_len);
}
