#include "../../includes/cub_3d.h"

/**
 * @brief Parsea una cadena de color RGB y la convierte a un valor entero sin signo
 * @param color_str Cadena con formato "R,G,B" donde R, G, B son valores entre 0-255
 * @return Valor entero sin signo que representa el color en formato RGBA
 */
unsigned int	ft_parse_color_rgb(char *color_str)
{
	char			**rgb_values;
	unsigned int	color;

	rgb_values = ft_split_ae(color_str, ',');
	color = ft_atoi(rgb_values[0]);
	color = (color << 8) + ft_atoi(rgb_values[1]);
	color = (color << 8) + ft_atoi(rgb_values[2]);
	color = (color << 8) + 0xFF;
	return (color);
}

/**
 * @brief Verifica si una cadena contiene únicamente dígitos numéricos
 * @param str Cadena a verificar
 * @return 1 si la cadena contiene solo dígitos, 0 en caso contrario
 * @note Esta función debería moverse a la libft en el futuro
 */
int ft_str_isnumber(char *str) // para pasar a la libft
{
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			ft_dprintf(2, "Error: character '%c' is not a digit.\n", *str);
			return (0);
		}
		str++;
	}
	return (1);
}

/**
 * @brief Determina si una cadena es una ruta de archivo o un color RGB
 * @param str Cadena a analizar
 * @return 1 si es una ruta de archivo, 2 si es un color RGB válido, 0 si es inválido
 * @note Detecta rutas por la presencia del carácter '/'
 * @note Valida colores RGB verificando que sean 3 valores entre 0-255
 */
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
