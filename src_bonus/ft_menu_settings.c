/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:17:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:01:21 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_loading_settings_buttons_resolution(t_game *game)
{
	t_vector_int	pos;
	t_vector_int	size;

	pos.x = (MENU_WIDTH / 2) - MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 20;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[1],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[1],
		"textures/menu/button_right.xpm",
		"textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[1].on_click = ft_previous_resolution;
	pos.x = (MENU_WIDTH / 2) + MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 20;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[2],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[2],
		"textures/menu/button_left.xpm", "textures/menu/button_left_hover.xpm");
	game->menu_settings.buttons[2].on_click = ft_next_resolution;
}

void	ft_loading_settings_buttons_players(t_game *game)
{
	t_vector_int	pos;
	t_vector_int	size;

	pos.x = (MENU_WIDTH / 2) - MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 120;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[3],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[3],
		"textures/menu/button_right.xpm",
		"textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[3].on_click = ft_decrease_players;
	pos.x = (MENU_WIDTH / 2) + MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 120;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[4],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[4],
		"textures/menu/button_left.xpm", "textures/menu/button_left_hover.xpm");
	game->menu_settings.buttons[4].on_click = ft_increase_players;
}

void	ft_loading_settings_buttons_charges(t_game *game)
{
	t_vector_int	pos;
	t_vector_int	size;

	pos.x = (MENU_WIDTH / 2) - MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 220;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[5],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[5],
		"textures/menu/button_right.xpm",
		"textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[5].on_click = ft_decrease_charges;
	pos.x = (MENU_WIDTH / 2) + MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 220;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[6],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[6],
		"textures/menu/button_left.xpm", "textures/menu/button_left_hover.xpm");
	game->menu_settings.buttons[6].on_click = ft_increase_charges;
}

void	ft_loading_settings_buttons_timer(t_game *game)
{
	t_vector_int	pos;
	t_vector_int	size;

	pos.x = (MENU_WIDTH / 2) - MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 320;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[7],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[7],
		"textures/menu/button_right.xpm",
		"textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[7].on_click = ft_decrease_timer;
	pos.x = (MENU_WIDTH / 2) + MENU_BUTTON_WIDTH - MENU_BUTTON_HEIGHT / 2;
	pos.y = MENU_BUTTON_HEIGHT + 320;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[8],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[8],
		"textures/menu/button_left.xpm", "textures/menu/button_left_hover.xpm");
	game->menu_settings.buttons[8].on_click = ft_increase_timer;
}

void	ft_loading_settings_buttons(t_game *game)
{
	t_vector_int	pos;
	t_vector_int	size;

	game->menu_settings.n_buttons = 9;
	game->menu_settings.buttons = hd_calloc(game->menu_settings.n_buttons,
			sizeof(t_button));
	pos.x = 20;
	pos.y = 20;
	size.x = MENU_BUTTON_HEIGHT;
	size.y = MENU_BUTTON_HEIGHT;
	ft_button_position_size(&game->menu_settings.buttons[0],
		pos, size);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[0],
		"textures/menu/button_right.xpm",
		"textures/menu/button_right_hover.xpm");
	game->menu_settings.buttons[0].on_click = ft_menu_button;
	ft_loading_settings_buttons_resolution(game);
	ft_loading_settings_buttons_players(game);
	ft_loading_settings_buttons_charges(game);
	ft_loading_settings_buttons_timer(game);
}
