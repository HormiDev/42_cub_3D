#include "../../includes/cub_3d.h"

void ft_ray_iter_up(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[1] += iter;
	else if (cuadrant == 1)
		position_xy[0] -= iter;
	else if (cuadrant == 2)
		position_xy[1] -= iter;
	else
		position_xy[0] += iter;
}

void ft_ray_iter_right(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[0] += iter;
	else if (cuadrant == 1)
		position_xy[1] += iter;
	else if (cuadrant == 2)
		position_xy[0] -= iter;
	else
		position_xy[1] -= iter;
}

void ft_calc_distance(int cuadrant, int *tile_ray_xy, t_vector2 player_position, t_vector2 *distance)
{
	if (cuadrant == 0)
	{
		distance->x = tile_ray_xy[0] + 1 - player_position.x;
		distance->y = tile_ray_xy[1] + 1 - player_position.y;
	}
	else if (cuadrant == 1)
	{
		distance->x = tile_ray_xy[1] + 1 - player_position.y;
		distance->y = player_position.x - tile_ray_xy[0];
	}
	else if (cuadrant == 2)
	{
		distance->x = player_position.x - tile_ray_xy[0];
		distance->y = player_position.y - tile_ray_xy[1];
	}
	else
	{
		distance->x = player_position.y - tile_ray_xy[1];
		distance->y = tile_ray_xy[0] + 1 - player_position.x;
	}
}

void ft_rotate_to_cuadrant(int cuadrant, double *distance_x, double *distance_y)
{
	double aux_distance_x;

	aux_distance_x = *distance_x;
	if (cuadrant == 0)
		return ;
	else if (cuadrant == 1)
	{
		*distance_x = -(*distance_y);
		*distance_y = aux_distance_x;
	}
	else if (cuadrant == 2)
	{
		*distance_x = -(*distance_x);
		*distance_y = -(*distance_y);
	}
	else
	{
		*distance_x = *distance_y;
		*distance_y = -aux_distance_x;
	}
}

void ft_calc_ray_position(t_raycast *ray, t_vector2 *player_position, double distance_x, double distance_y)
{
	ray->impact.x = player_position->x + distance_x;
	ray->impact.y = player_position->y + distance_y;
	ray->distance = ft_vector_distance(*player_position, ray->impact);
}

void ft_ray_type(t_raycast *ray, int cuadrant, int up_right)
{
	if (up_right == 0)
	{
		if (cuadrant == 0)
			ray->type = WALL_NO;
		else if (cuadrant == 1)
			ray->type = WALL_WE;
		else if (cuadrant == 2)
			ray->type = WALL_SO;
		else
			ray->type = WALL_EA;
	}
	else
	{
		if (cuadrant == 0)
			ray->type = WALL_EA;
		else if (cuadrant == 1)
			ray->type = WALL_NO;
		else if (cuadrant == 2)
			ray->type = WALL_WE;
		else
			ray->type = WALL_SO;
	}
}

void ft_raycast_max_size(t_game *game, double angle, t_raycast *ray, double max_size, int cuadrant)
{
	t_vector2	distance;
	double		sin_cos[2];

	sin_cos[0] = ft_cos(angle);
	sin_cos[1] = ft_sin(angle);
	distance.x = sin_cos[0] * max_size;
	distance.y = sin_cos[1] * max_size;
	ft_rotate_to_cuadrant(cuadrant, &distance.x, &distance.y);
	ray->impact.x = game->player.position.x + distance.x;
	ray->impact.y = game->player.position.y + distance.y;
	ray->distance = max_size;
	ray->type = -1;
}

void ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size)
{
	int		tile_ray_xy[2];
	t_vector2	distance;
	double		sin_cos[2];
	int		cuadrant = 0;
	double		aux_distance;

	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	while (angle >= 90)
	{
		angle -= 90;
		cuadrant++;
	}
	ft_bzero(ray, sizeof(t_raycast));
	tile_ray_xy[0] = (int)game->player.position.x;
	tile_ray_xy[1] = (int)game->player.position.y;
	sin_cos[0] = ft_sin(angle);
	sin_cos[1] = ft_cos(angle);
	while(1)
	{
		ft_calc_distance(cuadrant, tile_ray_xy, game->player.position, &distance);
		aux_distance = sin_cos[1] * (distance.y / sin_cos[0]); // calcular la distancia de x al tocar el tile superior
		if (aux_distance < distance.x)// si el rayo toca el tile superior
		{
			if (distance.x > max_size + 1)// si se supera la distancia maxima del rayo ¡¡¡formula milagrosa, comparar distancias de senos y cosenos!!!
			{
				ft_raycast_max_size(game, angle, ray, max_size, cuadrant);
				break;
			}
			ft_ray_iter_up(tile_ray_xy, cuadrant, 1);
			if (game->map[tile_ray_xy[1]][tile_ray_xy[0]] == '1')// si el tile superior es una pared
			{
				ft_rotate_to_cuadrant(cuadrant, &aux_distance, &distance.y);
				ft_calc_ray_position(ray, &(game->player.position), aux_distance, distance.y);
				ft_ray_type(ray, cuadrant, 0);
				if (ray->distance > max_size) // si la distancia es mayor que la maxima, se sale del bucle
					ft_raycast_max_size(game, angle, ray, max_size, cuadrant);
				break ;
			}
		}
		else // si el rayo toca el tile izquierdo
		{
			aux_distance = sin_cos[0] * (distance.x / sin_cos[1]); // calcular la distancia de y al tocar el tile izquierdo
			if (distance.y > max_size + 1) // si se supera la distancia maxima del rayo
			{
				ft_raycast_max_size(game, angle, ray, max_size, cuadrant);
				break;
			}
			ft_ray_iter_right(tile_ray_xy, cuadrant, 1);
			if (game->map[tile_ray_xy[1]][tile_ray_xy[0]] == '1') // si el tile izquierdo es una pared
			{
				distance.y = aux_distance; // calcular la distancia de y al tocar el tile izquierdo
				ft_rotate_to_cuadrant(cuadrant, &distance.x, &distance.y);
				ft_calc_ray_position(ray, &(game->player.position), distance.x, distance.y);
				ft_ray_type(ray, cuadrant, 1);
				if (ray->distance > max_size) // si la distancia es mayor que la maxima, se sale del bucle
					ft_raycast_max_size(game, angle, ray, max_size, cuadrant);
				break ;
			}
		}
	}
}
void ft_draw_player(t_game *game)
{
	int px;
	int py;
	//t_vector2 front;
	//t_vector2 right;
	//t_vector2 left;
	//double angle;
	
	px = (int)(game->player.position.x * TILE_MAP_SIZE);
	py = (int)(game->player.reverse_y_position * TILE_MAP_SIZE);
	ft_draw_circle(game, px, py, C_RED);
	/*
	angle = game->player.rotation.x;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	while (angle > 90)
		angle -= 90;

	
	front.x = ft_cos((game->player.rotation.x)) * TILE_MAP_SIZE / 3 + px;
	front.y = -ft_sin((game->player.rotation.x)) * TILE_MAP_SIZE / 3 + py;
	right.x = ft_cos((game->player.rotation.x + 90)) * TILE_MAP_SIZE / 7 + px;
	right.y = -ft_sin((game->player.rotation.x + 90)) * TILE_MAP_SIZE / 7 + py;
	left.x = ft_cos((game->player.rotation.x - 90)) * TILE_MAP_SIZE / 7 + px;
	left.y = -ft_sin((game->player.rotation.x - 90)) * TILE_MAP_SIZE / 7 + py;
	ft_draw_line_in_image(game, left, front, C_RED);
	ft_draw_line_in_image(game, right, front, C_RED);
	ft_draw_line_in_image(game, (t_vector2){px, py}, front, C_RED);*/
}

void ft_draw_raycast(t_game *game, t_raycast *ray)
{
	int color;

	if (ray->type == WALL_NO)
		color = C_GREEN;
	else if (ray->type == WALL_SO)
		color = C_YELLOW;
	else if (ray->type == WALL_EA)
		color = C_BLUE;
	else if (ray->type == WALL_WE)
		color = C_RED;
	else
		color = C_WHITE;

	ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
		(t_vector2){ray->impact.x * TILE_MAP_SIZE, (-ray->impact.y + game->width_height[1]) * TILE_MAP_SIZE}, color);
}

void ft_draw_map(t_game *game)
{
	int x;
	int y;
	int ry;
	int i;

	y = 0;
	ry = game->width_height[1] - 1;
	while (y < game->width_height[1])
	{
		x = 0;
		while (x < game->width_height[0])
		{
			if (game->map[y][x] == '1')
			ft_draw_sq(game, x * TILE_MAP_SIZE, ry * TILE_MAP_SIZE, C_WHITE);
			else if (game->map[y][x] == '0')
			ft_draw_sq(game, x * TILE_MAP_SIZE, ry * TILE_MAP_SIZE, C_GREY);
		else if (game->map[y][x] == ' ')
		ft_draw_sq(game, x * TILE_MAP_SIZE, ry * TILE_MAP_SIZE, C_BLACK);
		x++;
		}
	y++;
	ry--;
	}
	
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		if (i % 10 == 0)
			ft_draw_raycast(game, &game->raycasts[i]);
		i++;
	}
	ft_draw_player(game);
	ft_draw_grid_horizontal(game, C_BLUE);
	ft_draw_grid_vertical(game, C_BLUE);
	ft_draw_line_in_image(game, (t_vector2){0, 0}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){0, game->width_height[1] * TILE_MAP_SIZE}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){game->width_height[0] * TILE_MAP_SIZE, 0}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){game->width_height[0] * TILE_MAP_SIZE, game->width_height[1] * TILE_MAP_SIZE}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
}