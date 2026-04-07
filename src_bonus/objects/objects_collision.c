/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 19:50:00 by nirmata          #+#    #+#             */
/*   Updated: 2026/04/04 20:00:00 by nirmata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	ft_can_alien_hit_player(t_game *game, t_player *alien,
	t_player *player)
{
	double	dx;
	double	dy;
	double	distance;
	int		mid_x;
	int		mid_y;

	dx = player->position.x - alien->position.x;
	dy = player->position.y - alien->position.y;
	distance = ft_sqrt(dx * dx + dy * dy);
	if (distance < 0.8)
		return (1);
	if (distance > 1.05)
		return (0);
	mid_x = (int)((player->position.x + alien->position.x) * 0.5);
	mid_y = (int)((player->position.y + alien->position.y) * 0.5);
	if (ft_is_wall_or_closed_door(game, mid_x, mid_y))
		return (0);
	return (1);
}

/**
 * @brief Mata a un jugador y lo marca como inactivo.
 *
 * Cambia el estado del jugador a muerto (alive = 0) y lo marca como inactivo
 * para que no aparezca más en el rendering.
 *
 * @param player puntero al jugador a matar.
 */
void	ft_kill_player(t_player *player)
{
	if (!player || !player->alive)
		return ;
	player->alive = 0;
	//player->active = 0;
}

/**
 * @brief Verifica colisiones entre el alien y todos los jugadores.
 *
 * Revisa si el alien ha colisionado con algún jugador vivo. Si detecta una
 * colisión, mata al jugador.
 *
 * @param game estructura del juego.
 */
void	ft_check_alien_collision(t_game *game)
{
	t_player	*alien;
	int			i;

	if (!game)
		return ;
	alien = &game->players[4];
	if (!alien->active)
		return ;
	i = 0;
	while (i < game->config.n_players && i < 4)
	{
		if (game->players[i].alive
			&& ft_can_alien_hit_player(game, alien, &game->players[i]))
			ft_kill_player(&game->players[i]);
		i++;
	}
}

/**
 * @brief Cuenta cuántos jugadores están vivos.
 *
 * Itera sobre todos los jugadores y cuenta cuántos tienen alive = 1.
 *
 * @param game estructura del juego.
 * @return cantidad de jugadores vivos.
 */
static int	ft_count_alive_players(t_game *game)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < game->config.n_players && i < 4)
	{
		if (game->players[i].alive)
			count++;
		i++;
	}
	return (count);
}

/**
 * @brief Verifica si el juego ha terminado.
 *
 * El juego termina cuando:
 * - Todos los jugadores mueren (alien gana)
 * - Se completa el tiempo sin que el alien mate a todos (jugadores ganan)
 *
 * Actualiza game->game_state accordingly.
 *
 * @param game estructura del juego.
 * @return 1 si el juego ha terminado, 0 si sigue en progreso.
 */
int	ft_check_game_end(t_game *game)
{
	int	alive_players;

	if (!game)
		return (0);
	alive_players = ft_count_alive_players(game);
	if (alive_players == 0)
	{
		game->game_state = GAME_ALIEN_WIN;
		ft_dprintf(1, "%s[GAME OVER] Alien wins! All players eliminated!%s\n",
			RED, RESET);
		return (1);
	}
	return (0);
}

/**
 * @brief Dibuja información de debug del alien en pantalla.
 *
 * Muestra:
 * - Estado actual del alien (IDLE, PATROL, CHASE)
 * - Posición (X, Y)
 * - Distancia al jugador principal
 * - Velocidad
 * - Sentido del raycast (ángulo)
 *
 * @param game estructura del juego.
 */
void	ft_debug_alien(t_game *game)
{
	t_player	*alien;
	t_player	*player;
	double		distance;
	char		state_str[32];
	char		debug_buffer[256];

	if (!game || !game->players[4].active)
		return ;
	alien = &game->players[4];
	player = game->player;
	distance = ft_vector_distance(player->position, alien->position);
	if (alien->state == ALIEN_IDLE)
		ft_strlcpy(state_str, "IDLE", 32);
	else if (alien->state == ALIEN_PATROL)
		ft_strlcpy(state_str, "PATROL", 32);
	else if (alien->state == ALIEN_CHASE)
		ft_strlcpy(state_str, "CHASE", 32);
	else
		ft_strlcpy(state_str, "UNKNOWN", 32);
	ft_sprintf(debug_buffer,
		"[ALIEN] State: %s | Pos: (%d,%d) | Dist: %d",
		state_str, (int)alien->position.x, (int)alien->position.y, (int)distance);
	mlx_string_put(game->mlx, game->window, 10, 70, 0x00FF00, debug_buffer);
	ft_sprintf(debug_buffer,
		"[PATH] Len: %d | Step: %d | LastHeat: (%d,%d)",
		alien->path_len, alien->curr_step,
		alien->last_heatmap_pos.x, alien->last_heatmap_pos.y);
	mlx_string_put(game->mlx, game->window, 10, 90, 0x00FF00, debug_buffer);
	ft_sprintf(debug_buffer, "[PLAYERS] Alive: %d/%d",
		ft_count_alive_players(game), game->config.n_players);
	mlx_string_put(game->mlx, game->window, 10, 110, 0xFFFF00, debug_buffer);
}
