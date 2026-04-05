/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_transitable_gen.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:46 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/05 23:31:19 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Alloca memoria para el mapa transitable.
 *
 * @param game estructura del juego.
 */
static void	ft_alloc_map_transitable(t_game *game)
{
	int	i;
	int	rows;
	int	cols;

	rows = game->width_height[1];
	cols = game->width_height[0];
	game->map_transitable = hd_calloc(rows + 1, sizeof(char *));
	i = 0;
	while (i < rows)
	{
		game->map_transitable[i] = hd_calloc(cols + 1, sizeof(char));
		i++;
	}
	game->map_transitable[rows] = NULL;
}

/**
 * @brief Llena el mapa transitable marcando puntos caminables.
 *
 * Marca espacios abiertos como '0' (transitables, base para mapa de calor)
 * y muros/puertas como '1' (no transitables).
 *
 * @param game estructura del juego.
 */
static void	ft_fill_map_transitable(t_game *game)
{
	int	i;
	int	j;
	int	rows;
	int	cols;

	rows = game->width_height[1];
	cols = game->width_height[0];
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (game->map[i][j] == '0' || game->map[i][j] == 'N' 
				|| game->map[i][j] == 'S' || game->map[i][j] == 'E' 
				|| game->map[i][j] == 'W')
				game->map_transitable[i][j] = '0';
			else
				game->map_transitable[i][j] = '1';
			j++;
		}
		i++;
	}
}

/**
 * @brief Crea una copia del mapa marcando puntos transitables.
 *
 * Copia el mapa original y marca todos los espacios abiertos como '0',
 * y todos los muros/puertas como '1'. Esto facilita crear un mapa de calor
 * donde los '0s' pueden incrementarse (1, 2, 3...) según la presencia de jugadores.
 *
 * @param game estructura del juego.
 */
void	ft_create_map_transitable(t_game *game)
{
	if (!game || !game->map)
		return ;
	
	ft_alloc_map_transitable(game);
	ft_fill_map_transitable(game);
}

/**
 * @brief Imprime el mapa transitable en terminal para debug.
 *
 * @param game estructura del juego.
 */
void	ft_print_transitable_map(t_game *game)
{
	int	i;
	int	j;

	if (!game || !game->map_transitable)
		return ;
	
	ft_dprintf(1, "\n=== MAPA TRANSITABLE ===\n");
	i = 0;
	while (game->map_transitable[i])
	{
		j = 0;
		while (game->map_transitable[i][j])
		{
			ft_dprintf(1, "%c", game->map_transitable[i][j]);
			j++;
		}
		ft_dprintf(1, "\n");
		i++;
	}
	ft_dprintf(1, "========================\n\n");
}
