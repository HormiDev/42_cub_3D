#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Configura los parámetros de dibujado del sprite.
 */
static void	ft_setup_sprite_draw(t_game *game, t_alien_draw *draw,
	int screen_col, double base_size, double distance)
{
	draw->size = ft_compute_sprite_size(game, base_size, distance);
	draw->scaled = ft_new_texture(game->mlx, draw->size, draw->size);
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
void	ft_render_player_sprite(t_game *game, t_player *player)
{
	t_alien_draw	draw;
	t_vector2		pos;
	t_texture		*tex;
	double			distance;
	int				screen_col;
	t_vector2		diff;
	double			base_size;

	if (!ft_get_player_data(player, &pos, &base_size, &tex))
		return ;
	distance = ft_vector_distance(game->player->position, pos);
	if (distance < 0.3 || distance > (MAX_RAY_SIZE - 0.5))
		return ;
	diff.x = pos.x - game->player->position.x;
	diff.y = pos.y - game->player->position.y;
	screen_col = ft_project_sprite_column(game, diff.x, diff.y);
	if (screen_col < 0)
		return ;
	ft_setup_sprite_draw(game, &draw, screen_col, base_size, distance);
	if (!draw.scaled)
		return ;
	ft_scale_t_image(tex, draw.scaled);
	ft_mask_alien_by_depth(game, draw.scaled, draw.screen_x, distance);
	ft_draw_image_rgba(game->render, draw.scaled,
		draw.screen_x, draw.screen_y);
}

/**
 * @brief Renderiza todos los sprites visibles en la escena.
 */
void	ft_render_all_sprites(t_game *game)
{
	t_player	sorted[MAX_PLAYERS];
	int			idx;
	int			current_idx;
	int			orig_idx;

	ft_update_render_distances(game);
	ft_get_sorted_players(game, sorted);
	current_idx = game->player - game->players;
	idx = 0;
	while (idx < MAX_PLAYERS)
	{
		if (sorted[idx].active)
		{
			orig_idx = ft_get_original_index(game, &sorted[idx]);
			if (orig_idx >= 0 && orig_idx != current_idx)
				ft_render_player_sprite(game, &sorted[idx]);
		}
		idx++;
	}
}
