/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_draw_menu_background(t_game *game)
{
	long	time_diff;

	time_diff = ft_long_diff(game->menu.last_frame_time, game->current_time);
	if (time_diff > MENU_FRAME_MS)
	{
		game->menu.current_frame++;
		if (game->menu.current_frame >= game->menu.total_frames
			&& game->menu.total_frames > 0)
			game->menu.current_frame = 0;
		game->menu.last_frame_time = game->current_time;
	}
	if (game->menu.total_frames > 0)
	{
		ft_scale_t_image(game->menu.frames_textures[game->menu.current_frame],
			game->menu.render);
	}
}

static void	ft_draw_main_menu(t_game *game)
{
	if (game->menu.logo)
		ft_draw_image_rgba(game->menu.render, game->menu.logo,
			MENU_WIDTH / 2 - game->menu.logo->width / 2,
			MENU_HEIGHT / 6);
	ft_draw_buttons_menu(&game->menu);
}

static void	ft_draw_settings_texts(t_game *game, char *str, int y)
{
	t_string_ctx	ctx;

	ctx.dst = game->menu_settings.render;
	ctx.font = game->font;
	ctx.scale = 6;
	ctx.pos = (t_vector_int){MENU_WIDTH / 2 - (6 * 6 * ft_strlen(str) / 2), y};
	ft_draw_string_hud(ctx.dst, ctx.font, str, &ctx);
}

static void	ft_draw_settings_menu(t_game *game)
{
	char			str[20];
	t_string_ctx	ctx;

	ft_draw_buttons_menu(&game->menu_settings);
	ctx.dst = game->menu_settings.render;
	ctx.font = game->font;
	ctx.scale = 6;
	ctx.pos = (t_vector_int){MENU_WIDTH / 2 - (6 * 6 * 10 / 2), 30};
	ft_draw_string_hud(ctx.dst, ctx.font, "Resolution", &ctx);
	ft_snprintf(str, sizeof(str), "%d x %d",
		game->resolutions[game->config.resolution_index].width,
		game->resolutions[game->config.resolution_index].height);
	ft_draw_settings_texts(game, str, 110);
	ft_snprintf(str, sizeof(str), "players %d", game->config.n_players);
	ft_draw_settings_texts(game, str, 210);
	ft_snprintf(str, sizeof(str), "charges %d", game->config.charges);
	ft_draw_settings_texts(game, str, 310);
	ft_snprintf(str, sizeof(str), "timer %d",
		game->durations[game->config.duration_index]);
	ft_draw_settings_texts(game, str, 410);
}

void	ft_update_menu(t_game *game)
{
	t_string_ctx	ctx;

	ft_draw_menu_background(game);
	if (game->show_menu == 1)
		ft_draw_main_menu(game);
	else if (game->show_menu == 2)
		ft_draw_settings_menu(game);
	ctx.dst = game->menu.render;
	ctx.font = game->font;
	ctx.scale = 2;
	ctx.pos = (t_vector_int){10, MENU_HEIGHT - 30};
	ft_draw_string_hud(ctx.dst, ctx.font,
		"42 cub3d by hormidev and ismaelucky342", &ctx);
	ft_scale_t_image(game->menu.render, game->window_img);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window,
		game->window_img->img, 0, 0);
}
