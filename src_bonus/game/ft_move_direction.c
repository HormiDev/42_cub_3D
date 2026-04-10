/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:32:01 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:07:34 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static void	ft_reposition_player(t_game *game, t_raycast *colision_ray,
		double ray_move)
{
	t_vector2	vector;

	vector = game->player->position;
	vector.x -= ray_move;
	ft_raycast(&(t_raycast_input){game, 90.0, &colision_ray[5], DCP, vector});
	vector = game->player->position;
	vector.y += ray_move;
	ft_raycast(&(t_raycast_input){game, 180.0, &colision_ray[2], DCP, vector});
	vector = game->player->position;
	vector.y -= ray_move;
	ft_raycast(&(t_raycast_input){game, 180.0, &colision_ray[6], DCP, vector});
	vector = game->player->position;
	vector.x += ray_move;
	ft_raycast(&(t_raycast_input){game, 270.0, &colision_ray[3], DCP, vector});
	vector = game->player->position;
	vector.x -= ray_move;
	ft_raycast(&(t_raycast_input){game, 270.0, &colision_ray[7], DCP, vector});
	if (colision_ray[0].type != -1 || colision_ray[4].type != -1)
		game->player->position.x = (int)(game->player->position.x) + 1.0 - DCP;
	if (colision_ray[1].type != -1 || colision_ray[5].type != -1)
		game->player->position.y = (int)(game->player->position.y) + 1.0 - DCP;
	if (colision_ray[2].type != -1 || colision_ray[6].type != -1)
		game->player->position.x = (int)(game->player->position.x) + DCP;
	if (colision_ray[3].type != -1 || colision_ray[7].type != -1)
		game->player->position.y = (int)(game->player->position.y) + DCP;
}

static void	ft_apply_move_from_ray(t_game *game, t_raycast *ray)
{
	if (ray->type == -1)
		ft_move_player(game, ray->impact.x, ray->impact.y);
	else if (ray->type == WALL_NO || ray->type == WALL_SO)
		ft_move_player(game, ray->impact.x, game->player->position.y);
	else if (ray->type == WALL_EA || ray->type == WALL_WE)
		ft_move_player(game, game->player->position.x, ray->impact.y);
}

static void	ft_cast_move_collisions(t_game *game, t_raycast *colision_ray,
		double ray_move)
{
	t_vector2	vector;

	vector = game->player->position;
	vector.y += ray_move;
	ft_raycast(&(t_raycast_input){game, 0.0, &colision_ray[0], DCP, vector});
	vector = game->player->position;
	vector.y -= ray_move;
	ft_raycast(&(t_raycast_input){game, 0.0, &colision_ray[4], DCP, vector});
	vector = game->player->position;
	vector.x += ray_move;
	ft_raycast(&(t_raycast_input){game, 90.0, &colision_ray[1], DCP, vector});
}

void	ft_move_direction(t_game *game, double angle, double move_speed,
		int player_index)
{
	t_raycast	ray;
	t_raycast	colision_ray[8];
	double		ray_move;

	game->actions[player_index].walk = 1;
	angle = ft_normalize_angle(angle);
	ft_raycast(&(t_raycast_input){game, angle, &ray, move_speed
		* game->delta_time, game->player->position});
	ft_apply_move_from_ray(game, &ray);
	ray_move = DCP / 2;
	ft_cast_move_collisions(game, colision_ray, ray_move);
	ft_reposition_player(game, colision_ray, ray_move);
}
