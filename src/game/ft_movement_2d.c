#include "../../includes/cub_3d.h"

void ft_right_left(t_game *game, double move_speed)
{
	double angle = ft_angle_rad(game->player.rotation.x);
	double dx = cos(angle) * move_speed; 
	double dy = sin(angle) * move_speed;

	double new_x = game->player.position.x + dx;
	double new_y = game->player.position.y + dy;

	int map_x = (int)(new_x);
	int map_y = (int)(new_y);

	if (map_x >= 0 && map_x < game->width_height[0] &&
		map_y >= 0 && map_y < game->width_height[1] &&
		game->map[map_y][map_x] != '1')
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

void ft_forwad_back(t_game *game, double move_speed)
{
	double angle = ft_angle_rad(game->player.rotation.x + 90.0);
	double dx = cos(angle) * move_speed; 
	double dy = sin(angle) * move_speed; 

	double new_x = game->player.position.x + dx;
	double new_y = game->player.position.y + dy;

	int map_x = (int)(new_x);
	int map_y = (int)(new_y);

	if (map_x >= 0 && map_x < game->width_height[0] &&
		map_y >= 0 && map_y < game->width_height[1] &&
		game->map[map_y][map_x] != '1')
	{
		game->player.position.x = new_x;
		game->player.position.y = new_y;
	}
}

int ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
		ft_close_game(0);
	if (keycode == W)
		game->keys.w = 1;
	if (keycode == A)
		game->keys.a = 1;
	if (keycode == S)
		game->keys.s = 1;
	if (keycode == D)
		game->keys.d = 1;
	if (keycode == Q)
		game->keys.q = 1;
	if (keycode == E)
		game->keys.e = 1;
	return (0);
}

int ft_key_release(int keycode, t_game *game)
{
	if (keycode == W)
		game->keys.w = 0;
	if (keycode == A)
		game->keys.a = 0;
	if (keycode == S)
		game->keys.s = 0;
	if (keycode == D)
		game->keys.d = 0;
	if (keycode == Q)
		game->keys.q = 0;
	if (keycode == E)
		game->keys.e = 0;
	return (0);
}

int ft_update(void *param)
{
	t_game *game = (t_game *)param;

	if (game->keys.w)
		ft_forwad_back(game, -0.02);
	if (game->keys.s)
		ft_forwad_back(game, 0.02);
	if (game->keys.a)
		ft_right_left(game, -0.02);
	if (game->keys.d)
		ft_right_left(game, 0.02);
	if (game->keys.q)
	{
		game->player.rotation.x += 2.0;
		if (game->player.rotation.x >= 360.0)
			game->player.rotation.x -= 360.0;
	}
	if (game->keys.e)
	{
		game->player.rotation.x -= 2.0;
		if (game->player.rotation.x < 0.0)
			game->player.rotation.x += 360.0;
	}

	mlx_clear_window(game->mlx, game->window);
	ft_draw_map(game);
	return (0);
}
