#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Configura los parámetros de dibujado del sprite.
 */
static void	ft_setup_sprite_draw(t_game *game, t_objet_draw *draw,
	int screen_col, double base_size, double distance)
{
	draw->size = ft_compute_sprite_size(game, base_size, distance);
	draw->screen_x = screen_col - draw->size / 2;
	if (draw->screen_x < -draw->size)
		draw->screen_x = -draw->size;
	if (draw->screen_x > game->config.render_width)
		draw->screen_x = game->config.render_width;
	draw->screen_y = game->config.render_height / 2 - draw->size / 2
		+ draw->size / 8;
}

/**
 * @brief Renderiza un sprite (alien o jugador) usando técnica billboard.
 */
void	ft_render_player_sprite(t_game *game, t_player *object)
{
	t_objet_draw	draw;
	double			distance;
	int				screen_col;
	t_vector2		diff;

	if (!object->active || !object->texture)
		return ;
	distance = ft_vector_distance(game->player->position, object->position);
	if (distance < 0.3 || distance > (MAX_RAY_SIZE - 0.5))
		return ;
	diff.x = object->position.x - game->player->position.x;
	diff.y = object->position.y - game->player->position.y;
	screen_col = ft_project_sprite_column(game, diff.x, diff.y);
	if (screen_col == INT_MIN)
		return ;
	ft_setup_sprite_draw(game, &draw, screen_col, object->size, distance);
	if (draw.size <= 0)
		return ;
	/* Dibujar directamente escalado y con depth-test por columna, sin textura intermedia */
	ft_draw_image_rgba_scaled_depth(game, game->render, object->texture,
		draw.screen_x, draw.screen_y, draw.size, distance);
}

/**
 * @brief Renderiza todos los sprites visibles en la escena.
 */
void	ft_render_all_sprites(t_game *game)
{
	int			idx;
	int			current_idx;
	int			orig_idx;

	ft_update_render_distances(game);
	ft_get_sorted_players(game);
	current_idx = game->player - game->players;
	idx = 0;
	while (idx < MAX_PLAYERS)
	{
		if (game->ordered_ojects[idx]->active)
		{
			orig_idx = ft_get_original_index(game, game->ordered_ojects[idx]);
			if (orig_idx >= 0 && orig_idx != current_idx)
				ft_render_player_sprite(game, game->ordered_ojects[idx]);
		}
		idx++;
	}
}