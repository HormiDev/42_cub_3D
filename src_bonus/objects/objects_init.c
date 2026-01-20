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
}

/**
 * @brief Carga la textura del alien desde disco.
 */
static void	ft_load_alien_texture(t_game *game, t_player *alien)
{
	check_arguments_xpm("textures/alien.xpm");
	alien->texture = ft_loading_texture(game->mlx, "textures/alien.xpm");
	if (!alien->texture)
	{
		ft_dprintf(2, RED "Error: Failed to load alien texture\n" RESET);
		ft_close_game(1);
	}
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
			game->players[k].texture = game->players[4].texture;
			game->players[k].size = 2.0;
		}
		k++;
	}
}

/**
 * @brief Busca y configura aliens en el mapa.
 */
void	ft_config_aliens(t_game *game)
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
