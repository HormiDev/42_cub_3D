/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/10/27 13:56:03 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static int	ft_menu_key_press(int keycode, t_menu *menu)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == SPACE || keycode == 65293)
	{
		menu->start_game = 1;
		mlx_loop_end(menu->mlx);
	}
	return (0);
}

static int	ft_menu_close(t_menu *menu)
{
	(void)menu;
	exit(0);
	return (0);
}

static void	ft_draw_menu_text(t_menu *menu)
{
	int	x;
	int	y;

	x = 220;
	y = 80;
	mlx_string_put(menu->mlx, menu->window, x, y, C_ALIEN_GREEN,
		"    _    _     ___ _____ _   _ ");
	mlx_string_put(menu->mlx, menu->window, x, y + 20, C_ALIEN_GREEN,
		"   / \\  | |   |_ _| ____| \\ | |");
	mlx_string_put(menu->mlx, menu->window, x, y + 40, C_ALIEN_GREEN,
		"  / _ \\ | |    | ||  _| |  \\| |");
	mlx_string_put(menu->mlx, menu->window, x, y + 60, C_ALIEN_GREEN,
		" / ___ \\| |___ | || |___| |\\  |");
	mlx_string_put(menu->mlx, menu->window, x, y + 80, C_ALIEN_GREEN,
		"/_/   \\_\\_____|___|_____|_| \\_|");
	mlx_string_put(menu->mlx, menu->window, 280, 400, C_ALIEN_GRID,
		"Press SPACE to start");
	mlx_string_put(menu->mlx, menu->window, 300, 440, C_ALIEN_GRID,
		"Press ESC to exit");
	mlx_string_put(menu->mlx, menu->window, 300, 580, C_ALIEN_GRID,
		"Ismaelucky && HormiDev");
	mlx_string_put(menu->mlx, menu->window, 10, 580, 0x808080,
		"Cub3D - 42 Madrid");
}

static int	ft_menu_update(t_menu *menu)
{
	long	current_time;
	long	time_diff;

	current_time = ft_get_time();
	time_diff = ft_long_diff(menu->last_frame_time, current_time);
	if (time_diff > MENU_FRAME_MS)
	{
		menu->current_frame++;
		if (menu->current_frame >= menu->total_frames && menu->total_frames > 0)
			menu->current_frame = 0;
		menu->last_frame_time = current_time;
	}
	mlx_clear_window(menu->mlx, menu->window);
	if (menu->total_frames > 0 && menu->frames[menu->current_frame])
		mlx_put_image_to_window(menu->mlx, menu->window,
			menu->frames[menu->current_frame], 0, 0);
	ft_draw_menu_text(menu);
	return (0);
}

static void	ft_load_menu_frames(t_menu *menu)
{
	char	*path;
	char	*num_str;
	int		i;
	int		width;
	int		height;

	i = 0;
	while (i < 200)
	{
		num_str = ft_itoa(i);
		path = ft_strjoin_ae("menu_frames/frame_", num_str);
		path = ft_strjoin_ae(path, ".xpm");
		menu->frames[i] = mlx_xpm_file_to_image(menu->mlx, path,
				&width, &height);
		if (menu->frames[i])
			menu->total_frames++;
		else
			break ;
		i++;
	}
	if (menu->total_frames == 0)
		menu->frames[0] = NULL;
}

int	ft_show_menu(void *mlx)
{
	t_menu	menu;
	int		i;

	ft_bzero(&menu, sizeof(t_menu));
	menu.mlx = mlx;
	menu.window = mlx_new_window(mlx, 800, 600, "Cub3D - Menu");
	menu.start_game = 0;
	menu.current_frame = 0;
	menu.total_frames = 0;
	menu.last_frame_time = ft_get_time();
	ft_load_menu_frames(&menu);
	mlx_hook(menu.window, 17, 0, ft_menu_close, &menu);
	mlx_hook(menu.window, 2, 1L << 0, ft_menu_key_press, &menu);
	mlx_loop_hook(menu.mlx, ft_menu_update, &menu);
	mlx_loop(menu.mlx);
	i = 0;
	while (i < menu.total_frames)
	{
		if (menu.frames[i])
			mlx_destroy_image(menu.mlx, menu.frames[i]);
		i++;
	}
	mlx_destroy_window(menu.mlx, menu.window);
	return (menu.start_game);
}
