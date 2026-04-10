/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_settings_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:17:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 02:43:32 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"


void	ft_setup_settings_button(t_game *game, int idx,
		t_vector_int pos, const char *base_hover[2], void (*on_click)(void *))
{
	ft_button_position_size(&game->menu_settings.buttons[idx], pos.x, pos.y,
		MENU_BUTTON_HEIGHT, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu_settings.buttons[idx],
		(char *)base_hover[0], (char *)base_hover[1]);
	game->menu_settings.buttons[idx].on_click = on_click;
}

void	ft_fill_settings_callbacks(void (*callbacks[9])(void *))
{
	callbacks[0] = ft_menu_button;
	callbacks[1] = ft_previous_resolution;
	callbacks[2] = ft_next_resolution;
	callbacks[3] = ft_decrease_players;
	callbacks[4] = ft_increase_players;
	callbacks[5] = ft_decrease_charges;
	callbacks[6] = ft_increase_charges;
	callbacks[7] = ft_decrease_timer;
	callbacks[8] = ft_increase_timer;
}

void	ft_fill_settings_positions(t_vector_int positions[9])
{
	positions[0] = (t_vector_int){20, 20};
	positions[1] = (t_vector_int){(MENU_WIDTH / 2) - MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 20};
	positions[2] = (t_vector_int){(MENU_WIDTH / 2) + MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 20};
	positions[3] = (t_vector_int){(MENU_WIDTH / 2) - MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 120};
	positions[4] = (t_vector_int){(MENU_WIDTH / 2) + MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 120};
	positions[5] = (t_vector_int){(MENU_WIDTH / 2) - MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 220};
	positions[6] = (t_vector_int){(MENU_WIDTH / 2) + MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 220};
	positions[7] = (t_vector_int){(MENU_WIDTH / 2) - MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 320};
	positions[8] = (t_vector_int){(MENU_WIDTH / 2) + MENU_BUTTON_WIDTH
		- MENU_BUTTON_HEIGHT / 2, MENU_BUTTON_HEIGHT + 320};
}
