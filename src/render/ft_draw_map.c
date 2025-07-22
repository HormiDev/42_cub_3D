#include "../../includes/cub_3d.h"

void ft_draw_grid(t_game *game, int color)
{
	int i;
	int y;
	int x;
	int aux_w;
	int aux_h;

	aux_h = game->width_height[1] * TILE_MAP_SIZE;
	aux_w = game->width_height[0] * TILE_MAP_SIZE;
	i = 0;
	while (i <= aux_w)
	{
		y = 0;
		while (y < aux_h)
		{
			ft_draw_pixel_in_img(game, i, y, color);
			y++;
		}
		i += TILE_MAP_SIZE;
	}
	i = 0;
	while (i <= aux_h)
	{
		x = 0;
		while (x < aux_w)
		{
			ft_draw_pixel_in_img(game, x, i, color);
			x++;
		}
		i += TILE_MAP_SIZE;
	}
}

int ft_int_diff(int a, int b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int ft_int_max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void ft_draw_line_in_image(t_game *game, t_vector2 start, t_vector2 end, int color)
{
	t_vector2 pixel;
	int steps;
	int i;
	t_vector2 increment;

	// printf("Dibujando línea desde (%.2f, %.2f) hasta (%.2f, %.2f)\n", start.x, start.y, end.x, end.y);
	steps = ft_int_max(ft_int_diff(start.x, end.x), ft_int_diff(start.y, end.y));
	i = 0;
	pixel.x = start.x;
	pixel.y = start.y;
	increment.x = (start.x - end.x) / steps;
	increment.y = (start.y - end.y) / steps;
	while (i <= steps)
	{
		ft_draw_pixel_in_img(game, (int)pixel.x, (int)pixel.y, color);
		pixel.x -= increment.x;
		pixel.y -= increment.y;
		i++;
	}
}

double ft_double_diff(double a, double b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

double ft_vector_distance(t_vector2 a, t_vector2 b)
{
	t_vector2 diff;

	diff.x = ft_double_diff(a.x, b.x);
	diff.y = ft_double_diff(a.y, b.y);
	return sqrt(pow(diff.x, 2) + pow(diff.y, 2));
}

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
			if (distance.y > max_size)// si se supera la distancia maxima del rayo
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
		else if (aux_distance > distance.x) // si el rayo toca el tile izquierdo
		{
			if (distance.x > max_size) // si se supera la distancia maxima del rayo
			{
				ft_raycast_max_size(game, angle, ray, max_size, cuadrant);
				break;
			}
			ft_ray_iter_right(tile_ray_xy, cuadrant, 1);
			if (game->map[tile_ray_xy[1]][tile_ray_xy[0]] == '1') // si el tile izquierdo es una pared
			{
				distance.y = sin_cos[0] * (distance.x / sin_cos[1]); // calcular la distancia de y al tocar el tile izquierdo
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
	double fov = 45.0;
	int ray_count = WINDOW_WIDTH; // Number of rays to cast
	double angle_step = fov / ray_count;
	double start_angle = game->player.rotation.x - (fov / 2);

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
	while (i < ray_count)
	{
		double current_angle = start_angle + i * angle_step;
		ft_raycast(game, current_angle, &game->raycasts[i], MAX_RAY_SIZE);
		ft_draw_raycast(game, &game->raycasts[i]);
		i++;
	}
	ft_draw_player(game);
	ft_draw_grid(game, C_BLUE);
	ft_draw_line_in_image(game, (t_vector2){0, 0}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){0, game->width_height[1] * TILE_MAP_SIZE}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){game->width_height[0] * TILE_MAP_SIZE, 0}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){game->width_height[0] * TILE_MAP_SIZE, game->width_height[1] * TILE_MAP_SIZE}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	mlx_put_image_to_window(game->mlx, game->window, game->img_map->img, 0, 0);
}


/*void ft_raycast(t_game *game, double angle, t_raycast *ray)
{
	t_vector2 distance;
	int next_x;
	int next_y;
	t_vector2 raydir;
	
	int color = C_GREEN;

	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	//printf("\nRotación del jugador: (%.2f)\n", angle);
	//printf("Posición del jugador: (%.2f, %.2f)\n", game->player.position.x, game->player.position.y);
	if (angle >= 0 && angle < 90)
	{
		next_x = (int)game->player.position.x + 1;
		next_y = (int)game->player.position.y + 1;
		while (1)
		{	
			distance.x = next_x - game->player.position.x;
			distance.y = next_y - game->player.position.y;
			raydir.x = ft_cos(angle);
			raydir.y = ft_sin(angle);
			raydir.x = raydir.x * (distance.y / raydir.y);	
			//printf("Raydir: (%.2f, %.2f)\n", raydir.x, raydir.y);
			//printf("Distance: (%.2f, %.2f)\n", distance.x, distance.y);
			//printf("Next: (%d, %d)\n", next_x, next_y);
			if (raydir.x + game->player.position.x <= next_x)
			{
				if (game->map[next_y][next_x - 1] == '1')
				{
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = raydir.x + game->player.position.x;
					ray->impact.y = (-next_y + game->width_height[1]) * TILE_MAP_SIZE;
					ray->type = 0; // North
					ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE}, (t_vector2){(raydir.x + game->player.position.x) * TILE_MAP_SIZE, (-next_y + game->width_height[1]) * TILE_MAP_SIZE}, color);
					break;
				}
				else
					next_y++;
			}
			else
			{
				raydir.x = ft_cos(angle);
				raydir.y = raydir.y * (distance.x / raydir.x);
				if (game->map[next_y - 1][next_x] == '1')
				{
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = next_x;
					ray->impact.y = (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE;
					ray->type = 2; // East
					ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE}, (t_vector2){next_x * TILE_MAP_SIZE, (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE}, color);
					break;
				}
				else
					next_x++;
			}
		}	
	}
	else if (angle >= 90 && angle < 180)
	{
		next_x = (int)game->player.position.x;
		next_y = (int)game->player.position.y + 1;
		while (1)
		{	
			distance.x = next_x - game->player.position.x;
			distance.y = next_y - game->player.position.y;
			raydir.x = ft_cos(angle);
			raydir.y = ft_sin(angle);
			raydir.x = raydir.x * (distance.y / raydir.y);
			if (raydir.x + game->player.position.x >= next_x)
			{	
				if (game->map[next_y][next_x] == '1')
				{
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = next_x;
					ray->impact.y = (-next_y + game->width_height[1]) * TILE_MAP_SIZE;
					ray->type = 0; // North
					ft_draw_line_in_image(game,(t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE}, (t_vector2){(raydir.x + game->player.position.x) * TILE_MAP_SIZE, (-next_y + game->width_height[1]) * TILE_MAP_SIZE}, color);
					break;
				}
				else
					next_y++;
			}	
			else
			{
				raydir.x = ft_cos(angle);
				raydir.y = raydir.y * (distance.x / raydir.x);
				if (game->map[next_y - 1][next_x - 1] == '1')
				{
				
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = raydir.x + game->player.position.x;
					ray->impact.y = (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE;
					ray->type = 3; // West
					ft_draw_line_in_image(game,
						(t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
						(t_vector2){next_x * TILE_MAP_SIZE, (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE},
						color);
					break;
				}
				else
					next_x--;
			}
		}	
	}
	else if (angle >= 180 && angle < 270)
	{
		next_x = (int)game->player.position.x;
		next_y = (int)game->player.position.y;
		while (1)
		{		
			distance.x = next_x - game->player.position.x;
			distance.y = next_y - game->player.position.y;
			raydir.x = ft_cos(angle);
			raydir.y = ft_sin(angle);
			raydir.x = raydir.x * (distance.y / raydir.y);
			if (raydir.x + game->player.position.x >= next_x)
			{
				if (game->map[next_y - 1][next_x] == '1')
				{
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = next_x;
					ray->impact.y = (-next_y + game->width_height[1]) * TILE_MAP_SIZE;
					ray->type = 1; // South
					ft_draw_line_in_image(game,
						(t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
						(t_vector2){(raydir.x + game->player.position.x) * TILE_MAP_SIZE, (-next_y + game->width_height[1]) * TILE_MAP_SIZE},
						color);
					break;
				}
				else
					next_y--;
			}
			else
			{
				raydir.x = ft_cos(angle);
				raydir.y = raydir.y * (distance.x / raydir.x);
				if (game->map[next_y][next_x - 1] == '1')
				{
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = raydir.x + game->player.position.x;
					ray->impact.y = (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE;
					ray->type = 3; // West
					ft_draw_line_in_image(game,
						(t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
						(t_vector2){next_x * TILE_MAP_SIZE, (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE},
						color);
					break;
				}
				else
					next_x--;
			}
		}	
	}
	else if (angle >= 270 && angle < 360)
	{
		next_x = (int)game->player.position.x + 1;
		next_y = (int)game->player.position.y;
		while (1)
		{
			distance.x = next_x - game->player.position.x;
			distance.y = next_y - game->player.position.y;
			raydir.x = ft_cos(angle);
			raydir.y = ft_sin(angle);
			raydir.x = raydir.x * (distance.y / raydir.y);
			if (raydir.x + game->player.position.x <= next_x)
			{
				if (game->map[next_y - 1][next_x - 1] == '1')
				{
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = next_x;
					ray->impact.y = (-next_y + game->width_height[1]) * TILE_MAP_SIZE;
					ray->type = 1; // South
					ft_draw_line_in_image(game,
						(t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
						(t_vector2){(raydir.x + game->player.position.x) * TILE_MAP_SIZE, (-next_y + game->width_height[1]) * TILE_MAP_SIZE},
						color);
					break;
				}
				else
					next_y--;
			}
			else
			{
				raydir.x = ft_cos(angle);
				raydir.y = raydir.y * (distance.x / raydir.x);
				if (game->map[next_y][next_x] == '1')
				{
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
					ray->distance = ft_vector_distance(game->player.position, (t_vector2){next_x, next_y});
					ray->impact.x = next_x;
					ray->impact.y = (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE;
					ray->type = 2; // East
					ft_draw_line_in_image(game,
						(t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
						(t_vector2){next_x * TILE_MAP_SIZE, (-raydir.y + game->player.reverse_y_position) * TILE_MAP_SIZE},
						color);
					break;
				}
				else
					next_x++;
			}
		}	
	}
}
*/
