/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_one_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:43:53 by username          #+#    #+#             */
/*   Updated: 2026/04/10 03:54:36 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_one_player_aux(t_game *game)
{
	if (game->config.render_height != WINDOW_HEIGHT
		|| game->config.render_width != WINDOW_WIDTH)
	{
		ft_scale_t_image_precalc(game->render, game->window_img, game);
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100,
			WINDOW_HEIGHT / 100);
		ft_render_timer_hud(game);
		ft_render_flamethrower_hud(game, 0);
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window, game->window_img->img,
			0, 0);
	}
	else
	{
		ft_draw_image_rgba(game->render, game->minimap, WINDOW_WIDTH / 100,
			WINDOW_HEIGHT / 100);
		ft_render_timer_hud(game);
		ft_render_flamethrower_hud(game, 0);
		mlx_clear_window(game->mlx, game->window);
		mlx_put_image_to_window(game->mlx, game->window, game->render->img, 0,
			0);
	}
}

void	ft_one_player(t_game *game)
{
	ft_controls(game, 0);
	ft_update_flamethrower_cooldown(&game->actions[0], game->delta_time);
	ft_update_heatmap(game);
	ft_update_aliens(game);
	ft_update_doors(game);
	ft_calculate_raycasts(game);
	ft_render_3d(game);
	ft_render_all_sprites(game);
	ft_map2d(game);
	ft_render_flamethrower(game, 0);
	ft_one_player_aux(game);
}
