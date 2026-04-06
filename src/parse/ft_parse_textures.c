/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 01:18:49 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 19:20:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
* @brief Crea una textura a partir de una línea de definición y la carga
 *
 * Esta función analiza la línea proporcionada,
	determina si es una ruta de textura o un color,
 * y crea un objeto de textura correspondiente. Si es una ruta,
	carga la textura desde el archivo.
 * Si es un color, lo convierte a formato RGB.
 *
 * @param game estructura del juego donde se almacenará la textura.
 * @param line Línea que contiene la definición de la textura o color.
 * @return Puntero al objeto de textura creado.
 */
t_texture	*ft_create_texture(t_game *game, char *line)
{
	t_texture	*tex;
	char		**split;
	int			path_or_color;

	tex = hd_calloc(1, sizeof(t_texture));
	split = hd_alloc(ft_split_chars(line, " \n\t"), ft_hd_alloc_free_split);
	if (!split[1])
	{
		ft_dprintf(2, RED "Error: Texture path not found.\n" RESET);
		ft_close_game(1);
	}
	path_or_color = ft_path_or_color(split[1]);
	if (path_or_color == 1)
		ft_load_texture_from_path(game, tex, split[1]);
	else if (path_or_color == 2)
		tex->texture_color = ft_parse_color_rgb(split[1]);
	else
		ft_close_game(1);
	return (tex);
}

/**


 * @brief Procesa una línea de definición de textura de pared
 *
 * Esta función identifica el tipo de textura de pared (NO, SO, WE,
	EA) en la línea proporcionada,

 * crea un objeto de textura y lo añade a la lista correspondiente
 * @param game estructura del juego donde se almacenarán las texturas.
 * @param line Línea que contiene la definición de la textura de pared.
 * BONUS: Modificar
 */
static void	ft_parse_floor_ceiling(t_game *game, char *line)
{
	if (ft_strncmp_p(line, "F", 1) == 0)
	{
		game->floor_tex = ft_create_texture(game, line);
		if (game->floor_tex->path)
		{
			ft_dprintf(2, "Floor texture path: %s is invalid.\n",
				game->floor_tex->path);
			ft_close_game(1);
		}
	}
	else if (ft_strncmp_p(line, "C", 1) == 0)
	{
		game->ceiling_tex = ft_create_texture(game, line);
		if (game->ceiling_tex->path)
		{
			ft_dprintf(2, "Ceiling texture path: %s is invalid.\n",
				game->ceiling_tex->path);
			ft_close_game(1);
		}
	}
}

/**
 * @brief Procesa una linea de textura de pared (NO, SO, WE, EA).
 * @param game estructura del juego.
 * @param line linea con definicion de textura de pared.
 */
static void	ft_parse_wall_texture(t_game *game, char *line)
{
	t_texture	*new_tex;

	new_tex = ft_create_texture(game, line);
	if (ft_strncmp_p(line, "NO", 2) == 0)
		ft_lstadd_back(&game->textures[WALL_NO],
			hd_alloc(ft_lstnew(new_tex), free));
	else if (ft_strncmp_p(line, "SO", 2) == 0)
		ft_lstadd_back(&game->textures[WALL_SO],
			hd_alloc(ft_lstnew(new_tex), free));
	else if (ft_strncmp_p(line, "WE", 2) == 0)
		ft_lstadd_back(&game->textures[WALL_WE],
			hd_alloc(ft_lstnew(new_tex), free));
	else if (ft_strncmp_p(line, "EA", 2) == 0)
		ft_lstadd_back(&game->textures[WALL_EA],
			hd_alloc(ft_lstnew(new_tex), free));
}

/**
 * @brief Procesa una linea de definicion de textura o color.
 * @param game estructura del juego.
 * @param line linea con definicion.
 */
void	ft_parse_texture_line(t_game *game, char *line)
{
	if (ft_strncmp_p(line, "NO", 2) == 0
		|| ft_strncmp_p(line, "SO", 2) == 0
		|| ft_strncmp_p(line, "WE", 2) == 0
		|| ft_strncmp_p(line, "EA", 2) == 0)
		ft_parse_wall_texture(game, line);
	else
		ft_parse_floor_ceiling(game, line);
}

/**

 * @brief Parsea todas las definiciones de texturas y colores
 *
 * Recorre cada línea del archivo del mapa,
	identifica las definiciones de texturas y colores
 * (NO, SO, WE, EA, F, C),
 *
 * @param game estructura del juego donde se almacenarán las texturas y colores.
 * @param map_file estructura de archivo que contiene el contenido del mapa
 */
void	ft_read_textures_in_map(t_game *game, t_file *map_file)
{
	int	i;

	i = 0;
	while (map_file->array_content[i])
	{
		ft_parse_texture_line(game, map_file->array_content[i]);
		i++;
	}
}
