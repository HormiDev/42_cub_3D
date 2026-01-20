#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Oculta columnas del sprite que están detrás de paredes.
 */
void	ft_mask_alien_by_depth(t_game *game, t_texture *scaled,
	int screen_x, double alien_distance)
{
	int	x;
	int	ray_index;
	int	y;

	x = 0;
	while (x < scaled->width)
	{
		ray_index = game->config.render_width - (screen_x + x) - 1;
		if (screen_x + x < 0 || screen_x + x >= game->config.render_width
			|| ray_index < 0 || ray_index >= game->config.render_width
			|| (alien_distance - 0.3) >= game->raycasts[ray_index].distance)
		{
			y = 0;
			while (y < scaled->height)
				scaled->colors_matrix[y++][x] = 0x00FFFFFF;
		}
		x++;
	}
}

/**
 * @brief Calcula el tamaño del sprite en pantalla según la distancia.
 */
int	ft_compute_sprite_size(t_game *game, double base_size, double distance)
{
	int	size;

	size = (int)((base_size * game->config.render_height) / distance);
	if (size < MIN_ALIEN_SIZE)
		size = MIN_ALIEN_SIZE;
	if (size > game->config.render_height)
		size = game->config.render_height;
	return (size);
}

/**
 * @brief Obtiene los datos de un jugador para renderizar.
 */
int	ft_get_player_data(t_player *player, t_vector2 *pos,
	double *base_size, t_texture **tex)
{
	if (!player->active || !player->texture)
		return (0);
	*pos = player->position;
	*base_size = player->size;
	*tex = player->texture;
	return (1);
}
