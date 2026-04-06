#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Verifica si el player está en FOV 180° dentro de 10 unidades y sin obstáculos.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param target puntero al jugador.
 * @return 1 si está en rango, FOV y sin muros en el camino, 0 si no.
 */
static int	ft_is_player_visible(t_game *game, t_player *alien, t_player *target)
{
	double		dist;
	double		angle_to_target;
	double		angle_diff;
	double		step_x;
	double		step_y;
	double		current_x;
	double		current_y;
	int			steps;
	int			i;

	dist = ft_vector_distance(alien->position, target->position);
	if (dist > 10.0)
		return (0);
	
	angle_to_target = atan2(target->position.y - alien->position.y,
			target->position.x - alien->position.x) * 180.0 / M_PI;
	angle_to_target = ft_normalize_angle(angle_to_target);
	angle_diff = ft_normalize_relative_angle(angle_to_target - alien->rotation.x);
	if (angle_diff < -90.0 || angle_diff > 90.0)
		return (0);
	
	steps = (int)(dist * 2);
	if (steps < 1)
		steps = 1;
	step_x = (target->position.x - alien->position.x) / steps;
	step_y = (target->position.y - alien->position.y) / steps;
	current_x = alien->position.x;
	current_y = alien->position.y;
	
	i = 0;
	while (i < steps)
	{
		current_x += step_x;
		current_y += step_y;
		if (game->map_heatmap[(int)current_y][(int)current_x] == -1)
			return (0);
		i++;
	}
	
	return (1);
}

/**
 * @brief Persigue al jugador en linea recta respetando colisiones.
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @param target jugador a perseguir.
 */
static void	ft_move_toward_player(t_game *game, t_player *alien, t_player *target)
{
	double		angle;
	double		move_dist;
	double		next_x;
	double		next_y;
	int			tile_x;
	int			tile_y;

	angle = atan2(target->position.y - alien->position.y,
			target->position.x - alien->position.x) * 180.0 / M_PI;
	angle = ft_normalize_angle(angle);
	alien->rotation.x = angle;
	move_dist = alien->speed * game->delta_time;
	next_x = alien->position.x + ft_cos(angle * M_PI / 180.0) * move_dist;
	next_y = alien->position.y + ft_sin(angle * M_PI / 180.0) * move_dist;
	tile_x = (int)next_x;
	tile_y = (int)next_y;
	if (tile_x >= 0 && tile_x < game->width_height[0] && 
		tile_y >= 0 && tile_y < game->width_height[1] &&
		game->map_heatmap[tile_y][tile_x] != -1)
	{
		alien->position.x = next_x;
		alien->position.y = next_y;
	}
}


/**
 * @brief Actualiza el estado CHASE del alien.
 * @param game estructura del juego.
 * @param alien puntero al alien a actualizar.
 */
void	ft_alien_chase_update(t_game *game, t_player *alien)
{
	t_player	*closest;
	double		closest_dist;
	double		dist;
	int			i;

	if (!alien || !game)
		return ;
	
	closest = NULL;
	closest_dist = 999.0;
	
	if (game->player && game->player->alive)
	{
		if (ft_is_player_visible(game, alien, game->player))
		{
			closest = game->player;
			closest_dist = ft_vector_distance(alien->position, game->player->position);
		}
	}
	
	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive)
		{
			if (ft_is_player_visible(game, alien, &game->players[i]))
			{
				dist = ft_vector_distance(alien->position, game->players[i].position);
				if (dist < closest_dist)
				{
					closest = &game->players[i];
					closest_dist = dist;
				}
			}
		}
		i++;
	}
	
	if (!closest)
	{
		alien->state = ALIEN_PATROL;
		alien->path_len = 0;
		return ;
	}
	
	alien->path_len = 0;
	ft_move_toward_player(game, alien, closest);
}
