/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/10 00:42:20 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_draw_menu_text(t_game *game)
{
	int	x;
	int	y;
	int scale_x;
	int scale_y;

	scale_x = WINDOW_WIDTH / 4;
	scale_y = WINDOW_HEIGHT / 8;
	x = scale_x;
	y = scale_y;
	mlx_string_put(game->mlx, game->window, x, y, C_ALIEN_GREEN,
		"    _    _     ___ _____ _   _ ");
	mlx_string_put(game->mlx, game->window, x, y + 20, C_ALIEN_GREEN,
		"   / \\  | |   |_ _| ____| \\ | |");
	mlx_string_put(game->mlx, game->window, x, y + 40, C_ALIEN_GREEN,
		"  / _ \\ | |    | ||  _| |  \\| |");
	mlx_string_put(game->mlx, game->window, x, y + 60, C_ALIEN_GREEN,
		" / ___ \\| |___ | || |___| |\\  |");
	mlx_string_put(game->mlx, game->window, x, y + 80, C_ALIEN_GREEN,
		"/_/   \\_\\_____|___|_____|_| \\_|");
	mlx_string_put(game->mlx, game->window, WINDOW_WIDTH / 3, 
		WINDOW_HEIGHT / 2, C_ALIEN_GRID, "Press SPACE to start");
	mlx_string_put(game->mlx, game->window, WINDOW_WIDTH / 3 + 20, 
		WINDOW_HEIGHT / 2 + 40, C_ALIEN_GRID, "Press ESC to exit");
	mlx_string_put(game->mlx, game->window, WINDOW_WIDTH / 3 + 20, 
		WINDOW_HEIGHT / 2 + 80, C_ALIEN_GRID, "Press P to pause");
	mlx_string_put(game->mlx, game->window, WINDOW_WIDTH / 3 + 20, 
		WINDOW_HEIGHT - 100, C_ALIEN_GRID, "Ismaelucky && HormiDev");
	mlx_string_put(game->mlx, game->window, 10, WINDOW_HEIGHT - 20, 0x808080,
		"Cub3D - 42 Madrid");
}

void	ft_update_menu(t_game *game)
{
	long	current_time;
	long	time_diff;
	int		status;

	if (game->menu.menu_music_pid > 0)
	{
		if (waitpid(game->menu.menu_music_pid, &status, WNOHANG) != 0)
			game->menu.menu_music_pid = ft_play_audio("music&sounds/menu.wav", game->env);
	}
	else
		game->menu.menu_music_pid = ft_play_audio("music&sounds/menu.wav", game->env);
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
	mlx_clear_window(game->mlx, game->window);
	if (game->menu.total_frames > 0 && game->menu.frames_textures[game->menu.current_frame])
	{
		ft_scale_t_image(game->menu.frames_textures[game->menu.current_frame], 
			game->menu.scaled_frame);
		mlx_put_image_to_window(game->mlx, game->window,
			game->menu.scaled_frame->img, 0, 0);
	}
	ft_draw_menu_text(game);
}

static void	ft_load_menu_frames(t_game *game)
{
	char	*path;
	char	*num_str;
	int		i;
	int		width;
	int		height;
	int		j;

	i = 0;
	while (i < 200)
	{
		num_str = ft_itoa(i);
		path = ft_strjoin_ae("menu_frames/frame_", num_str);
		path = ft_strjoin_ae(path, ".xpm");
		game->menu.frames[i] = mlx_xpm_file_to_image(game->mlx, path,
				&width, &height);
		if (game->menu.frames[i])
		{
			game->menu.frames_textures[i] = ft_alloc_lst(sizeof(t_texture), 4);
			game->menu.frames_textures[i]->img = (t_img *)game->menu.frames[i];
			game->menu.frames_textures[i]->width = width;
			game->menu.frames_textures[i]->height = height;
			game->menu.frames_textures[i]->colors_matrix = ft_alloc_lst(
				sizeof(unsigned int *) * height, 4);
			j = 0;
			while (j < height)
			{
				game->menu.frames_textures[i]->colors_matrix[j] = (unsigned int *)
					(game->menu.frames_textures[i]->img->data + (j * sizeof(char) * 4 * width));
				j++;
			}
			game->menu.total_frames++;
		}
		else
			break ;
		i++;
	}
	if (game->menu.total_frames == 0)
		game->menu.frames[0] = NULL;
}

void	ft_init_menu(t_game *game)
{
	int i;

	ft_bzero(&game->menu, sizeof(t_menu));
	game->menu.current_frame = 0;
	game->menu.total_frames = 0;
	game->menu.last_frame_time = ft_get_time();
	game->menu.menu_music_pid = ft_play_audio("music&sounds/menu.wav", game->env);
	
	game->menu.scaled_frame = ft_alloc_lst(sizeof(t_texture), 4);
	game->menu.scaled_frame->img = (t_img *)mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->menu.scaled_frame->img)
		ft_close_game(1);
	game->menu.scaled_frame->width = WINDOW_WIDTH;
	game->menu.scaled_frame->height = WINDOW_HEIGHT;
	game->menu.scaled_frame->colors_matrix = ft_alloc_lst(
		sizeof(unsigned int *) * WINDOW_HEIGHT, 4);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		game->menu.scaled_frame->colors_matrix[i] = (unsigned int *)
			(game->menu.scaled_frame->img->data + (i * sizeof(unsigned int) * WINDOW_WIDTH));
		i++;
	}
	ft_load_menu_frames(game);
}

void	ft_free_menu(t_game *game)
{
	int i;

	i = 0;
	while (i < game->menu.total_frames)
	{
		if (game->menu.frames[i])
			mlx_destroy_image(game->mlx, game->menu.frames[i]);
		i++;
	}
	if (game->menu.scaled_frame && game->menu.scaled_frame->img)
		mlx_destroy_image(game->mlx, game->menu.scaled_frame->img);
}
