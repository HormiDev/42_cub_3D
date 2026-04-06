/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:35:28 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 03:14:02 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_build_array_textures(t_game *game)
{
	int		i;
	t_list	*list;
	int		j;

	i = 0;
	while (i < 6)
	{
		list = game->textures[i];
		game->larraytex[i] = ft_lstsize(list);
		if (game->larraytex[i] > 0)
		{
			game->arraytextures[i] = hd_calloc(game->larraytex[i],
					sizeof(t_texture *));
			j = 0;
			while (list)
			{
				game->arraytextures[i][j] = (t_texture *)list->content;
				list = list->next;
				j++;
			}
		}
		i++;
	}
}

void	ft_create_render(t_game *game)
{
	int	i;

	game->render = hd_calloc(1, sizeof(t_texture));
	game->render->img = ft_create_image(game->mlx, game->config.render_width,
			game->config.render_height);
	if (!game->render->img)
	{
		ft_dprintf(2, "Error: Failed to create render image\n");
		ft_close_game(1);
	}
	game->render->width = game->config.render_width;
	game->render->height = game->config.render_height;
	game->render->colors_matrix = hd_calloc(game->config.render_height,
			sizeof(unsigned int *));
	i = 0;
	while (i < game->config.render_height)
	{
		game->render->colors_matrix[i] = (unsigned int *)(game->render->img->data
				+ (i * sizeof(unsigned int) * game->config.render_width));
		i++;
	}
}

void	ft_create_window_img(t_game *game)
{
	int	i;

	game->window_img = hd_calloc(1, sizeof(t_texture));
	game->window_img->img = ft_create_image(game->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!game->window_img->img)
	{
		ft_dprintf(2, "Error: Failed to create window image\n");
		ft_close_game(1);
	}
	game->window_img->width = WINDOW_WIDTH;
	game->window_img->height = WINDOW_HEIGHT;
	game->window_img->colors_matrix = hd_calloc(WINDOW_HEIGHT,
			sizeof(unsigned int *));
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		game->window_img->colors_matrix[i] = (unsigned int *)(game->window_img->img->data
				+ (i * sizeof(unsigned int) * WINDOW_WIDTH));
		i++;
	}
}

/**
 * @brief Crea la imagen del minimapa.
 * @param game estructura del juego.
 * @details La función crea una imagen de 200x200 píxeles para el minimapa.
 */
void	ft_create_minimap(t_game *game)
{
	int	i;
	int	size;

	size = WINDOW_HEIGHT / 5;
	game->minimap = hd_calloc(1, sizeof(t_texture));
	game->minimap->img = ft_create_image(game->mlx, size, size);
	if (!game->minimap->img)
	{
		ft_dprintf(2, "Error: Failed to create minimap image\n");
		ft_close_game(1);
	}
	game->minimap->width = size;
	game->minimap->height = size;
	game->minimap->colors_matrix = hd_calloc(size, sizeof(unsigned int *));
	i = 0;
	while (i < size)
	{
		game->minimap->colors_matrix[i] = (unsigned int *)(game->minimap->img->data
				+ (i * sizeof(unsigned int) * size));
		i++;
	}
}

void	ft_loading_render(t_game *game, int render_height, int render_width)
{
	game->config.render_width = render_width;
	game->config.render_height = render_height;
	game->precalc.scale_x_table = ft_scale_precalc_x(game);
	game->precalc.scale_y_table = ft_scale_precalc_y(game);
	if (game->config.n_players > 1)
		game->config.render_height /= 2;
	if (game->config.n_players > 2)
		game->config.render_width /= 2;
	ft_create_render(game);
	// tas impementar hd_alloc para liberar game->raycasts antes de reasignar
	game->raycasts = hd_calloc(render_width, sizeof(t_raycast));
	ft_prec_fish_eye_correction(game);
	ft_prec_vector_cloud(game);
}

/**
 * @brief Carga el juego desde un archivo de mapa.
 *
 * Esta función crea una nueva estructura de juego,
	carga el mapa desde el archivo
 * especificado, y configura las texturas,
	colores y raycasts necesarios para el juego.
 * Si ocurre algún error durante la carga,
	se imprime un mensaje de error y se retorna NULL.
 *
 * @param path_map Ruta al archivo del mapa.
 * @return estructura del juego cargado o NULL en caso de error.
 */
t_game	*ft_loading_game(char *path_map)
{
	t_game	*game;
	t_file	*map_file;

	game = hd_calloc(1, sizeof(t_game));
	ft_config_mlx(game);
	map_file = hd_alloc(ft_create_file_from_filename(path_map), hd_alloc_free_t_file);
	if (!map_file)
	{
		ft_dprintf(2, "Error: Failed to create map\n");
		return (0);
	}
	ft_parse_map(game, map_file);
	ft_read_textures_in_map(game, map_file);
	ft_build_array_textures(game);
	ft_loading_menu(game);
	ft_loading_menu_settings(game);
	game->font = ft_loading_texture(game->mlx, "textures/fuente.xpm");
	if (!game->font)
		ft_dprintf(2, RED "Error: Failed to load font texture\n" RESET);
	game->config.n_players = 1;
	game->config.duration_index = 2;
	game->config.charges = 3;
	game->game_state = GAME_PLAYING;
	ft_init_durations(game);
	ft_init_timer(game);
	ft_init_resolutions(game);
	game->config.resolution_index = RES_540;
	ft_loading_render(game, game->resolutions[game->config.resolution_index].height,
		game->resolutions[game->config.resolution_index].width);
	ft_create_window_img(game);
	ft_create_minimap(game);
	ft_sin(0);
	ft_cos(0);
	ft_sqrt(0);
	game->precalc.rotated_squares = ft_precalc_rotated_squares();
	ft_loading_prerender_models(game);
	ft_config_player(game);
	ft_config_alien(game);
	ft_init_doors(game);
	hd_free(map_file);
	return (game);
}
