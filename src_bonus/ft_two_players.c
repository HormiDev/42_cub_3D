/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_two_players.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:43:53 by username          #+#    #+#             */
/*   Updated: 2026/04/09 18:39:45 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_two_players(t_game *game)
{
	int				player_index;
	int				offset_x;
	int				offset_y;
	t_vector_int	viewport;

	player_index = 0;
	viewport.x = game->window_img->width;
	viewport.y = game->window_img->height / 2;
	while (player_index < 2)
	{
		game->player = &game->players[player_index];
		ft_controls(game, player_index);
		ft_update_flamethrower_cooldown(&game->actions[player_index],
			game->delta_time);
		ft_update_doors(game);
		ft_calculate_raycasts(game);
		ft_render_3d(game);
		ft_render_all_sprites(game);
		ft_map2d(game);
		ft_render_flamethrower(game, player_index);
		ft_scale_t_image_precalc_two(game->render, game->window_img, game,
			player_index);
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100,
			WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2 * (player_index)));
		offset_x = 0;
		offset_y = viewport.y * player_index;
		ft_render_timer_hud_viewport(game, game->window_img,
			offset_x, offset_y, viewport);
		ft_flamethrower_hud(game, player_index,
			game->window_img, offset_x, offset_y, viewport);
		player_index++;
	}
	game->player = &game->players[0];
	ft_update_heatmap(game);
	ft_update_aliens(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0,
		0);
}
