#include "../../includes/cub_3d.h"

void ft_forwad_back(t_game *game, double move_speed)
{
	double new_x;
	double new_y;
	int map_x;
	int map_y;

	new_x = game->player.position.x;
	new_y = game->player.position.y + move_speed;

	map_x = (int)(new_x / TILE_MAP_SIZE);
	map_y = (int)(new_y / TILE_MAP_SIZE);

	if (map_x >= 0 && map_x < game->width_height[0] &&
		map_y >= 0 && map_y < game->width_height[1] &&
		game->map[map_y][map_x] != '1')
	{
		game->player.position.y = new_y;
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

	map_x = (int)(new_x / TILE_MAP_SIZE);
	map_y = (int)(new_y / TILE_MAP_SIZE);

	if(map_x >= 0 && map_x < game->width_height[0] &&
	   map_y >= 0 && map_y < game->width_height[1] &&
	    game->map[map_y][map_x] != '1')
	{
		game->player.position.x = new_x;
	}
}

/*
revisar movimientos diagonales fluidos
*/
int ft_handle_key(int keycode, t_game *game)
{
	if(keycode == ESC)
		ft_close_game(0);
	if(keycode == W)
		ft_forwad_back(game, -2); 
	if(keycode == S)
		ft_forwad_back(game, 2);
	if(keycode == A)
		ft_right_left(game, -2);
	if(keycode == D)
		ft_right_left(game, 2);
	mlx_clear_window(game->mlx, game->window);
	ft_draw_map(game);
	return (0);
}
