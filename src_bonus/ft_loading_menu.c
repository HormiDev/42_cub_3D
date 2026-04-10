/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:35:28 by username          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_load_menu_logo(t_game *game)
{
	game->menu.logo = ft_loading_texture(game->mlx, "textures/Alien_logo.xpm");
	if (!game->menu.logo)
		ft_dprintf(2, RED "Error: Failed to load menu logo texture\n" RESET);
}

void	ft_loading_menu_frames(t_game *game)
{
	char		path[256];
	int			i;
	t_texture	*frame;

	i = 0;
	hd_alloc_set_error_func(0);
	while (i < 200)
	{
		ft_snprintf(path, sizeof(path), "menu_frames/frame_%d.xpm", i);
		frame = ft_loading_texture(game->mlx, path);
		if (frame)
			game->menu.frames_textures[i] = frame;
		else
			game->menu.frames_textures[i] = game->null_texture;
		i++;
	}
	hd_alloc_set_error_func(hd_alloc_error_func_d);
	game->menu.total_frames = i;
}

/**
 * ft_button_position_size - Establece la posición y el tamaño de un botón.
 * @button: Puntero al botón a configurar.
 * @x: Coordenada x de la posición del botón.
 * @y: Coordenada y de la posición del botón.
 * @width: Ancho del botón.
 * @height: Alto del botón.
 * especificadas al botón proporcionado.
 */

void	ft_button_position_size(t_button *button, t_vector_int pos,
		t_vector_int size)
{
	button->position = pos;
	button->size = size;
}

void	ft_loading_menu_buttons(t_game *game)
{
	t_vector_int	pos;
	t_vector_int	size;

	game->menu.n_buttons = 3;
	game->menu.buttons = hd_calloc(game->menu.n_buttons, sizeof(t_button));
	size.x = MENU_BUTTON_WIDTH;
	size.y = MENU_BUTTON_HEIGHT;
	pos.x = (MENU_WIDTH / 2) - (MENU_BUTTON_WIDTH / 2);
	pos.y = (MENU_HEIGHT / 2);
	ft_button_position_size(&game->menu.buttons[0], pos, size);
	ft_loading_texture_buttons(game, &game->menu.buttons[0],
		"textures/menu/button_play.xpm", "textures/menu/button_play_hover.xpm");
	game->menu.buttons[0].on_click = ft_start_button;
	pos.y = (MENU_HEIGHT / 2) + MENU_BUTTON_HEIGHT + 20;
	ft_button_position_size(&game->menu.buttons[1], pos, size);
	ft_loading_texture_buttons(game, &game->menu.buttons[1],
		"textures/menu/button_settings.xpm",
		"textures/menu/button_settings_hover.xpm");
	game->menu.buttons[1].on_click = ft_settings_button;
	pos.y = (MENU_HEIGHT / 2) + 2 * (MENU_BUTTON_HEIGHT + 20);
	ft_button_position_size(&game->menu.buttons[2], pos, size);
	ft_loading_texture_buttons(game, &game->menu.buttons[2],
		"textures/menu/button_exit.xpm", "textures/menu/button_exit_hover.xpm");
	game->menu.buttons[2].on_click = ft_exit_button;
}

void	ft_loading_menu(t_game *game)
{
	ft_bzero(&game->menu, sizeof(t_menu));
	game->menu.current_frame = 0;
	game->menu.last_frame_time = game->current_time;
	game->menu.render = ft_new_texture(game->mlx, MENU_WIDTH, MENU_HEIGHT);
	ft_loading_menu_frames(game);
	ft_load_menu_logo(game);
	ft_loading_menu_buttons(game);
}
