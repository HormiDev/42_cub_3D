
#include "../../includes/cub_3d.h"
#include <stdbool.h>

/**
 * @brief Verifica si una línea es una directiva del mapa.
 *
 * Esta función comprueba si la línea comienza con alguna de las directivas
 * requeridas para el mapa, como "NO ", "SO ", "EA ", "WE ", "F ", o "C ".
 *
 * @param line Línea a verificar.
 * @return true Si la línea es una directiva.
 * @return false Si la línea no es una directiva.
 */
bool is_directive_line(char *line)
{
	int i;

	i = 0;
    const char *dirs[6] = {"NO ", "SO ", "EA ", "WE ", "F ", "C "};
    while (i < 6)
    {
        if (ft_strncmp_p(line, dirs[i], ft_strlen(dirs[i])) == 0)
            return true;
		i++;
    }
    return false;
}

/**
 * @brief Verifica si una línea contiene solo espacios, tabulaciones o saltos de línea.
 *
 * Esta función recorre cada carácter de la línea y devuelve true si todos los caracteres
 * son espacios, tabulaciones o saltos de línea. De lo contrario, devuelve false.
 *
 * @param line Línea a verificar.
 * @return true Si la línea contiene solo espacios, tabulaciones o saltos de línea.
 * @return false Si la línea contiene algún otro carácter.
 */
static bool is_only_spaces(const char *line)
{
	int j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
			return false;
		j++;
	}
	return true;
}

/**
 * @brief Verifica si todas las directivas requeridas están presentes en el mapa.
 *
 * Esta función comprueba un arreglo de booleanos que indica si cada directiva
 * ha sido encontrada. Si alguna directiva no se encuentra, imprime un mensaje de error
 * y finaliza el programa.
 *
 * @param found Arreglo de booleanos indicando si cada directiva fue encontrada.
 * @param dirs Arreglo de cadenas con los nombres de las directivas requeridas.
 */
static void check_all_directives_found(bool found[6], const char *dirs[6])
{
	int k = 0;
	while (k < 6)
	{
		if (!found[k])
		{
			ft_dprintf(2, RED "Error: Missing texture or color definition: %s\n" RESET, dirs[k]);
			ft_close_game(1);
		}
		k++;
	}
}

/**
 * @brief Encuentra el índice de inicio del mapa en el contenido del archivo.
 *
 * Esta función recorre el contenido del archivo para encontrar la primera línea que
 * contiene un carácter distinto de espacio y verifica la presencia de todas las directivas requeridas.
 * Devuelve el índice de la primera línea del mapa.
 *
 * @param map_file Puntero a la estructura de archivo que contiene el contenido del mapa.
 * @return int El índice de la primera línea del mapa.
 */
int ft_get_map_start_index(t_file *map_file)
{
	int i; 
	int	k;
	bool found[6] = {false, false, false, false, false, false};
	const char *dirs[6] = {"NO ", "SO ", "EA ", "WE ", "F ", "C "};
	
	i = 0; 
	while (map_file->array_content[i])
	{
		if (!is_only_spaces(map_file->array_content[i]))
		{
			k = 0;
			while (k < 6)
			{
				if (ft_strncmp_p(map_file->array_content[i], dirs[k], ft_strlen(dirs[k])) == 0)
				{
					found[k] = true;
					break;
				}
				k++;
			}
			if (k == 6)
				break;
		}
		i++;
	}
	check_all_directives_found(found, dirs);
	return i;
}
