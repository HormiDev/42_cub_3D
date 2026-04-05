/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:17:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/05 23:25:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void ft_menu_button(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (!game)
		return ;
	if (game->config.resolution_index != game->tmp_config.resolution_index)
		ft_loading_render(game, game->resolutions[game->config.resolution_index].height,
			game->resolutions[game->config.resolution_index].width);
	if (game->config.n_players != game->tmp_config.n_players)
	{
		ft_loading_render(game, game->resolutions[game->config.resolution_index].height,
			game->resolutions[game->config.resolution_index].width);
		ft_config_player(game);
		ft_config_alien(game);
	}
	game->show_menu = 1;
}

void	ft_loading_settings_buttons(t_game *game)
{
	game->menu_settings.n_buttons = 5; // Actualizar si se añaden más botones
	game->menu_settings.buttons = hd_calloc(game->menu_settings.n_buttons,
			sizeof(t_button));
	// Back Button
	ft_button_position_size(&game->menu_settings.buttons[0],
		20, 20, MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[0],
		"textures/menu/button_right.xpm", "textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[0].on_click = ft_menu_button;
	// Dummy Button

	//botones de resolución
	ft_button_position_size(&game->menu_settings.buttons[1],
		(MENU_WIDTH / 2) - MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 20,
		MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[1],
		"textures/menu/button_right.xpm", "textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[1].on_click = ft_previous_resolution;
	// Dummy Button
	ft_button_position_size(&game->menu_settings.buttons[2],
		(MENU_WIDTH / 2) + MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 20,
		MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[2],
		"textures/menu/button_left.xpm", "textures/menu/button_left_hover.xpm");
	game->menu_settings.buttons[2].on_click = ft_next_resolution;

	//botones de numero de Players
	ft_button_position_size(&game->menu_settings.buttons[3],
		(MENU_WIDTH / 2) - MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 120,
		MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[3],
		"textures/menu/button_right.xpm", "textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[3].on_click = ft_decrease_players;
	// Dummy Button
	ft_button_position_size(&game->menu_settings.buttons[4],
		(MENU_WIDTH / 2) + MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 120,
		MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[4],
		"textures/menu/button_left.xpm", "textures/menu/button_left_hover.xpm");
	game->menu_settings.buttons[4].on_click = ft_increase_players;
}

void	ft_loading_menu_settings(t_game *game)
{
	ft_bzero(&game->menu_settings, sizeof(t_menu));
	game->menu_settings.current_frame = 0;
	game->menu_settings.render = game->menu.render;
	ft_loading_settings_buttons(game);
}