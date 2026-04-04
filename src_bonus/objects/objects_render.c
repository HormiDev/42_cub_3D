/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:24:09 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/04 20:53:04 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Configura los parámetros de dibujado del sprite.
 */
static void	ft_setup_sprite_draw(t_game *game, t_objet_draw *draw,
	int screen_col, double base_size)//funcion para borrar
{
	draw->size = ft_compute_sprite_size(game, base_size, draw->distance);
	//draw->scaled = ft_new_texture(game->mlx, draw->size, draw->size);
	draw->screen_x = screen_col - draw->size / 2;

	draw->screen_y = game->config.render_height / 2 - draw->size / 2
		+ draw->size / 8;
}

t_texture	*ft_select_texture(t_prerender_model *model, double angle, int frame, double rotation)
{
	int angle_model;

	angle = ft_normalize_angle(angle - rotation + 180 - (365.0 / model->n_angles / 2));
	angle_model = -(int)(angle * model->n_angles / 360.0) + model->n_angles;
	angle_model = ft_normalize_angle(angle_model);
	//ft_printf("Angle model: %d\n", angle_model * frame - 1);
	return (model->texture[angle_model * frame - 1]);
}

/**
 * @brief Renderiza un sprite (alien o jugador) usando técnica billboard.
 */
void	ft_render_player_sprite(t_game *game, t_player *object)
{
	t_objet_draw	draw;
	int				screen_col;
	t_vector2		diff;
	int frame = 1;

	if (!object->active || !object->model)
		return ;
	draw.distance = ft_vector_distance(game->player->position, object->position);
	if (draw.distance < 0.3 || draw.distance > (MAX_RAY_SIZE))
		return ;
	diff.x = object->position.x - game->player->position.x;
	diff.y = object->position.y - game->player->position.y;
	screen_col = ft_project_sprite_column(game, diff.x, diff.y, &draw);
	if (screen_col == INT_MIN)
		return ;
	draw.scaled = ft_select_texture(object->model, draw.angle, frame, object->rotation.x);
	ft_setup_sprite_draw(game, &draw, screen_col, object->size);
	//ft_draw_image_rgba_scaled(game->render, draw.scaled, draw.screen_x, draw.screen_y, draw.size);
	ft_draw_image_rgba_scaled_plus(game, draw.scaled, draw.screen_x, draw.screen_y, draw.size, draw.distance);
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
