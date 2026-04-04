/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:23:51 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/04 01:37:14 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Inicializa los datos del alien en su posición inicial.
 */
static void	ft_init_alien_data(t_player *alien, double x, double y)
{
	alien->type = ENTITY_ALIEN;
	alien->active = 1;
	alien->position.x = x;
	alien->position.y = y;
	alien->state = ALIEN_IDLE;
	alien->speed = 1.2;
	alien->chase_distance = 4.0;
	alien->size = 2.0;
	alien->path_len = 0;
	alien->curr_step = 0;
	alien->last_heatmap_pos.x = -1;
	alien->last_heatmap_pos.y = -1;
}

/**
 * @brief Carga la textura del alien desde disco.
 */
static void	ft_load_alien_texture(t_game *game, t_player *alien)
{
	alien->model = game->alien_prerender;
}

/**
 * @brief Crea un alien en la posición especificada del mapa.
 */
static void	ft_spawn_alien(t_game *game, int x, int y)
{
	ft_init_alien_data(&game->players[4], x + 0.5, y + 0.5);
	ft_load_alien_texture(game, &game->players[4]);
	game->map[y][x] = '0';
}

/**
 * @brief Asigna texturas a todos los jugadores activos.
 */
static void	ft_assign_textures_to_players(t_game *game)
{
    int	k;

    k = 0;
    while (k < MAX_PLAYERS)
    {
        if (k != 4 && game->players[k].active)
        {
            game->players[k].model = game->players[4].model;
            game->players[k].size = 2.0;
        }
        k++;
    }
}

/**
 * @brief Busca y configura aliens en el mapa.
 */
void	ft_config_objects(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'A')
			{
				ft_spawn_alien(game, j, i);
				ft_assign_textures_to_players(game);
				return ;
			}
			j++;
		}
		i++;
	}
}
