/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_textures_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:23:15 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:50:37 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @file ft_parse_textures.c

 * @brief texturas del archivo del mapa y cargarlas en el juego.
 *
 * Este archivo contiene funciones para manejar el análisis de texturas,
	incluyendo la carga de texturas desde rutas de archivos
 * y la creación de objetos de textura para paredes, suelos y techos.
 */
void	ft_load_texture_from_path(t_game *game, t_texture *tex, char *path)
{
	int	i;

	check_arguments_xpm(path);
	tex->path = hd_alloc(ft_strdup(path), free);
	tex->img = (t_img *)ft_mlx_xpm_file_to_image(game->mlx,
			tex->path, &tex->width, &tex->height);
	if (!tex->img)
	{
		ft_dprintf(2, RED "Error: Failed to load texture from path: %s\n" RESET,
			tex->path);
		ft_close_game(1);
	}
	tex->cmx = hd_calloc(tex->height, sizeof(unsigned int *));
	i = 0;
	while (i < tex->height)
	{
		tex->cmx[i] = (unsigned int *)(tex->img->data + (i
					* sizeof(char) * 4 * tex->width));
		i++;
	}
}
