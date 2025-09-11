#include "../../includes/cub_3d_bonus.h"

/**
 * @file ft_read_textures.c
 * @brief Funciones para leer y analizar texturas desde archivos XPM.
 *
 * Este archivo contiene funciones para manejar la lectura de texturas desde archivos XPM,
 * incluyendo la verificación de argumentos y el conteo de caracteres en cadenas.
 */
size_t	ft_count_char(const char *str, char c)
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief validate_xpm_line - Verifica si una línea de un archivo XPM es válida.
 *
 * Esta función comprueba que una línea de un archivo XPM contenga comillas y que tenga
 * el formato correcto para ser interpretada como una línea de definición de color.
 *
 * @param line Línea del archivo XPM a validar.
 */
static void	validate_xpm_line(char *line)
{
	char	*start_quote;
	char	*sub_str;

	start_quote = ft_strchr(line, '\"');
	if (!ft_strchr(start_quote + 1, '\"'))
	{
		ft_dprintf(2, RED "Error: Invalid XPM: The quote is not closed: %s\n" RESET, line);
		ft_close_game(1);
	}
	sub_str = ft_substr_ae(start_quote + 1, 0,
			ft_strchr(start_quote + 1, '\"') - start_quote - 1);
	if (ft_splitlen(ft_split_ae(sub_str, ' ')) < 4)
	{
		ft_dprintf(2, "Error: Invalid XPM file format in line: %s\n", line);
		ft_close_game(1);
	}
}

/**
 * @brief check_arguments_xpm - Verifica los argumentos de un archivo XPM.
 *
 * Esta función abre un archivo XPM y valida cada línea para asegurarse de que cumple
 * con el formato esperado. Si se encuentra un error, se imprime un mensaje y se cierra el juego.
 *
 * @param path Ruta del archivo XPM a verificar.
 */
void	check_arguments_xpm(char *path)
{
	t_file		*file;
	t_strlist	*current;

	file = ft_create_file_from_filename(path);
	if (!file)
	{
		ft_dprintf(2, RED "Error: Failed to open XPM file: %s\n" RESET, path);
		ft_close_game(1);
	}
	current = file->list_content;
	while (current)
	{
		if (ft_strchr(current->str, '\"'))
		{
			validate_xpm_line(current->str);
			return ;
		}
		current = current->next;
	}
}

