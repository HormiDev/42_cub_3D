#include "../../includes/cub_3d.h"

/**
 * @file ft_parse_textures.c
 * @brief Funciones para analizar las texturas del archivo del mapa y cargarlas en el juego.
 *
 * Este archivo contiene funciones para manejar el análisis de texturas, incluyendo la carga de texturas desde rutas de archivos
 * y la creación de objetos de textura para paredes, suelos y techos.
 */
static void	ft_load_texture_from_path(t_game *game, t_texture *tex, char *path)
{
	int	i;

	check_arguments_xpm(path);
	tex->path = ft_strdup(path);
	tex->img = mlx_xpm_file_to_image(game->mlx, tex->path, &tex->width, &tex->height);
	if (!tex->img)
	{
		ft_dprintf(2, RED "Error: Failed to load texture from path: %s\n" RESET, tex->path);
		ft_close_game(1);
	}
	tex->colors_matrix = ft_alloc_lst(sizeof(unsigned int *) * tex->height, 4);
	i = 0;
	while (i < tex->height)
	{
		tex->colors_matrix[i] = tex->img->data + (i * sizeof(unsigned int) * tex->width);
		i++;
	}
}

/**
 * @brief Crea una textura a partir de una línea de definición y la carga en el juego.
 *
 * Esta función analiza la línea proporcionada, determina si es una ruta de textura o un color,
 * y crea un objeto de textura correspondiente. Si es una ruta, carga la textura desde el archivo.
 * Si es un color, lo convierte a formato RGB.
 *
 * @param game Puntero a la estructura del juego donde se almacenará la textura.
 * @param line Línea que contiene la definición de la textura o color.
 * @return Puntero al objeto de textura creado.
 */
t_texture	*ft_create_texture(t_game *game, char *line)
{
	t_texture 	*tex;
	char		**split;
	int			path_or_color;

	tex = ft_alloc_lst(sizeof(t_texture), 4);
	split = ft_split_chars_ae(line, " \n\t");
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
 * @brief Procesa una línea de definición de textura de pared y la añade a la lista de texturas del juego.
 *
 * Esta función identifica el tipo de textura de pared (NO, SO, WE, EA) en la línea proporcionada,
 * crea un objeto de textura y lo añade a la lista correspondiente en la estructura del juego.
 *
 * @param game Puntero a la estructura del juego donde se almacenarán las texturas.
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
			ft_dprintf(2, "Floor texture path: %s is invalid.\n", game->floor_tex->path);
			ft_close_game(1);
		}
	}
	else if (ft_strncmp_p(line, "C", 1) == 0)
	{
		game->ceiling_tex = ft_create_texture(game, line);
		if (game->ceiling_tex->path)
		{
			ft_dprintf(2, "Ceiling texture path: %s is invalid.\n", game->ceiling_tex->path);
			ft_close_game(1);
		}
	}
}

/**
 * @brief Procesa una línea de definición de textura y la añade a la lista de texturas del juego.
 *
 * Esta función identifica el tipo de textura (NO, SO, WE, EA) en la línea proporcionada,
 * crea un objeto de textura y lo añade a la lista correspondiente en la estructura del juego.
 *
 * @param game Puntero a la estructura del juego donde se almacenarán las texturas.
 * @param line Línea que contiene la definición de la textura.
 */
void ft_parse_texture_line(t_game *game, char *line)
{
	t_texture *new_tex;

	if (ft_strncmp_p(line, "NO", 2) == 0)
	{
		new_tex = ft_create_texture(game, line);
		ft_lstadd_back(&game->textures[WALL_NO], ft_lstnew_a(new_tex));
	}
	else if (ft_strncmp_p(line, "SO", 2) == 0)
	{
		new_tex = ft_create_texture(game, line);
		ft_lstadd_back(&game->textures[WALL_SO], ft_lstnew_a(new_tex));
	}
	else if (ft_strncmp_p(line, "WE", 2) == 0)
	{
		new_tex = ft_create_texture(game, line);
		ft_lstadd_back(&game->textures[WALL_WE], ft_lstnew_a(new_tex));
	}
	else if (ft_strncmp_p(line, "EA", 2) == 0)
	{
		new_tex = ft_create_texture(game, line);
		ft_lstadd_back(&game->textures[WALL_EA], ft_lstnew_a(new_tex));
	}
	else
		ft_parse_floor_ceiling(game, line);
}



/**
 * @brief Parsea todas las definiciones de texturas y colores desde el archivo del mapa.
 *
 * Recorre cada línea del archivo del mapa, identifica las definiciones de texturas y colores
 * (NO, SO, WE, EA, F, C), y las añade a las listas o campos correspondientes en la estructura del juego.
 *
 * @param game Puntero a la estructura del juego donde se almacenarán las texturas y colores.
 * @param map_file Puntero a la estructura de archivo que contiene el contenido del mapa como un arreglo de cadenas.
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
