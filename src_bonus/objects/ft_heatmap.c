#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Obtiene el valor de calor en una posición del mapa original.
 * 
 * Devuelve '2' (corre), '3' (camina), '4' (quieto), o '0' (sin rastro).
 * Respeta paredes ('1').
 *
 * @param game estructura del juego.
 * @param tx posición X en tiles del mapa.
 * @param ty posición Y en tiles del mapa.
 * @return valor '0'-'4' o '1' si es pared.
 */
static char	ft_get_tile_heat(t_game *game, int tx, int ty)
{
	if (!game || !game->map_original)
		return ('0');
	if (tx < 0 || tx >= game->width_height[0] || ty < 0 || ty >= game->width_height[1])
		return ('0');
	if (game->map_original[ty][tx] == ' ' || game->map_original[ty][tx] == '0')
		return (game->map_original[ty][tx]);
	return ('1');
}

/**
 * @brief Marca la casilla actual del jugador en el mapa original.
 * 
 * Actualiza el heatmap consultando game->map_original. Marca '2' si corre,
 * '3' si camina, '4' si está quieto. No sobrescribe paredes ('1').
 *
 * @param game estructura del juego con posición del jugador.
 * @param player_idx índice del jugador (0 = principal).
 */
void	ft_update_heatmap(t_game *game, int player_idx)
{
	int		px;
	int		py;
	char	heat;

	if (!game || !game->player || !game->map_original)
		return ;
	px = (int)game->player->position.x;
	py = (int)game->player->position.y;
	if (px < 0 || px >= game->width_height[0])
		return ;
	if (py < 0 || py >= game->width_height[1])
		return ;
	if (game->map_original[py][px] == '1')
		return ;
	heat = '4';
	if (game->is_running)
		heat = '2';
	else if (game->is_walking)
		heat = '3';
	game->map_original[py][px] = heat;
}
