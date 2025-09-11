#include "../../includes/cub_3d_bonus.h"

// Declaraciones de funciones auxiliares
static int	ft_row_has_content(char *row);
static int	ft_check_space_surrounded(char **map, int i, int j);

/**
 * @brief Verifica si las filas superior e inferior del mapa están cerradas.
 *
 * Esta función recorre las filas superior e inferior del mapa y verifica que
 * todos los caracteres sean '1' o espacios. Si encuentra algún carácter diferente,
 * devuelve 0. Si ambas filas están correctamente cerradas, devuelve 1.
 *
 * @param game Puntero a la estructura del juego que contiene el mapa.
 * @return int 1 si las filas están cerradas, 0 en caso contrario.
 */
int ft_check_up_down(t_game *game)
{
    int i;
	int last_row;

	i = 0;
	while (game->map[0] && game->map[0][i])
	{
		if (game->map[0][i] != '1' && game->map[0][i] != ' ')
			return (ft_print_map(game->map, i, 0), 0);
		i++;
	}
	last_row = 0;
	while (game->map[last_row])
		last_row++;
	last_row--; // Ajustar al índice de la última fila
	
	// Buscar hacia atrás hasta encontrar una fila con contenido real
	while (last_row >= 0 && game->map[last_row])
	{
		int has_content = 0;
		int j = 0;
		while (game->map[last_row][j])
		{
			if (game->map[last_row][j] != ' ' && game->map[last_row][j] != '\t')
			{
				has_content = 1;
				break;
			}
			j++;
		}
		if (has_content)
			break;
		last_row--;
	}
	
	// Verificar que last_row sea válido
	if (last_row < 0 || !game->map[last_row])
		return (ft_print_map(game->map, 0, 0), 0);
	
	i = 0;
	while (game->map[last_row][i])
	{
		if (game->map[last_row][i] != '1' 
			&& game->map[last_row][i] != ' ')
			return (ft_print_map(game->map, i, last_row), 0);
		i++;
	}
    return (1); 
}

/**
 * @brief Verifica si los bordes izquierdo y derecho del mapa están cerrados.
 *
 * Esta función recorre cada fila del mapa y verifica que el primer y último carácter
 * de cada fila sea '1'. Si encuentra alguna fila que no cumpla con esta condición,
 * devuelve 0. Si todas las filas están correctamente cerradas, devuelve 1.
 *
 * @param map Mapa a verificar.
 * @return int 1 si los bordes están cerrados, 0 en caso contrario.
 */
int ft_check_borders(char **map)
{
    int i;
    int len; 
    int j; 
    int last;

    i = 0; 
    while (map[i])
    {
        if (ft_row_has_content(map[i]))
        {
            len = ft_strlen_p(map[i]);
            j = 0; 
            while(map[i][j] == ' ')
                j++; 
            if(map[i][j] != '1')
                return(ft_print_map(map, j, i), 0);
            last = len - 1;
            while (last > 0 && map[i][last] == ' ')
                last--;
            if (map[i][last] != '1')
                return (ft_print_map(map, last, i), 0);
        }
        i++;
    }
    return (1); 
}

/**
 * @brief Verifica si una fila tiene contenido real (no solo espacios).
 *
 * Esta función auxiliar verifica si una fila contiene caracteres que no sean
 * espacios o tabulaciones.
 *
 * @param row Fila del mapa a verificar.
 * @return int 1 si tiene contenido real, 0 si solo tiene espacios.
 */
static int	ft_row_has_content(char *row)
{
	int	k;

	k = 0;
	while (row[k])
	{
		if (row[k] != ' ' && row[k] != '\t')
			return (1);
		k++;
	}
	return (0);
}

/**
 * @brief Verifica si un espacio está correctamente cerrado.
 *
 * Esta función auxiliar verifica que un espacio vacío esté rodeado por
 * paredes ('1') o por otros espacios vacíos.
 *
 * @param map Mapa a verificar.
 * @param i Índice de fila del espacio.
 * @param j Índice de columna del espacio.
 * @return int 1 si está correctamente cerrado, 0 en caso contrario.
 */
static int	ft_check_space_surrounded(char **map, int i, int j)
{
	if (i > 0 && map[i - 1][j] != 0 && map[i - 1][j] != '1' && map[i - 1][j] != ' ')
		return (ft_print_map(map, j, i - 1), 0);
	if (map[i + 1] && map[i + 1][j] != 0 && map[i + 1][j] != '1' && map[i + 1][j] != ' ')
		return (ft_print_map(map, j, i + 1), 0);
	if (j > 0 && map[i][j - 1] != 0 && map[i][j - 1] != '1' && map[i][j - 1] != ' ')
		return (ft_print_map(map, j - 1, i), 0);
	if (map[i][j + 1] != 0 && map[i][j + 1] != '1' && map[i][j + 1] != ' ')
		return (ft_print_map(map, j + 1, i), 0);
	return (1);
}

/**
 * @brief Verifica si el mapa está cerrado internamente.
 *
 * Esta función recorre el mapa y verifica que cada espacio vacío (' ')
 * esté rodeado por paredes ('1') o por otros espacios vacíos. Si encuentra
 * un espacio vacío que no cumple con esta condición, devuelve 0.
 *
 * @param map Mapa a verificar.
 * @return int 1 si el mapa está cerrado, 0 en caso contrario.
 */
int	ft_check_map_closed_in(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		if (ft_row_has_content(map[i]))
		{
			j = 0;
			while (map[i][j])
			{
				if (map[i][j] == ' ')
				{
					if (!ft_check_space_surrounded(map, i, j))
						return (0);
				}
				j++;
			}
		}
		i++;
	}
	return (1);
}

/**
 * @brief Verifica si el mapa está cerrado.
 *
 * Esta función comprueba si el mapa cumple con las siguientes condiciones:
 * 1. Las filas superior e inferior están completamente cerradas con '1'.
 * 2. Los bordes izquierdo y derecho de cada fila están cerrados con '1'.
 * 3. No hay espacios vacíos que no estén rodeados por paredes.
 *
 * @param game Puntero a la estructura del juego que contiene el mapa.
 * @return int 1 si el mapa está cerrado, 0 en caso contrario.
 */
int ft_check_map_closed(t_game *game)
{
    if(!ft_check_up_down(game))
        return (0);
    if(!ft_check_borders(game->map))
        return (0);
    if(!ft_check_map_closed_in(game->map))
        return (0);
    return (1);
}
