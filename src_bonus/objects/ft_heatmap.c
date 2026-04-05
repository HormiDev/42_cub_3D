#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Marca una posición en el heatmap como objetivo.
 * 
 * Marca tiles válidos (no muros) con calor '2' (máximo) para que el alien
 * sepa que hay un jugador allí. El alien buscará perseguir este calor.
 *
 * @param game estructura del juego.
 * @param px posición X en tiles.
 * @param py posición Y en tiles.
 */
static void	ft_mark_heat(t_game *game, int px, int py)
{
	if (px < 0 || px >= game->width_height[0])
		return ;
	if (py < 0 || py >= game->width_height[1])
		return ;
	if (game->map_heatmap[py][px] == '1')
		return ;
	game->map_heatmap[py][px] = '2';
}

/**
 * @brief Limpia el heatmap de objetivos anteriores.
 * 
 * Restaura las casillas del heatmap a su estado transparente (copiado del
 * grid caminable). Esto evita que el alien persiga posiciones antiguas
 * de jugadores ya muertos o movidos.
 *
 * @param game estructura del juego.
 */
static void	ft_clear_heatmap(t_game *game)
{
	int	y;
	int	x;

	if (!game || !game->map_heatmap || !game->map)
		return ;
	y = 0;
	while (y < game->width_height[1])
	{
		x = 0;
		while (x < game->width_height[0])
		{
			if (game->map_heatmap[y][x] >= '2' && game->map_heatmap[y][x] <= '4')
				game->map_heatmap[y][x] = game->map[y][x];
			x++;
		}
		y++;
	}
}

/**
 * @brief Actualiza el heatmap con posiciones actuales de jugadores vivos.
 * 
 * 1. Primero limpia el heatmap anterior.
 * 2. Marca TODOS los jugadores vivos con calor máximo '2', sin discriminación
 *    por estado (corriendo, caminando o quieto).
 * 3. El alien siempre buscará el calor más cercano o más fuerte.
 *
 * @param game estructura del juego.
 */
void	ft_update_heatmap(t_game *game)
{
	int	i;
	int	px;
	int	py;

	if (!game || !game->map_heatmap)
		return ;
	ft_clear_heatmap(game);
	if (game->player && game->player->alive)
	{
		px = (int)game->player->position.x;
		py = (int)game->player->position.y;
		ft_mark_heat(game, px, py);
	}
	i = 0;
	while (i < game->config.n_players)
	{
		if (game->players[i].active && game->players[i].alive && i != 4)
		{
			px = (int)game->players[i].position.x;
			py = (int)game->players[i].position.y;
			ft_mark_heat(game, px, py);
		}
		i++;
	}
}
