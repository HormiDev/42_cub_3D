/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:56:43 by ismherna          #+#    #+#             */
/*   Updated: 2026/01/03 20:06:19 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_calculate_mouse_position_menu(t_game *game, t_menu *menu)
{
	menu->mouse_position.x = game->input.raw.mouse.mouse_x * MENU_WIDTH / WINDOW_WIDTH;
	menu->mouse_position.y = game->input.raw.mouse.mouse_y * MENU_HEIGHT / WINDOW_HEIGHT;
}

void	ft_hober_buttons(t_game *game, t_menu *menu)
{
	int i;

	ft_calculate_mouse_position_menu(game, menu);
	i = 0;
	while (i < menu->n_buttons)
	{
		if (menu->buttons[i].texture)
		{
			if (menu->mouse_position.x >= menu->buttons[i].position.x
				&& menu->mouse_position.x <= menu->buttons[i].position.x + menu->buttons[i].size.x
				&& menu->mouse_position.y >= menu->buttons[i].position.y
				&& menu->mouse_position.y <= menu->buttons[i].position.y + menu->buttons[i].size.y)
				menu->buttons[i].is_hovered = 1;
			else
				menu->buttons[i].is_hovered = 0;
		}
		i++;
	}
}

void ft_click_button(t_game *game, t_menu *menu)
{
	int i;

	i = 0;
	while (i < menu->n_buttons)
	{
		if (menu->buttons[i].is_hovered)
		{
			if (menu->buttons[i].on_click)
				menu->buttons[i].on_click(game);
			break;
		}
		i++;
	}
}

/**
 * @brief Maneja el movimiento del ratón y actualiza la rotación del jugador.
 *
 * Esta función es llamada cuando el ratón se mueve. Calcula la diferencia en la posición
 * horizontal del ratón respecto al centro de la ventana y actualiza la rotación del jugador.
 * Debido a que el sistema de coordenadas del mundo tiene el eje Y invertido en comparación
 * con las coordenadas de la ventana, invertimos la dirección del movimiento para una 
 * experiencia de control más intuitiva.
 *
 * @param x Posición horizontal del ratón en la ventana.
 * @param y Posición vertical del ratón en la ventana (no se utiliza).
 * @param game Puntero a la estructura del juego.
 * @return Siempre devuelve 0 (requerido por la API de minilibx).
 */
int ft_mouse_move(int x, int y, t_game *game)
{
    int center_x;
    int center_y; 
    int patata_x;
	
    if (!game->mouse_captured)
    {
		game->input.raw.mouse.mouse_x = x;
		game->input.raw.mouse.mouse_y = y;
		if (game->show_menu)
			ft_hober_buttons(game, &game->menu);
		return (0);
	}
	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
    patata_x = x - center_x;
    game->player->rotation.x -= patata_x * MOUSE_SENSITIVITY * game->delta_time;
    game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
    mlx_mouse_move(game->mlx, game->window, center_x, center_y);
    return (0);
}

void ft_mouse_capture(t_game *game)
{
	game->mouse_captured = 1;
    mlx_mouse_move(game->mlx, game->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    mlx_mouse_hide(game->mlx, game->window);
}

void ft_mouse_free(t_game *game)
{
	game->mouse_captured = 0;
	mlx_mouse_move(game->mlx, game->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_mouse_show(game->mlx, game->window);
}

int ft_mouse_click(int button, int x, int y, t_game *game)
{
	if (button == 1)
	{
		if (!game->mouse_captured)
		{
			game->input.raw.mouse.mouse_x = x;
			game->input.raw.mouse.mouse_y = y;
			if (game->show_menu)
			{
				ft_hober_buttons(game, &game->menu);
				ft_click_button(game, &game->menu);
			}
		}
	}
	return (0);
}
