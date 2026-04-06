# include "../includes/cub_3d.h"

/**
 * @brief Imprime una celda del mapa con color si es un error.
 *
 * @param map el mapa.
 * @param i fila actual.
 * @param j columna actual.
 * @param error_y fila del error (-1 si no hay).
 * @param error_x columna del error (-1 si no hay).
 */
static void	ft_print_cell(char **map, int i, int j, int error_y, int error_x)
{
    if (i == error_y && j == error_x)
    {
        if (ft_isprint(map[i][j]))
            ft_dprintf(2, "%s%c%s", RED, map[i][j], RESET);
        else
            ft_dprintf(2, "%s%c%s", RED, '?', RESET);
    }
    else
        ft_dprintf(1, "%c", map[i][j]);
}

/**
 * @brief Imprime un mapa completo con errores resaltados.
 *
 * @param map el mapa a imprimir.
 * @param error_x columna del error (-1 si no hay).
 * @param error_y fila del error (-1 si no hay).
 */
void	ft_print_map(char **map, int error_x, int error_y)
{
    int	i;
    int	j;

    if (error_x != -1 || error_y != -1)
        ft_dprintf(2, "%sError: in %d, %d\n%s", RED, error_y + 1, error_x + 1, RESET);
    if (!map)
    {
        ft_dprintf(2, "Map: (null)\n");
        return ;
    }
    ft_dprintf(2, "Map:\n");
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            ft_print_cell(map, i, j, error_y, error_x);
            j++;
        }
        ft_dprintf(1, "\n");
        i++;
    }
}
