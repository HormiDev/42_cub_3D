#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Realiza raycasting para detectar si hay línea directa al jugador.
 * 
 * Usa ft_raycast para disparar un rayo desde la posición del alien hacia
 * el jugador. Si el rayo toca al jugador (distance < 0.5) retorna 1.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien.
 * @return 1 si hay visión directa, 0 si no.
 */
static int	ft_has_line_of_sight(t_game *game, t_player *alien)
{
	t_vector2	delta;
	double		angle;
	t_raycast	ray;
	double		target_dist;

	delta.x = game->player->position.x - alien->position.x;
	delta.y = game->player->position.y - alien->position.y;
	angle = atan2(delta.y, delta.x);
	target_dist = ft_vector_distance(alien->position, game->player->position);
	ft_raycast(game, angle, &ray, target_dist + 1.0);
	if (ray.distance < target_dist + 0.5)
		return (1);
	return (0);
}

/**
 * @brief Persigue al jugador en línea recta con velocidad constante.
 * 
 * Calcula el vector dirección normalizado hacia el jugador.
 * Mueve el alien a velocidad constante en esa dirección.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien a mover.
 */
static void	ft_move_toward_player(t_game *game, t_player *alien)
{
	t_vector2	direction;
	double		norm;

	direction.x = game->player->position.x - alien->position.x;
	direction.y = game->player->position.y - alien->position.y;
	norm = ft_sqrt(direction.x * direction.x + direction.y * direction.y);
	if (norm > 0.001)
	{
		direction.x /= norm;
		direction.y /= norm;
	}
	alien->position.x += direction.x * alien->speed * game->delta_time;
	alien->position.y += direction.y * alien->speed * game->delta_time;
}

/**
 * @brief Actualiza el estado CHASE del alien.
 * 
 * Verifica línea directa de visión. Si está disponible, persigue al jugador.
 * Si pierde visión, cambia a estado PATROL.
 *
 * @param game estructura del juego.
 * @param alien puntero al alien.
 */
void	ft_alien_chase_update(t_game *game, t_player *alien)
{
	if (!alien || !game || !game->player)
		return ;
	if (!ft_has_line_of_sight(game, alien))
	{
		alien->state = ALIEN_PATROL;
		alien->path_len = 0;
		return ;
	}
	alien->path_len = 0;
	ft_move_toward_player(game, alien);
}
