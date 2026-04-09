/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_three_players.c                                :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/09 13:43:53 by username         #+#    #+#              */
/*   Updated: 2026/04/09 19:13:57 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static void	ft_draw_minimap_viewport(t_game *game, int player_index)
{
	if (player_index == 0)
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100,
		WINDOW_HEIGHT / 100);
	else if (player_index == 1)
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100,
		WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2));
	else if (player_index == 2)
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100
		+(WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100);
	else
		ft_draw_image_rgba(game->window_img, game->minimap, WINDOW_WIDTH / 100
		+(WINDOW_WIDTH / 2), WINDOW_HEIGHT / 100 + (WINDOW_HEIGHT / 2));
}

static void	ft_render_player_scene(t_game *game, int player_index)
{
	ft_calculate_raycasts(game);
	ft_render_3d(game);
	ft_render_all_sprites(game);
	ft_map2d(game);
	ft_render_flamethrower(game, player_index);
	ft_scale_t_image_precalc_three(game->render, game->window_img, game,
		player_index);
}

static t_vector_int ft_get_player_viewport_offset(int player_index,
	t_vector_int	viewport)
{
	t_vector_int	offset;

	offset.x = 0;
	offset.y = 0;
	if (player_index == 1)
		offset.y = viewport.y;
	else if (player_index == 2)
		offset.x = viewport.x;
	else if (player_index == 3)
	{
		offset.x = viewport.x;
		offset.y = viewport.y;
	}
	return (offset);
}

static void ft_render_player_view(t_game * game, int player_index,
	t_vector_int	viewport)
{
	t_vector_int	offset;

	game->player = &game->players[player_index];
	ft_controls(game, player_index);
	ft_update_flamethrower_cooldown(&game->actions[player_index],
		game->delta_time);
	ft_update_doors(game);
	ft_render_player_scene(game, player_index);
	ft_draw_minimap_viewport(game, player_index);
	offset = ft_get_player_viewport_offset(player_index, viewport);
	ft_render_timer_hud_viewport(game, game->window_img,
		offset.x, offset.y, viewport);
	ft_render_flamethrower(game, player_index);
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
		ft_render_player_view(game, player_index, viewport);
		player_index++;
	}
	game->player = &game->players[0];
	ft_update_heatmap(game);
	ft_update_aliens(game);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0,
		0);
}
