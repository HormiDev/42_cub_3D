/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:17:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/20 01:06:40 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void ft_menu_button(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	game->show_menu = 1;
}

void	ft_loading_settings_buttons(t_game *game)
{
	game->menu_settings.n_buttons = 3; // Actualizar si se añaden más botones
	game->menu_settings.buttons = ft_alloc_lst(sizeof(t_button) * game->menu_settings.n_buttons, 4);
	// Back Button
	ft_button_position_size(&game->menu_settings.buttons[0],
		(MENU_WIDTH / 2) - (MENU_BUTTON_WIDTH / 2), MENU_BUTTON_HEIGHT + 20,
		MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[0],
		"textures/menu/button_settings.xpm", "textures/menu/button_settings_hover.xpm");
	game->menu_settings.buttons[0].on_click = ft_menu_button;
	// Dummy Button
	ft_button_position_size(&game->menu_settings.buttons[1],
		(MENU_WIDTH / 2) - MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT + 20,
		MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[1],
		"textures/menu/button_right.xpm", "textures/menu/button_right.xpm");
	game->menu_settings.buttons[1].on_click = ft_previous_resolution;
	// Dummy Button
	ft_button_position_size(&game->menu_settings.buttons[2],
		(MENU_WIDTH / 2) + MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT + 20,
		MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[2],
		"textures/menu/button_right.xpm", "textures/menu/button_right.xpm");
	game->menu_settings.buttons[2].on_click = ft_next_resolution;
}

void	ft_loading_menu_settings(t_game *game)
{
	ft_bzero(&game->menu_settings, sizeof(t_menu));
	game->menu_settings.current_frame = 0;
	game->menu_settings.render = game->menu.render;
	ft_loading_settings_buttons(game);
}