/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/03 20:38:59 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static void	ft_load_menu_logo(t_game *game)
{
	game->menu.logo = ft_loading_texture(game->mlx, "textures/Alien_logo.xpm");
	if (!game->menu.logo)
	{
		ft_dprintf(2, RED "Error: Failed to load menu logo texture\n" RESET);
	}
}

void	ft_draw_buttons_menu(t_game *game)
{
	int i;

	i = 0;
	while (i < game->menu.n_buttons)
	{
		if (game->menu.buttons[i].is_hovered && game->menu.buttons[i].hover_texture)
		{
			ft_draw_transparent_image(game->menu.render,
				game->menu.buttons[i].hover_texture,
				game->menu.buttons[i].position.x,
				game->menu.buttons[i].position.y);
		}
		else if (game->menu.buttons[i].texture)
		{
			ft_draw_transparent_image(game->menu.render,
				game->menu.buttons[i].texture,
				game->menu.buttons[i].position.x,
				game->menu.buttons[i].position.y);
		}
		i++;
	}
}

void	ft_update_menu(t_game *game)
{
	long	current_time;
	long	time_diff;

	audio_play_menu(game, "music&sounds/menu.wav");
	current_time = ft_get_time();
	time_diff = ft_long_diff(game->menu.last_frame_time, current_time);
	if (time_diff > MENU_FRAME_MS)
	{
		game->menu.current_frame++;
		if (game->menu.current_frame >= game->menu.total_frames 
			&& game->menu.total_frames > 0)
			game->menu.current_frame = 0;
		game->menu.last_frame_time = current_time;
	}
	if (game->menu.total_frames > 0)
	{
		ft_scale_t_image(game->menu.frames_textures
			[game->menu.current_frame], game->menu.render);
	}
	if (game->menu.logo)
		ft_draw_transparent_image(game->menu.render, game->menu.logo, MENU_WIDTH / 2 - game->menu.logo->width / 2, MENU_HEIGHT / 6);
	ft_draw_buttons_menu(game);
	ft_scale_t_image(game->menu.render, game->window_img);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0, 0);
}

void	ft_loading_menu_frames(t_game *game)
{
	char		path[256];
	int			i;
	int			j;
	t_texture	*frame;

	i = 0;
	j = 0;
	while (i < 200)
	{
		ft_snprintf(path, sizeof(path), "menu_frames/frame_%d.xpm", i);
		frame = ft_loading_texture(game->mlx, path);
		if (frame)
		{
			game->menu.frames_textures[j] = frame;
			j++;
		}
		i++;
	}
	game->menu.total_frames = j;
}

void	ft_start_button(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (!game)
		return ;
	audio_stop_menu(game);
	game->show_menu = 0;
}

void	ft_loading_menu_buttons(t_game *game)
{
	t_texture	*button_texture;

	game->menu.n_buttons = 3; // Actualizar si se añaden más botones
	game->menu.buttons = ft_alloc_lst(sizeof(t_button) * game->menu.n_buttons, 4);
	// Start Button
	button_texture = ft_loading_texture(game->mlx, "textures/menu/Play_Button.xpm");
	game->menu.buttons[0].texture = ft_new_texture(game->mlx, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_scale_t_image(button_texture, game->menu.buttons[0].texture);
	button_texture = ft_loading_texture(game->mlx, "textures/menu/Play_Button_red.xpm");
	game->menu.buttons[0].hover_texture = ft_new_texture(game->mlx, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_scale_t_image(button_texture, game->menu.buttons[0].hover_texture);
	game->menu.buttons[0].position.x = (MENU_WIDTH / 2) - (MENU_BUTTON_WIDTH / 2);
	game->menu.buttons[0].position.y = (MENU_HEIGHT / 2);
	game->menu.buttons[0].size.x = MENU_BUTTON_WIDTH;
	game->menu.buttons[0].size.y = MENU_BUTTON_HEIGHT;
	game->menu.buttons[0].on_click = ft_start_button;
	// Options Button
	button_texture = ft_loading_texture(game->mlx, "textures/menu/Settings_Button.xpm");
	game->menu.buttons[1].texture = ft_new_texture(game->mlx, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_scale_t_image(button_texture, game->menu.buttons[1].texture);
	button_texture = ft_loading_texture(game->mlx, "textures/menu/Settings_Button_red.xpm");
	game->menu.buttons[1].hover_texture = ft_new_texture(game->mlx, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_scale_t_image(button_texture, game->menu.buttons[1].hover_texture);
	game->menu.buttons[1].position.x = (MENU_WIDTH / 2) - (MENU_BUTTON_WIDTH / 2);
	game->menu.buttons[1].position.y = (MENU_HEIGHT / 2) + MENU_BUTTON_HEIGHT + 20;
	game->menu.buttons[1].size.x = MENU_BUTTON_WIDTH;
	game->menu.buttons[1].size.y = MENU_BUTTON_HEIGHT;
	game->menu.buttons[1].on_click = NULL; // Implementar función de opciones
	// Exit Button
	button_texture = ft_loading_texture(game->mlx, "textures/menu/Exit_Button.xpm");
	game->menu.buttons[2].texture = ft_new_texture(game->mlx, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_scale_t_image(button_texture, game->menu.buttons[2].texture);
	button_texture = ft_loading_texture(game->mlx, "textures/menu/Exit_Button_red.xpm");
	game->menu.buttons[2].hover_texture = ft_new_texture(game->mlx, MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_scale_t_image(button_texture, game->menu.buttons[2].hover_texture);
	game->menu.buttons[2].position.x = (MENU_WIDTH / 2) - (MENU_BUTTON_WIDTH / 2);
	game->menu.buttons[2].position.y = (MENU_HEIGHT / 2) + 2 * (MENU_BUTTON_HEIGHT + 20);
	game->menu.buttons[2].size.x = MENU_BUTTON_WIDTH;
	game->menu.buttons[2].size.y = MENU_BUTTON_HEIGHT;
	game->menu.buttons[2].on_click = NULL;
}

void	ft_loading_menu(t_game *game)
{
	ft_bzero(&game->menu, sizeof(t_menu));
	game->menu.current_frame = 0;
	game->menu.last_frame_time = ft_get_time();
	game->menu.render = ft_new_texture(game->mlx, MENU_WIDTH, MENU_HEIGHT);
	ft_loading_menu_frames(game);
	ft_load_menu_logo(game);
	ft_loading_menu_buttons(game);
}
