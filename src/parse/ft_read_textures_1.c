#include "../../includes/cub_3d.h"

/**
 * @brief Convierte una cadena hexadecimal a un valor unsigned int.
 * 
 * @param hex_str Cadena con número hexadecimal (por ejemplo: "FF00FF").
 * @return unsigned int Valor numérico convertido.
 */
unsigned int hex_to_uint(const char *hex_str)
{
	unsigned int val = 0;
	while (*hex_str)
	{
		val <<= 4;
		if (*hex_str >= '0' && *hex_str <= '9')
			val |= *hex_str - '0';
		else if (*hex_str >= 'a' && *hex_str <= 'f')
			val |= *hex_str - 'a' + 10;
		else if (*hex_str >= 'A' && *hex_str <= 'F')
			val |= *hex_str - 'A' + 10;
		hex_str++;
	}
	return val;
}

/**
 * @brief Salta espacios y tabulaciones al inicio de una cadena.
 * 
 * @param s Cadena de caracteres a procesar.
 * @return char* Puntero a la primera posición de carácter distinto de espacio/tab.
 */
static char *skip_whitespace(char *s)
{
	while (*s == ' ' || *s == '\t') 
		s++;
	return s;
}

/**
 * @brief Lee la cabecera del archivo XPM y extrae dimensiones y datos del formato.
 * 
 * @param file Puntero a estructura t_file que contiene el contenido del archivo XPM.
 * @param texture Puntero a la estructura t_texture donde se almacenan las dimensiones y datos.
 * @param char_per_pixel Puntero a entero donde se guarda el número de caracteres por píxel.
 * @param line_idx Puntero a entero que indica la línea actual para leer y se actualiza con la siguiente línea.
 * @return int 0 si éxito, -1 si error o formato incorrecto.
 */
static int	read_xpm_header_file(t_file *file, t_texture *texture, int *char_per_pixel, int *line_idx)
{
	char *line;
	char *start;
	char *end;

	while (*line_idx < file->lines)
	{
		line = file->array_content[*line_idx];
		if (ft_strchr(line, '"'))
			break;
		(*line_idx)++;
	}
	if (*line_idx >= file->lines)
		return (-1);
	line = file->array_content[*line_idx];
	start = ft_strchr(line, '"');
	end = ft_strrchr(line, '"');
	if (!start || !end || end <= start)
		return (-1);
	*end = '\0';
	start++;
	if (sscanf(start, "%d %d %d %d", &texture->width, &texture->height,
			&texture->size_colors, char_per_pixel) != 4)
		return (-1);
	(*line_idx)++;
	return (0);
}

/**
 * @brief Parsea una línea de la paleta del XPM para obtener el código de color.
 * 
 * @param line Línea del archivo XPM que contiene el mapeo color->caracteres.
 * @param char_per_pixel Número de caracteres por pixel.
 * @param color Puntero a estructura t_xpm_color donde se guardará el color y el código.
 * @param alloc_list_ptr Puntero a lista de asignaciones para control de memoria.
 * @return int 0 si éxito, -1 si error.
 */
static int	parse_palette_line(char *line, int char_per_pixel, t_xpm_color *color, t_list **alloc_list_ptr)
{
	char	*start = ft_strchr(line, '"');
	char	*end, *hex_start;
	unsigned int rgb_val;

	if (!start || !(end = ft_strrchr(line, '"')) || end <= start)
		return (-1);
	*end = '\0';
	start++;
	color->chars = (char *)ft_malloc_lst_e(alloc_list_ptr, char_per_pixel + 1);
	ft_strncpy(color->chars, start, char_per_pixel);
	color->chars[char_per_pixel] = '\0';
	hex_start = ft_strnstr(start + char_per_pixel, "#", ft_strlen(start + char_per_pixel));
	if (hex_start)
	{
		rgb_val = hex_to_uint(hex_start + 1);
		color->value = 0xFF000000 | rgb_val;
	}
	else if (ft_strnstr(start + char_per_pixel, "None", ft_strlen(start + char_per_pixel)))
		color->value = 0x00000000;
	else
		return (-1);
	return (0);
}

/**
 * @brief Lee la paleta de colores completa del archivo XPM.
 * 
 * @param file Archivo XPM ya cargado en memoria.
 * @param xpm_palette Array donde se almacenarán los colores.
 * @param size_colors Número total de colores a leer.
 * @param char_per_pixel Número de caracteres por pixel.
 * @param alloc_list_ptr Puntero a lista para control de memoria.
 * @param line_idx Puntero al índice actual de línea que se va incrementando.
 * @return int 0 si éxito, -1 si error.
 */
static int	read_xpm_palette_file(t_file *file, t_xpm_color *xpm_palette, int size_colors,
		int char_per_pixel, t_list **alloc_list_ptr, int *line_idx)
{
	int	i = 0;

	while (i < size_colors && *line_idx < file->lines)
	{
		if (parse_palette_line(file->array_content[*line_idx], char_per_pixel,
				&xpm_palette[i], alloc_list_ptr) < 0)
			return (-1);
		i++;
		(*line_idx)++;
	}
	if (i != size_colors)
		return (-1);
	return (0);
}

/**
 * @brief Busca el índice de un color en la paleta según el código de caracteres.
 * 
 * @param xpm_palette Paleta de colores cargada.
 * @param size_colors Número de colores en la paleta.
 * @param pixel_chars Caracteres que representan el color en la línea.
 * @return int Índice del color en la paleta o -1 si no encontrado.
 */
static int find_palette_color(t_xpm_color *xpm_palette, int size_colors, 
								const char *pixel_chars)
{
	int i = 0;

	while (i < size_colors)
	{
		if (ft_strncmp(pixel_chars, xpm_palette[i].chars, strlen(xpm_palette[i].chars)) == 0)
			return (i);
		i++;
	}
	return (-1);
}