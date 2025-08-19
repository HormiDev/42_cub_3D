#include "../../includes/cub_3d.h"

/**
 * @brief Realiza la operación principal de la función seleccionada.
 * 
 * @param parametro1 Descripción del primer parámetro.
 * @param parametro2 Descripción del segundo parámetro.
 */
void	ft_check_map_valid_characters(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' 
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
			{
				ft_dprintf(2, "%sError: %c Invalid character in map\n%s", RED, map[i][j], RESET);
				ft_close_game(1);
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Cuenta el número de jugadores en el mapa.
 * 
 * Recorre el mapa y cuenta cuántas veces aparecen los caracteres que representan
 * a los jugadores ('N', 'S', 'E', 'W'). Debe haber exactamente un jugador.
 * 
 * @param game Puntero a la estructura del juego que contiene el mapa.
 * @return int Número de jugadores encontrados en el mapa.
 */
int	ft_check_map_count_player(t_game *game)
{
	int i;
	int j;
	int player_count;

	i = 0;
	player_count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' 
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count);
}

/**
 * @brief Verifica si el mapa está cerrado.
 * 
 * Comprueba si el mapa está cerrado, es decir, si todas las áreas accesibles
 * están rodeadas por paredes ('1'). Si el mapa no está cerrado, se imprime un
 * mensaje de error y se cierra el juego.
 * 
 * @param game Puntero a la estructura del juego que contiene el mapa.
 * @return int 1 si el mapa está cerrado, 0 si no lo está.
 */
void	ft_check_map(t_game *game)
{
	int player_count;

	ft_check_map_valid_characters(game->map);
	player_count = ft_check_map_count_player(game);
	if (player_count != 1)
	{
		if (player_count < 1)
			ft_dprintf(2, "%sError: No player found in map%s", RED, RESET);
		else
		{
			ft_dprintf(2, "%sError: More than one player found in map\n", RED);
			ft_dprintf(2, RESET);
		}
		ft_close_game(1);
	}
	
	if(!ft_check_map_closed(game))
	{
		ft_dprintf(2, RED "Error: Map is not closed\n" RESET);
		ft_close_game(1);
	}	
}