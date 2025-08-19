#include "../../includes/cub_3d.h"

/**
 * @brief Encuentra la primera línea del mapa que no está vacía.
 *
 * Recorre las líneas del mapa hasta encontrar una que contenga un carácter distinto de espacio o salto de línea.
 * Si no se encuentra tal línea, imprime un mensaje de error y cierra el juego.
 *
 * @param map_file Puntero a la estructura del archivo que contiene el mapa.
 * @return int Índice de la primera línea del mapa.
 */
int	ft_start_line_map(t_file *map_file)
{
	int i;
	int j;

	i = ft_get_map_start_index(map_file);
	while (map_file->array_content[i])
	{
		j = 0;
		while (map_file->array_content[i][j])
		{
			if (map_file->array_content[i][j] != ' ' 
				&& map_file->array_content[i][j] != '\n')
				return (i);
			j++;
		}
		i++;
	}
	ft_dprintf(2, "%sError: Failed to load map: start not found\n%s", RED, RESET);
	ft_close_game(1);
	return (0);
}

/**
 * @brief Encuentra la última línea no vacía en el mapa.
 *
 * Recorre las líneas del mapa desde start_line hasta que encuentre una línea
 * que contenga un carácter distinto de espacio o salto de línea, y devuelve
 * el índice de esa línea.
 *
 * @param map_file Puntero a la estructura del archivo que contiene el mapa.
 * @param start_line Línea desde la cual comenzar la búsqueda.
 * @return int Índice de la última línea no vacía.
 */
int	ft_end_line_map(t_file *map_file, int start_line)
{
	int j;
	int last_line;

	last_line = start_line;
	while (map_file->array_content[start_line])
	{
		j = 0;
		while (map_file->array_content[start_line][j])
		{
			if (map_file->array_content[start_line][j] != ' ' 
				&& map_file->array_content[start_line][j] != '\n')
				last_line = start_line;
			j++;
		}
		start_line++;
	}
	return (last_line);
}

/**
 * @brief Encuentra la primera columna no vacía en el mapa.
 *
 * Recorre las líneas del mapa desde height_start_end[0] hasta height_start_end[1]
 * y determina la primera columna que contiene un carácter distinto de espacio o salto de línea.
 *
 * @param map_file Puntero a la estructura del archivo que contiene el mapa.
 * @param height_start_end Array con los índices de inicio y fin de las líneas del mapa.
 * @return int Índice de la primera columna no vacía.
 */
int	ft_start_column_map(t_file *map_file, const int *height_start_end)
{
	int i;
	int j;
	int	start_column;

	i = height_start_end[0];
	start_column = INT_MAX;
	while (i <= height_start_end[1])
	{
		j = 0;
		while (map_file->array_content[i][j])
		{
			if (map_file->array_content[i][j] != ' ' 
				&& map_file->array_content[i][j] != '\n')
				if (j < start_column)
					start_column = j;
			j++;
		}
		i++;
	}
	return (start_column);
}

/**
 * @brief Encuentra la última columna no vacía en el mapa.
 *
 * Recorre las líneas del mapa desde height_start_end[0] hasta height_start_end[1]
 * y determina la última columna que contiene un carácter distinto de espacio o salto de línea.
 *
 * @param map_file Puntero a la estructura del archivo que contiene el mapa.
 * @param height_start_end Array con los índices de inicio y fin de las líneas del mapa.
 * @return int Índice de la última columna no vacía.
 */
int	ft_end_column_map(t_file *map_file, const int *height_start_end)
{
	int i;
	int j;
	int end_column;

	end_column = 0;
	i = height_start_end[0];
	while (i <= height_start_end[1])
	{
		j = ft_strlen(map_file->array_content[i]) - 1;
		while (j >= 0)
		{
			if (map_file->array_content[i][j] != ' ' 
				&& map_file->array_content[i][j] != '\n')
			{
				if (j > end_column)
					end_column = j;
				break ;
			}	
			j--;
		}
		i++;
	}
	return (end_column);
}

void	ft_rotate_map_y(t_game *game)
{
	char	*tmp;
	int		start;
	int		end;

	start = 0;
	end = game->width_height[1] - 1;
	while (start < end)
	{
		tmp = game->map[start];
		game->map[start] = game->map[end];
		game->map[end] = tmp;
		start++;
		end--;
	}
}
