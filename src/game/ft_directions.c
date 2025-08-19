#include "../../includes/cub3d.h"

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
		ft_move_player(game, ray.impact.x, ray.impact.y);
}