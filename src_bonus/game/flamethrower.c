#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Calcula si un alien está dentro del rango de ataque del lanzallamas.
 *
 * Utiliza la distancia euclidiana para determinar si la distancia entre el jugador
 * y el alien es menor o igual a 5.0 unidades.
 *
 * @param player Puntero a la estructura del jugador atacante.
 * @param alien Puntero a la estructura del alien a verificar.
 * @return 1 si el alien está en rango, 0 en caso contrario.
 */
static int	is_alien_in_range(t_player *player, t_alien *alien)
{
	double	dx;
	double	dy;
	double	dist;

	dx = player->position.x - alien->position.x;
	dy = player->position.y - alien->position.y;
	dist = ft_sqrt(dx * dx + dy * dy);
	return (dist <= 5.0);
}

/**
 * @brief Verifica si el lanzallamas está en cooldown y puede volver a disparar.
 *
 * Compara el tiempo actual con el timestamp del último disparo. Si la diferencia
 * es menor a 2.0 segundos, calcula el tiempo restante de cooldown y devuelve 0.
 * Si el cooldown ha expirado, devuelve 1 para permitir el siguiente disparo.
 *
 * @param actions Puntero a la estructura de acciones del jugador con datos del lanzallamas.
 * @return 1 si el cooldown ha expirado y se puede disparar, 0 si aún está en cooldown.
 */
static int	ft_check_flamethrower_cooldown(t_player_actions *actions)
{
	long	current_time;
	double	time_diff_seconds;

	if (actions->flamethrower_last_time != 0)
	{
		current_time = ft_get_time();
		time_diff_seconds = (current_time - actions->flamethrower_last_time) / 1000.0;
		if (time_diff_seconds < 2.0)
		{
			actions->flamethrower_cooldown_remaining = 2.0 - time_diff_seconds;
			return (0);
		}
	}
	return (1);
}

/**
 * @brief Ejecuta el ataque del lanzallamas contra aliens en rango.
 *
 * Decrementa el contador de cargas, actualiza el timestamp del último disparo,
 * inicia el cooldown y busca aliens dentro del rango de ataque para desactivarlos.
 * Solo desactiva el primer alien que encuentre en rango.
 *
 * @param game Puntero a la estructura del juego.
 * @param player Puntero a la estructura del jugador que dispara.
 * @param actions Puntero a la estructura de acciones donde se actualizan datos del lanzallamas.
 */
static void	ft_flamethrower_attack(t_game *game, t_player *player,
		t_player_actions *actions)
{
	int	i;

	actions->flamethrower_charges--;
	actions->flamethrower_ready = 0;
	actions->flamethrower_last_time = ft_get_time();
	actions->flamethrower_cooldown_remaining = 2.0;
	
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (game->players[i].type == ENTITY_ALIEN)
		{
			if (is_alien_in_range(player, (t_alien *)&game->players[i]))
			{
				game->players[i].active = 0;
				break ;
			}
		}
		i++;
	}
}

/**
 * @brief Interfaz principal para disparar el lanzallamas del jugador.
 *
 * Valida que el jugador tenga cargas disponibles, verifica que el cooldown
 * haya expirado y ejecuta el ataque si estas condiciones se cumplen.
 * Llamada cuando el jugador hace click con el ratón.
 *
 * @param game Puntero a la estructura del juego.
 * @param player_index Índice del jugador en el array de jugadores.
 */
void	flamethrower(t_game *game, int player_index)
{
	t_player		*player;
	t_player_actions	*actions;

	player = &game->players[player_index];
	actions = &game->actions[player_index];
	
	if (actions->flamethrower_charges <= 0)
		return ;
	
	if (!ft_check_flamethrower_cooldown(actions))
		return ;
	
	ft_flamethrower_attack(game, player, actions);
}

/**
 * @brief Actualiza el estado del cooldown del lanzallamas en cada frame.
 *
 * Decrementa el tiempo restante de cooldown basándose en el delta_time del frame.
 * Cuando el cooldown llega a 0, marca el lanzallamas como listo (flamethrower_ready = 1).
 * Si no hay cooldown activo y aún hay cargas disponibles, el lanzallamas está listo para disparar.
 *
 * @param actions Puntero a la estructura de acciones del jugador.
 * @param delta_time Tiempo transcurrido en el frame actual (en segundos).
 */
void	ft_update_flamethrower_cooldown(t_player_actions *actions, double delta_time)
{
	if (actions->flamethrower_cooldown_remaining > 0)
	{
		actions->flamethrower_cooldown_remaining -= delta_time;
		if (actions->flamethrower_cooldown_remaining <= 0)
		{
			actions->flamethrower_cooldown_remaining = 0;
			actions->flamethrower_ready = 1;
		}
	}
	else if (actions->flamethrower_charges < 3)
		actions->flamethrower_ready = 1;
}