/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:56:43 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 02:24:00 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_calculate_mouse_position_menu(t_game *game, t_menu *menu)
{
	menu->mouse_position.x = game->mouse_xy[0] * MENU_WIDTH / WINDOW_WIDTH;
	menu->mouse_position.y = game->mouse_xy[1] * MENU_HEIGHT / WINDOW_HEIGHT;
}

void	ft_hober_buttons(t_game *game, t_menu *menu)
{
	int	i;

	ft_calculate_mouse_position_menu(game, menu);
	i = 0;
	while (i < menu->n_buttons)
	{
		if (menu->buttons[i].texture)
		{
			if (menu->mouse_position.x >= menu->buttons[i].position.x
				&& menu->mouse_position.x <= menu->buttons[i].position.x
				+ menu->buttons[i].size.x
				&& menu->mouse_position.y >= menu->buttons[i].position.y
				&& menu->mouse_position.y <= menu->buttons[i].position.y
				+ menu->buttons[i].size.y)
				menu->buttons[i].is_hovered = 1;
			else
				menu->buttons[i].is_hovered = 0;
		}
		i++;
	}
}

void	ft_click_button(t_game *game, t_menu *menu)
{
	int	i;

	i = 0;
	while (i < menu->n_buttons)
	{
		if (menu->buttons[i].is_hovered)
		{
			if (menu->buttons[i].on_click)
				menu->buttons[i].on_click(game);
			break ;
		}
		i++;
	}
}

void	ft_mouse_capture(t_game *game)
{
	game->mouse_captured = 1;
	mlx_mouse_move(game->mlx, game->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT
		/ 2);
	mlx_mouse_hide(game->mlx, game->window);
}

int	ft_mouse_click(int button, int x, int y, t_game *game)
{
	if (button == 1)
	{
		if (!game->mouse_captured)
		{
			game->mouse_xy[0] = x;
			game->mouse_xy[1] = y;
			if (game->show_menu == 1)
			{
				ft_hober_buttons(game, &game->menu);
				ft_click_button(game, &game->menu);
			}
			else if (game->show_menu == 2)
			{
				ft_hober_buttons(game, &game->menu_settings);
				ft_click_button(game, &game->menu_settings);
			}
		}
		else
			flamethrower(game, game->kb_player);
	}
	return (0);
}
