#include "../../includes/cub_3d.h"

/*

*/

void ft_forwad_back(t_game *game, double move_speed)
{	
	game->player.position.y += move_speed;
}

void ft_right_left(t_game *game, double move_speed)
{
	game->player.position.x += move_speed;
}

int ft_handle_key(int keycode, t_game *game)
{
	if(keycode == ESC)
		ft_close_game(0);
	else if(keycode == W)
		ft_forwad_back(game, -5); 
	else if(keycode == S)
		ft_forwad_back(game, 5);
	else if(keycode == A)
		ft_right_left(game, -5);
	else if(keycode == D)
		ft_right_left(game, 5);
	mlx_clear_window(game->mlx, game->window);
	ft_draw_map(game);
}