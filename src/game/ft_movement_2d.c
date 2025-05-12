#include "../../includes/cub_3d.h"

/*

*/

void ft_forwad_back(t_game *game, double move_speed)
{
	double new_x;
	double new_y; 

	new_x = game->player.x + game->player.dir_x * move_speed; 
	new_y = game->player.y + game->player.dir_y * move_speed; 

	if(new_x >= 0 && new_x < game->width_height[0] && new_y < game->width_height[1])
	{
		if(game->map[(int)new_y][(int)new_x] != '1')
		{
			game->player.y = new_y;
			game->player.x = new_x;
		}
	}
}

void ft_right_left(t_game *game, double move_speed)
{
	double new_x;
	double new_y; 
	double lateral_x;
	double lateral_y; 

	lateral_x = -game->player.dir_y;
	lateral_y = game->player.dir_x;
	new_x = game->player.x + lateral_x * move_speed; 
	new_y = game->player.y + lateral_y * move_speed; 

	if (new_x >= 0 && new_x < game->width_height[0] && new_y >= 0 && new_y < game->width_height[1]) 
	{
		if(game->map[(int)lateral_y][(int)game->player.x] != '1')
			game->player.y = lateral_y;
		if(game->map[(int)game->player.y][(int)lateral_x] != '1')
			game->player.x = lateral_x;
	}
}

void ft_handle_key(int keycode, t_game *game)
{
	if(keycode == ESC)
		ft_close_game(0);
	else if(keycode == W)
		ft_forwad_back(game, 30); 
	else if(keycode == S)
		ft_forwad_back(game, -30);
	else if(keycode == A)
		ft_right_left(game, -30);
	else if(keycode == D)
		ft_right_left(game, 30);
}