/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_directions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 00:22:23 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/16 20:33:35 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void ft_forwad_back(t_game *game, double move_speed)
{
	double new_x;
	double new_y;
	int map_x;
	int map_y;

	new_x = game->player->position.x;
	new_y = game->player->position.y - move_speed;

	map_x = (int)(new_x);
	map_y = (int)(new_y);

	if (map_x >= 0 && map_x < game->width_height[0] &&
		map_y >= 0 && map_y < game->width_height[1] &&
		game->map[map_y][map_x] != '1')
	{
		game->player->position.y = new_y;
		game->player->reverse_y_position = -new_y + game->width_height[1];
	}
}

void ft_right_left(t_game *game, double move_speed)
{	
	double new_x;
	double new_y;
	int map_x;
	int map_y;

	new_x = game->player->position.x + move_speed;
	new_y = game->player->position.y;

	map_x = (int)(new_x);
	map_y = (int)(new_y);

	if(map_x >= 0 && map_x < game->width_height[0] &&
	   map_y >= 0 && map_y < game->width_height[1] &&
	    game->map[map_y][map_x] != '1')
	{
		game->player->position.x = new_x;
	}
}

void ft_move_player(t_game *game, double move_x, double move_y)
{
	game->player->position.x = move_x;
	game->player->position.y = move_y;
	game->player->reverse_y_position = -game->player->position.y + game->width_height[1];
}

void ft_move_direction(t_game *game, double angle, double move_speed)
{
	t_raycast ray;
	t_raycast colision_ray[4];

	angle = ft_normalize_angle(angle);
	ft_raycast(game, angle, &ray, move_speed * game->delta_time);
	if (ray.type == -1)
		ft_move_player(game, ray.impact.x, ray.impact.y);
	else if (ray.type == WALL_NO || ray.type == WALL_SO)
		ft_move_player(game, ray.impact.x, game->player->position.y);
	else if (ray.type == WALL_EA || ray.type == WALL_WE)
		ft_move_player(game, game->player->position.x, ray.impact.y);
	ft_raycast(game, 0.0, &colision_ray[0], DCP);
	ft_raycast(game, 90.0, &colision_ray[1], DCP);
	ft_raycast(game, 180.0, &colision_ray[2], DCP);
	ft_raycast(game, 270.0, &colision_ray[3], DCP);
	if (colision_ray[0].type != -1)
		game->player->position.x = (int)(game->player->position.x) + 1.0 - DCP;
	if (colision_ray[1].type != -1)
		game->player->position.y = (int)(game->player->position.y) + 1.0 - DCP;
	if (colision_ray[2].type != -1)
		game->player->position.x = (int)(game->player->position.x) + DCP;
	if (colision_ray[3].type != -1)
		game->player->position.y = (int)(game->player->position.y) + DCP;
}
