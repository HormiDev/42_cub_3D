/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:35:28 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:55:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_finalize_world(t_game *game)
{
	ft_loading_prerender_models(game);
	ft_config_player(game);
	ft_config_alien(game);
	ft_init_doors(game);
}

void	ft_loading_render(t_game *game, int render_height, int render_width)
{
	game->config.render_width = render_width;
	game->config.render_height = render_height;
	game->precalc.sxt = ft_scale_precalc_x(game);
	game->precalc.syt = ft_scale_precalc_y(game);
	if (game->config.n_players > 1)
		game->config.render_height /= 2;
	if (game->config.n_players > 2)
		game->config.render_width /= 2;
	ft_create_render(game);
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
	game->x_dcp = sqrt((DCP * DCP) + (DCP * DCP));
	ft_config_mlx(game);
	map_file = hd_alloc(ft_create_file_from_filename(path_map),
			hd_alloc_free_t_file);
	if (!map_file)
		return (ft_dprintf(2, "Error: Failed to create map\n"), NULL);
	ft_create_null_texture(game);
	ft_setup_map_and_ui(game, map_file);
	ft_load_all_textures(game);
	ft_init_game(game);
	ft_loading_render(game,
		game->resolutions[game->config.resolution_index].height,
		game->resolutions[game->config.resolution_index].width);
	ft_create_window_img(game);
	ft_create_minimap(game);
	ft_finalize_world(game);
	hd_free(map_file);
	return (game);
}
