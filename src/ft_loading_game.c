/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:35:28 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/22 13:03:20 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void ft_create_render(t_game *game)
{
	int i;

	game->render = ft_alloc_lst(sizeof(t_texture), 4);
	game->render->img = mlx_new_image(game->mlx, RENDER_WIDTH, RENDER_HEIGHT);
	if (!game->render->img)
	{
		ft_dprintf(2, "Error: Failed to create render image\n");
		ft_close_game(1);
	}
	game->render->width = RENDER_WIDTH;
	game->render->height = RENDER_HEIGHT;
	game->render->colors_matrix = ft_alloc_lst(sizeof(unsigned int *) * RENDER_HEIGHT, 4);
	i = 0;
	while (i < RENDER_HEIGHT)
	{
		game->render->colors_matrix[i] = (unsigned int *)(game->render->img->data + (i * sizeof(unsigned int) * RENDER_WIDTH));
		i++;
	}
}

void ft_create_window_img(t_game *game)
{
	int i;

	game->window_img = ft_alloc_lst(sizeof(t_texture), 4);
	game->window_img->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->window_img->img)
	{
		ft_dprintf(2, "Error: Failed to create window image\n");
		ft_close_game(1);
	}
	game->window_img->width = WINDOW_WIDTH;
	game->window_img->height = WINDOW_HEIGHT;
	game->window_img->colors_matrix = ft_alloc_lst(sizeof(unsigned int *) * WINDOW_HEIGHT, 4);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		game->window_img->colors_matrix[i] = (unsigned int *)(game->window_img->img->data + (i * sizeof(unsigned int) * WINDOW_WIDTH));
		i++;
	}
}

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
	ft_config_mlx(game);
	map_file = ft_create_file_from_filename(path_map);
	if (!map_file)
	{
		ft_dprintf(2, "Error: Failed to create map\n");
		return (0);
	}
	ft_parse_map(game, map_file);
	ft_read_textures_in_map(game, map_file);
	game->raycasts = ft_alloc_lst(sizeof(t_raycast) * RENDER_WIDTH, 4);
	ft_config_player(game);
	ft_create_render(game);
	ft_create_window_img(game);
	ft_sin(0);
	ft_cos(0);
	ft_sqrt(0);
	//ft_debug_game(game);
	ft_file_clear(&map_file);
	return (game);
}

