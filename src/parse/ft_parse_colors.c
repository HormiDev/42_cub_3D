#include "../../includes/cub_3d.h"

/**
 * @brief Establece el color en el arreglo destino.
 *
 * Esta función asigna los valores RGB en el arreglo target_color.
 *
 * @param target_color Puntero al arreglo donde se establecerá el color.
 * @param r Componente rojo (0-255).
 * @param g Componente verde (0-255).
 * @param b Componente azul (0-255).
 */
static void ft_set_color(int *target_color, int r, int g, int b)
{
    target_color[0] = r;
    target_color[1] = g;
    target_color[2] = b;
}

/**
 * @brief Parsea los valores RGB de una cadena de texto.
 *
 * Esta función toma una cadena de texto que representa un color en formato R,G,B,
 * la divide en sus componentes y verifica que estén dentro del rango válido (0-255).
 * Luego, establece el color correspondiente en el juego.
 *
 * @param game Puntero a la estructura del juego donde se almacenará el color.
 * @param color_str Cadena de texto que contiene los valores RGB.
 * @param color_type Tipo de color (FLOOR o CEILING).
 * @return int 1 si el parsing fue exitoso, 0 si hubo un error.
 */
int ft_parse_rgb_values(t_game *game, char *color_str, int color_type)
{
    char **rgb_values;
    int r, g, b;
    int i;

    rgb_values = ft_split_ae(color_str, ',');
    if (!rgb_values)
        return (ft_dprintf(2, RED "Error: Failed to split color values.\n" RESET), 0);
    i = 0;
    while (rgb_values[i])
        i++;
    if (i != 3)
        return (ft_dprintf(2, RED "Error: Invalid color format. Expected R,G,B.\n" RESET), 0);
    r = ft_atoi(rgb_values[0]);
    g = ft_atoi(rgb_values[1]);
    b = ft_atoi(rgb_values[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (ft_dprintf(2, RED "Error: Color values must be between 0 and 255.\n" RESET), 0);

    if (color_type == FLOOR)
        ft_set_color(game->floor_color, r, g, b);
    else if (color_type == CEILING)
        ft_set_color(game->ceiling_color, r, g, b);
    return (1);
}

/**
 * @brief Obtiene la cadena de color de una línea y la procesa.
 *
 * Esta función toma una línea del archivo, extrae la cadena de color,
 * la limpia de espacios y tabulaciones, y luego llama a ft_parse_rgb_values
 * para procesar los valores RGB.
 *
 * @param game Puntero a la estructura del juego donde se almacenará el color.
 * @param line Línea del archivo que contiene el color.
 * @param color_type Tipo de color (FLOOR o CEILING).
 * @return int 1 si el parsing fue exitoso, 0 si hubo un error.
 */
int ft_get_color_string(t_game *game, char *line, int color_type)
{
    char *color_str;
    
    color_str = ft_add_to_alloc_lst_e(ft_strtrim(line + 2, " \t\n"));
    if (ft_parse_rgb_values(game, color_str, color_type))
        return (1);
    return (0);
}

/**
 * @brief Parsea los colores del mapa.
 *
 * Esta función recorre el contenido del archivo del mapa y busca las líneas
 * que definen los colores del suelo (F) y del techo (C). Llama a ft_get_color_string
 * para procesar cada línea de color.
 *
 * @param game Puntero a la estructura del juego donde se almacenarán los colores.
 * @param map_file Puntero a la estructura del archivo que contiene el mapa.
 */
void ft_parse_colors(t_game *game, t_file *map_file)
{
    int i; 
    int count; 

    i = 0; 
    count = 0; 
    while (map_file->array_content[i] && count < 2)
	{
		if (ft_strncmp_p(map_file->array_content[i], "F ", 1) == 0)
			count += ft_get_color_string(game, map_file->array_content[i], FLOOR);
		else if (ft_strncmp_p(map_file->array_content[i], "C", 1) == 0)
			count += ft_get_color_string(game, map_file->array_content[i], CEILING);
		i++;
	}
	if (count != 2)
		ft_dprintf(2, RED "Error: Failed to load colors: missing elements \n" RESET);
}
