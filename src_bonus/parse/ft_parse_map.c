/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:23:15 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/09 20:54:59 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief copia del mapa para usar como heatmap del pathfinding del alien.
 *
 * Copia game->map a game->map_heatmap como matriz de enteros. El heatmap usa:
 * -1 para muros ('1') y puertas cerradas ('D')
 *  0 para tiles transitables
 * 1/2/4 para calor generado por players según su acción (quieto/andar/correr)
 *
 * @param game estructura del juego con el mapa a copiar.
 */
static void	ft_create_map_heat(t_game *game)
{
	int		i;
	int		j;
	char	tile;

	if (!game || !game->map)
		return ;
	game->map_heatmap = hd_calloc(game->width_height[1], sizeof(int *));
	i = 0;
	while (i < game->width_height[1])
	{
		game->map_heatmap[i] = hd_calloc(game->width_height[0], sizeof(int));
		j = 0;
		while (j < game->width_height[0])
		{
			tile = game->map[i][j];
			if (tile == '1' || tile == 'D')
				game->map_heatmap[i][j] = -1;
			else
				game->map_heatmap[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	ft_set_map_dimensions_and_bfs(t_game *game, t_file *map_file,
		int h_start_end[2], int w_start_end[2])
{
	h_start_end[0] = ft_start_line_map(map_file);
	h_start_end[1] = ft_end_line_map(map_file, h_start_end[0]);
	game->width_height[1] = h_start_end[1] - h_start_end[0] + 1;
	w_start_end[0] = ft_start_column_map(map_file, h_start_end);
	w_start_end[1] = ft_end_column_map(map_file, h_start_end);
	game->width_height[0] = w_start_end[1] - w_start_end[0] + 1;
	if (game->width_height[0] < 3 || game->width_height[1] < 3)
	{
		ft_dprintf(2, "%sError: Failed to load small map\n%s", RED, RESET);
		ft_close_game(1);
	}
	game->bfs_queue_size = game->width_height[0] * game->width_height[1];
	if (game->bfs_queue_size > 8192)
		game->bfs_queue_size = 8192;
	game->bfs_parent_size = game->width_height[0] * game->width_height[1];
	game->bfs_visited_width = game->width_height[0];
	game->bfs_visited_height = game->width_height[1];
}

/**
 * @brief Parsea el mapa del juego.
 *
 * Esta función determina las dimensiones del mapa (ancho y alto) y crea el mapa
 * en la estructura del juego. También verifica que el mapa sea válido y lo rota
 * si es necesario. Además, crea una copia del mapa para usar como heatmap.
 *
 * @param game estructura del juego donde se almacenará el mapa.
 * @param map_file estructura del archivo que contiene el mapa.
 */
void	ft_parse_map(t_game *game, t_file *map_file)
{
	int	h_start_end[2];
	int	w_start_end[2];

	ft_set_map_dimensions_and_bfs(game, map_file, h_start_end, w_start_end);
	ft_create_game_map(game, map_file, h_start_end, w_start_end);
	ft_check_map(game);
	ft_rotate_map_y(game);
	ft_create_map_heat(game);
	ft_create_map_transitable(game);
	ft_create_map_transitable_aux(game);
	ft_alloc_bfs_structures(game);
}

/**
 * @brief Asigna dinámicamente la memoria para las estructuras BFS.
 * 
 * Usa HD_alloc para asegurar que toda la memoria se libera al cierre del juego.
 * Las dimensiones ya están calculadas en game->bfs_queue_size, bfs_parent_size,
 * bfs_visited_width y bfs_visited_height basado en el tamaño del mapa.
 *
 * @param game estructura del juego.
 */
void	ft_alloc_bfs_structures(t_game *game)
{
	int		i;

	if (game->bfs_queue_size > 8192)
		game->bfs_queue_size = 8192;
	if (game->bfs_parent_size > 8192)
		game->bfs_parent_size = 8192;
	game->bfs_queue
		= (t_vector_int *)hd_calloc(game->bfs_queue_size, sizeof(t_vector_int));
	game->bfs_parent = (int *)hd_calloc(game->bfs_parent_size, sizeof(int));
	game->bfs_visited
		= (int **)hd_calloc(game->bfs_visited_height, sizeof(int *));
	i = -1;
	while (++i < game->bfs_visited_height)
		game->bfs_visited[i]
			= (int *)hd_calloc(game->bfs_visited_width, sizeof(int));
}
