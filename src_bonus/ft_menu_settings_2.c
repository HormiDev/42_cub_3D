/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_settings_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:17:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:32 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_loading_menu_settings(t_game *game)
{
	ft_bzero(&game->menu_settings, sizeof(t_menu));
	game->menu_settings.current_frame = 0;
	game->menu_settings.render = game->menu.render;
	ft_loading_settings_buttons(game);
}

void	ft_draw_buttons_menu(t_menu *menu)
{
	int	i;

	i = 0;
	while (i < menu->n_buttons)
	{
		if (menu->buttons[i].is_hovered && menu->buttons[i].hover_texture)
		{
			ft_draw_image_rgba(menu->render, menu->buttons[i].hover_texture,
				menu->buttons[i].position.x, menu->buttons[i].position.y);
		}
		else if (menu->buttons[i].texture)
		{
			ft_draw_image_rgba(menu->render, menu->buttons[i].texture,
				menu->buttons[i].position.x, menu->buttons[i].position.y);
		}
		i++;
	}
}
