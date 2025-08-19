/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:17:36 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/09 01:36:556 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

/**
 * @brief Carga el juego desde un archivo de mapa.
 *
 * Esta función crea una nueva estructura de juego, carga el mapa desde el archivo
 * especificado, y configura las texturas, colores y raycasts necesarios para el juego.
 * Si ocurre algún error durante la carga, se imprime un mensaje de error y se retorna NULL.
 *
 * @param path_map Ruta al archivo del mapa.
 * @return Puntero a la estructura del juego cargado o NULL en caso de error.
 */
t_game	*ft_loading_game(char *path_map)
{
	t_game *game;
	t_file *map_file;
    
    game = ft_alloc_lst(sizeof(t_game), 4);
	map_file = ft_create_file_from_filename(path_map);
	if (!map_file)
	{
		ft_dprintf(2, "Error\n");
		return (0);
	}
	//ft_file_print(map_file);

	ft_parse_map(game, map_file);
	ft_read_textures_in_map(game, map_file);
	game->raycasts = ft_alloc_lst(sizeof(t_raycast) * WINDOW_WIDTH, 4);
	if (!game->raycasts)
	{
		ft_dprintf(2, "Error: Failed to allocate raycast array\n");
		return (0);
	}
	ft_config_player(game);
	ft_sin(0);
	ft_cos(0);
	ft_sqrt(0);
	ft_debug_game(game);
	ft_file_clear(&map_file);
	ft_printf("Map loaded successfully\n");
	
	return (game);
}

