/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_three_players.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:43:53 by username          #+#    #+#             */
/*   Updated: 2026/04/10 00:39:10 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static void	ft_render_three_player_scene(t_game *game, int player_index)
{
	game->player = &game->players[player_index];
	ft_controls(game, player_index);
	if (game->player->alive)
	{
		ft_update_flamethrower_cooldown(&game->actions[player_index],
			game->delta_time);
		ft_update_doors(game);
		ft_calculate_raycasts(game);
		ft_render_3d(game);
		ft_render_all_sprites(game);
		ft_map2d(game);
		ft_render_flamethrower(game, player_index);
	}
	else
		ft_scale_t_image(game->dead_image, game->render);
	ft_scale_t_image_precalc_three(game->render, game->window_img, game,
		player_index);
}

static void	ft_get_three_offsets(int player_index, t_vector_int viewport,
	int *offset_x, int *offset_y)
{
	*offset_x = 0;
	*offset_y = 0;
	if (player_index == 1)
		*offset_y = viewport.y;
	else if (player_index == 2)
		*offset_x = viewport.x;
	else if (player_index == 3)
	{
		*offset_x = viewport.x;
		*offset_y = viewport.y;
	}
}

static void	ft_render_three_player_hud(t_game *game, int player_index,
	t_vector_int viewport)
{
	int	minimap_x;
	int	minimap_y;
	int	offset_x;
	int	offset_y;

	if (!game->player->alive)
		return ;
	minimap_x = WINDOW_WIDTH / 100;
	minimap_y = WINDOW_HEIGHT / 100;
	if (player_index == 1)
		minimap_y += WINDOW_HEIGHT / 2;
	else if (player_index == 2)
		minimap_x += WINDOW_WIDTH / 2;
	else if (player_index > 2)
	{
		minimap_x += WINDOW_WIDTH / 2;
		minimap_y += WINDOW_HEIGHT / 2;
	}
	ft_draw_image_rgba(game->window_img, game->minimap, minimap_x, minimap_y);
	ft_get_three_offsets(player_index, viewport, &offset_x, &offset_y);
	ft_render_timer_hud_viewport(game, game->window_img,
		offset_x, offset_y, viewport);
	{
		t_vector_int	pos_offset;
		pos_offset.x = offset_x;
		pos_offset.y = offset_y;
		ft_flamethrower_hud(game, player_index,
			game->window_img, pos_offset);
	}
}

static void	ft_finish_three_players_frame(t_game *game)
{
	game->player = &game->players[0];
	ft_update_heatmap(game);
	ft_update_aliens(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0,
		0);
}

void	ft_three_players(t_game *game)
{
	int				player_index;
	t_vector_int	viewport;

	player_index = 0;
	viewport.x = game->window_img->width / 2;
	viewport.y = game->window_img->height / 2;
	while (player_index < game->config.n_players)
	{
		ft_render_three_player_scene(game, player_index);
		ft_render_three_player_hud(game, player_index, viewport);
		player_index++;
	}
	ft_finish_three_players_frame(game);
}
