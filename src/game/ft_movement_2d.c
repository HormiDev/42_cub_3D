#include "../../includes/cub_3d.h"

void ft_forwad_back(t_game *game, double move_speed)
{
	double new_x;
	double new_y;
	int map_x;
	int map_y;

	new_x = game->player.position.x;
	new_y = game->player.position.y - move_speed;

	map_x = (int)(new_x);
	map_y = (int)(new_y);

	if (map_x >= 0 && map_x < game->width_height[0] &&
		map_y >= 0 && map_y < game->width_height[1] &&
		game->map[map_y][map_x] != '1')
	{
		game->player.position.y = new_y;
		game->player.reverse_y_position = -new_y + game->width_height[1];
	}
}

void ft_right_left(t_game *game, double move_speed)
{	
	double new_x;
	double new_y;
	int map_x;
	int map_y;

	new_x = game->player.position.x + move_speed;
	new_y = game->player.position.y;

	map_x = (int)(new_x);
	map_y = (int)(new_y);

	if(map_x >= 0 && map_x < game->width_height[0] &&
	   map_y >= 0 && map_y < game->width_height[1] &&
	    game->map[map_y][map_x] != '1')
	{
		game->player.position.x = new_x;
	}
}


int ft_key_press(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		ft_free_gamepad(game);
		ft_close_game(0);
	}
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

void ft_move_player(t_game *game, double move_x, double move_y)
{
	game->player.position.x = move_x;
	game->player.position.y = move_y;
	game->player.reverse_y_position = -game->player.position.y + game->width_height[1];
}

void ft_move_direction(t_game *game, double angle, double move_speed)
{
	t_raycast ray;

	if (angle < 0.0)
		angle += 360.0;
	else if (angle >= 360.0)
		angle -= 360.0;
	ft_raycast(game, angle, &ray, move_speed * game->delta_time);
	if (ray.type == -1)
		ft_move_player(game, move_speed * ray.impact.x, ray.impact.y);
}

void ft_movement_2d(t_game *game)
{
	// Actualizar estado del gamepad
	//ft_update_gamepad(game);
	
	// Procesamiento de movimiento con gamepad
	//ft_gamepad_movement(game);
	
	if (game->keys.w)
		ft_move_direction(game, game->player.rotation.x, 1);
	if (game->keys.s)
		ft_move_direction(game, game->player.rotation.x + 180, 1);
	if (game->keys.a)
		ft_move_direction(game, game->player.rotation.x + 270, 1);
	if (game->keys.d)
		ft_move_direction(game, game->player.rotation.x + 90, 1);
	if (game->keys.q)
	{
		game->player.rotation.x -= 2.0;
		if (game->player.rotation.x >= 360.0)
			game->player.rotation.x -= 360.0;
	}
	if (game->keys.e)
	{
		game->player.rotation.x += 2.0;
		if (game->player.rotation.x < 0.0)
			game->player.rotation.x += 360.0;
	}
}
