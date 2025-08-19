#include "../../includes/cub_3d.h"

unsigned int	ft_parse_color_rgb(char *color_str) //borrar
{
	char			**rgb_values;
	unsigned int	color;

	rgb_values = ft_split_ae(color_str, ',');
	color = ft_atoi(rgb_values[0]);
	color = (color << 8) + ft_atoi(rgb_values[1]);
	color = (color << 8) + ft_atoi(rgb_values[2]);
	color = (color << 8) + 0xFF;
	// Liberar memoria de rgb_values tras actualizar ft_alloc_lst
	return (color);
}


int ft_str_isnumber(char *str) // para pasar a la libft
{
	printf("string: %s, len: %zu\n", str, ft_strlen(str));
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			printf("Error: character '%c' is not a digit.\n", *str);
			return (0);
		}
		str++;
	}
	printf("ok\n");
	return (1);
}

int ft_path_or_color(char *str)
{
	char	**split;
	int		rgb[3];

	if (ft_strchr(str, '/'))
		return (1);
	split = ft_split_chars_ae(str, ",\n\t");
	if (ft_splitlen(split) == 3)
	{
		rgb[0] = ft_atoi(split[0]);
		rgb[1] = ft_atoi(split[1]);
		rgb[2] = ft_atoi(split[2]);
		if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0
			|| rgb[1] > 255 || rgb[2] < 0 || rgb[2] > 255
			|| !ft_str_isnumber(split[0]) || !ft_str_isnumber(split[1])
			|| !ft_str_isnumber(split[2]))
		{
			ft_dprintf(2, RED "Error: Invalid color format. Expected R,G,B. %s\n" RESET, str); 
			return (0);
		}
		else
			return (2);
	}
    ft_dprintf(2, RED "Error: Invalid color format. Expected R,G,B.\n" RESET);
	return (0);
}

/**
 * @brief Crea una textura a partir de una línea de definición.
 *
 * Esta función toma una línea que define una textura, extrae la ruta de la textura
 * y crea un objeto de tipo t_texture con esa información. Si la ruta no se encuentra,
 * se imprime un mensaje de error y se cierra el juego.
 *
 * @param line Línea que contiene la definición de la textura.
 * @return Puntero a la nueva textura creada.
 */
t_texture	*ft_create_texture(t_game *game, char *line)
{
	t_texture 	*tex;
	char		**split;
	int			path_or_color;
	int			i;

	tex = ft_alloc_lst(sizeof(t_texture), 4);
	split = ft_split_chars_ae(line, " \n\t");
	if (split[1])
	{
		path_or_color = ft_path_or_color(split[1]);
		if (path_or_color == 1)
		{
			check_arguments_xpm(split[1]);
			tex->path = ft_strdup(split[1]);
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
				tex->colors_matrix[i] = tex->img->data + (i * tex->width * sizeof(unsigned int));
				i++;
			}
		}
		else if (path_or_color == 2)
			tex->texture_color = ft_parse_color_rgb(split[1]);
		else
			ft_close_game(1);
	}
	else
	{
		ft_dprintf(2, RED "Error: Texture path not found.\n" RESET);
		ft_close_game(1);
	}
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
		game->floor_tex = ft_create_texture(line);
		if (game->floor_tex->path)
		{
			ft_dprintf(2, "Floor texture path: %s is invalid.\n", game->floor_tex->path);
			ft_close_game(1);
		}
	}
	else if (ft_strncmp_p(line, "C", 1) == 0)
	{
		game->ceiling_tex = ft_create_texture(line);
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
