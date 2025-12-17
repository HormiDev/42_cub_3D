/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:30:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/17 03:01:21 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Establece la rotación del jugador según el carácter de dirección.
 *
 * Esta función estática configura la rotación del jugador basándose en el carácter
 * que representa la dirección inicial ('N', 'S', 'E', 'W').
 *
 * @param game Puntero a la estructura del juego.
 * @param direction_char Carácter que representa la dirección ('N', 'S', 'E', 'W').
 */
static void	ft_set_player_rotation(t_game *game, char direction_char)
{
	if (direction_char == 'N')
		game->player->rotation.x = 90.0;
	else if (direction_char == 'S')
		game->player->rotation.x = 270.0;
	else if (direction_char == 'E')
		game->player->rotation.x = 0.0;
	else if (direction_char == 'W')
		game->player->rotation.x = 180.0;
	// Normalizar el ángulo por consistencia
	game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
}

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
	game->players = ft_alloc_lst(sizeof(t_player) * 4, 3);
	game->player = &game->players[0];
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player->position.x = j + 0.5;
				game->player->position.y = i + 0.5;
				game->player->reverse_y_position = -game->player->position.y + game->width_height[1];
				ft_set_player_rotation(game, game->map[i][j]);
				game->map[i][j] = '0';
			} 
			j++;
		}
		i++;
	}
	ft_memcpy(&game->players[1], &game->players[0], sizeof(t_player));
	game->players[1].position.x += 0.3;
	ft_memcpy(&game->players[2], &game->players[0], sizeof(t_player));
	game->players[2].position.x -= 0.3;
	ft_memcpy(&game->players[3], &game->players[0], sizeof(t_player));
	game->players[3].position.y += 0.3;
}
