/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:10 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/15 23:18:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @file ft_parse_textures.c
 * @brief Funciones para analizar las texturas del archivo 
 * del mapa y cargarlas en el juego.
 *
 * Este archivo contiene funciones para manejar el 
 * análisis de texturas, incluyendo la carga de texturas desde rutas de archivos
 * y la creación de objetos de textura para paredes, suelos y techos.
 */
static void	ft_load_texture_from_path(t_game *game, t_texture *tex, char *path)
{
	int		i;

	check_arguments_xpm(path);
	tex->path = hd_alloc(ft_strdup(path), free);
	tex->img = (t_img *)ft_mlx_xpm_file_to_image(game->mlx,
			tex->path, &tex->width, &tex->height);
	if (!tex->img)
	{
		ft_dprintf(2,
			RED "Error: Failed to load from path: %s\n" RESET, tex->path);
		ft_close_game(1);
	}
	tex->cmx = hd_calloc(tex->height, sizeof(unsigned int *));
	i = 0;
	while (i < tex->height)
	{
		tex->cmx[i] = (unsigned int *)(tex->img->data
				+ (i * sizeof(char) * 4 * tex->width));
		i++;
	}
}

/**
 * @brief Crea una textura con  línea de definición y la carga en el juego.
 *
 * Esta función analiza la línea proporcionada, determina 
 * si es una ruta de textura o un color,
 * y crea un objeto de textura correspondiente. Si es una ruta, 
 * carga la textura desde el archivo.
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
	{
		tex->texture_color = ft_parse_color_rgb(split[1]);
		ft_printf("Parsed color: %u\n", tex->texture_color);
		tex->path = NULL;
	}
	else
		ft_close_game(1);
	return (tex);
}

static void	ft_add_wall_texture(t_game *game, char *line, int wall_id)
{
	t_texture	*new_tex;

	new_tex = ft_create_texture(game, line);
	ft_lstadd_back(&game->textures[wall_id],
		hd_alloc(ft_lstnew(new_tex), free));
}

/**
 * @brief Procesa una línea de definición de textura y la añade 
 * a la lista de texturas del juego.
 *
 * Esta función identifica el tipo de textura (NO, SO, WE, EA) 
 * en la línea proporcionada,
 * crea un objeto de textura y lo añade a la lista correspondiente 
 * en la estructura del juego.
 *
 * @param game estructura del juego donde se almacenarán las texturas.
 * @param line Línea que contiene la definición de la textura.
 */
void	ft_parse_texture_line(t_game *game, char *line)
{
	if (ft_strncmp_p(line, "NO", 2) == 0)
		ft_add_wall_texture(game, line, WALL_NO);
	else if (ft_strncmp_p(line, "SO", 2) == 0)
		ft_add_wall_texture(game, line, WALL_SO);
	else if (ft_strncmp_p(line, "WE", 2) == 0)
		ft_add_wall_texture(game, line, WALL_WE);
	else if (ft_strncmp_p(line, "EA", 2) == 0)
		ft_add_wall_texture(game, line, WALL_EA);
	else if (ft_strncmp_p(line, "F", 1) == 0)
		ft_add_wall_texture(game, line, 4);
	else if (ft_strncmp_p(line, "C", 1) == 0)
		ft_add_wall_texture(game, line, 5);
	else if (ft_strncmp_p(line, "D", 1) == 0)
		ft_add_wall_texture(game, line, 6);
}

/**
 * @brief Parsea todas las definiciones de texturas 
 * y colores desde el archivo del mapa.
 *
 * Recorre cada línea del archivo del mapa, identifica 
 * las definiciones de texturas y colores
 * (NO, SO, WE, EA, F, C, D), y las añade a las listas o 
 * campos correspondientes en la estructura del juego.
 *
 * @param game estructura del juego donde se almacenarán 
 * las texturas y colores.
 * @param map_file estructura de archivo que contiene 
 * el contenido del mapa como un arreglo de cadenas.
 */
void	ft_read_textures_in_map(t_game *game, t_file *map_file)
{
	int			i;

	i = 0;
	while (map_file->array_content[i])
	{
		ft_parse_texture_line(game, map_file->array_content[i]);
		i++;
	}
}
