/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:35:28 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:50:37 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void	ft_build_array_textures(t_game *game)
{
	int		i;
	t_list	*list;
	int		j;

	i = 0;
	while (i < 4)
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
	game->render->img = ft_create_image(game->mlx, RENDER_WIDTH, RENDER_HEIGHT);
	if (!game->render->img)
	{
		ft_dprintf(2, "Error: Failed to create render image\n");
		ft_close_game(1);
	}
	game->render->width = RENDER_WIDTH;
	game->render->height = RENDER_HEIGHT;
	game->render->cmx = hd_calloc(RENDER_HEIGHT,
			sizeof(unsigned int *));
	i = 0;
	while (i < RENDER_HEIGHT)
	{
		game->render->cmx[i]
			= (unsigned int *)(game->render->img->data
				+ (i * sizeof(unsigned int) * RENDER_WIDTH));
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
	game->window_img->cmx = hd_calloc(WINDOW_HEIGHT,
			sizeof(unsigned int *));
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		game->window_img->cmx[i]
			= (unsigned int *)(game->window_img->img->data
				+ (i * sizeof(unsigned int) * WINDOW_WIDTH));
		i++;
	}
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
	map_file = hd_alloc(ft_create_file_from_filename(path_map),
			hd_alloc_free_t_file);
	ft_parse_map(game, map_file);
	ft_read_textures_in_map(game, map_file);
	ft_build_array_textures(game);
	game->raycasts = hd_calloc(RENDER_WIDTH, sizeof(t_raycast));
	ft_config_player(game);
	ft_create_render(game);
	ft_create_window_img(game);
	ft_sin(0);
	ft_cos(0);
	ft_sqrt(0);
	game->precalc.scale_x_table = ft_scale_precalc_x();
	game->precalc.scale_y_table = ft_scale_precalc_y();
	hd_free(map_file);
	return (game);
}
