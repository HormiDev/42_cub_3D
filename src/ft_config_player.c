/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/13 20:29:34 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

/**
 * @brief Configura la posición y rotación del jugador en el mapa.
 *
 * Esta función recorre el mapa del juego para encontrar la posición del jugador
 * representada por los caracteres 'N', 'S', 'E' o 'W'. Establece la posición y
 * rotación del jugador según el carácter encontrado, y luego reemplaza el carácter
 * en el mapa con '0'.
 *
 * @param game Puntero a la estructura del juego que contiene el mapa y la información del jugador.
 */
void	ft_config_player(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.position.x = j + 0.5;
				game->player.position.y = i + 0.5;
				game->player.reverse_y_position = -game->player.position.y + game->width_height[1];
				if (game->map[i][j] == 'N')
					game->player.rotation.x = 90.0;
				else if (game->map[i][j] == 'S')
					game->player.rotation.x = 270.0;
				else if (game->map[i][j] == 'E')
					game->player.rotation.x = 0.0;
				else if (game->map[i][j] == 'W')
					game->player.rotation.x = 180.0;
				game->map[i][j] = '0';
			} 
			j++;
		}
		i++;
	}
}
