#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Actualiza el estado del alien según su distancia al jugador.
 */
void	ft_update_aliens(t_game *game)
{
	t_player	*alien;
	double		distance;

	if (!game->players[4].active)
		return ;
	alien = &game->players[4];
	distance = ft_vector_distance(game->player->position, alien->position);
	if (distance <= alien->chase_distance)
		alien->state = ALIEN_CHASE;
	else
		alien->state = ALIEN_IDLE;
}

/**
 * @brief Actualiza las distancias de render de todos los jugadores.
 */
void	ft_update_render_distances(t_game *game)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (game->players[i].active)
			game->players[i].render_distance = ft_vector_distance(
				game->player->position, game->players[i].position);
		i++;
	}
}
