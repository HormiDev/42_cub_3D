#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Configura los parámetros de dibujado del sprite.
 */
static void	ft_setup_sprite_draw(t_game *game, t_objet_draw *draw,
	int screen_col, double base_size, double distance)//funcion para borrar
{
	draw->size = ft_compute_sprite_size(game, base_size, distance);
	//draw->scaled = ft_new_texture(game->mlx, draw->size, draw->size);
	draw->screen_x = screen_col - draw->size / 2;

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
	draw.scaled = object->texture;
	distance = ft_vector_distance(game->player->position, object->position);
	if (distance < 0.3 || distance > (MAX_RAY_SIZE - 0.5))
		return ;
	diff.x = object->position.x - game->player->position.x;
	diff.y = object->position.y - game->player->position.y;
	screen_col = ft_project_sprite_column(game, diff.x, diff.y, &distance);
	if (screen_col == INT_MIN)
		return ;
	ft_setup_sprite_draw(game, &draw, screen_col, object->size, distance);
	//ft_draw_image_rgba_scaled(game->render, draw.scaled, draw.screen_x, draw.screen_y, draw.size);
	ft_draw_image_rgba_scaled_plus(game->render, draw.scaled, draw.screen_x, draw.screen_y, draw.size, distance);
	//ft_scale_t_image(object->texture, draw.scaled);
	//ft_mask_alien_by_depth(game, draw.scaled, draw.screen_x, distance);
	//ft_draw_image_rgba(game->render, draw.scaled,
	//	draw.screen_x, draw.screen_y);
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
