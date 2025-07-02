#include "../../includes/cub_3d.h"

void ft_draw_pixel_in_img(t_game *game, int x, int y, int color)
{
	char *pixel;
	if (x >= 0 && (x < game->width_height[0] * TILE_MAP_SIZE) &&
		y >= 0 && (y < game->width_height[1] * TILE_MAP_SIZE))
	{
		pixel = game->img_map->img_data + (y * game->img_map->image_len + x * (game->img_map->bits_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

void ft_draw_circle(t_game *game, int cx, int cy, int color)
{
	int x;
	int y;
	int radius;
	int aux_radius;

	radius = TILE_MAP_SIZE / 6;
	aux_radius = radius * radius;
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= aux_radius)
				ft_draw_pixel_in_img(game, cx + x, cy + y, color);
			x++;
		}
		y++;
	}
}

void ft_draw_sq(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE_MAP_SIZE)
	{
		j = 0;
		while (j < TILE_MAP_SIZE)
		{
			ft_draw_pixel_in_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

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

double ft_vector_distance(t_vector2 a, t_vector2 b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void ft_raycast(t_game *game, double angle, double ray_length)
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
					if (raydir.x > ft_cos(angle) * ray_length)
					{
						raydir.x = ft_cos(angle) * ray_length;
						raydir.y = ft_sin(angle) * ray_length;
						ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE}, (t_vector2){(raydir.x + game->player.position.x) * TILE_MAP_SIZE, (game->player.reverse_y_position - raydir.y) * TILE_MAP_SIZE}, color);
						break;
					}
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
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
					if (raydir.y > ft_sin(angle) * ray_length)
					{
						raydir.x = ft_cos(angle) * ray_length;
						raydir.y = ft_sin(angle) * ray_length;
						ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE}, (t_vector2){(raydir.x + game->player.position.x) * TILE_MAP_SIZE, (game->player.reverse_y_position - raydir.y) * TILE_MAP_SIZE}, color);
						break;
					}
					//printf("Ray hit wall at (%d, %d)\n", next_x, next_y);
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

void ft_draw_player(t_game *game)
{
	int px;
	int py;
	t_vector2 front;
	t_vector2 right;
	t_vector2 left;

	px = (int)(game->player.position.x * TILE_MAP_SIZE);
	py = (int)(game->player.reverse_y_position * TILE_MAP_SIZE);
	ft_draw_circle(game, px, py, C_RED);

	front.x = ft_cos((game->player.rotation.x)) * TILE_MAP_SIZE / 3 + px;
	front.y = -ft_sin((game->player.rotation.x)) * TILE_MAP_SIZE / 3 + py;
	right.x = ft_cos((game->player.rotation.x + 90)) * TILE_MAP_SIZE / 7 + px;
	right.y = -ft_sin((game->player.rotation.x + 90)) * TILE_MAP_SIZE / 7 + py;
	left.x = ft_cos((game->player.rotation.x - 90)) * TILE_MAP_SIZE / 7 + px;
	left.y = -ft_sin((game->player.rotation.x - 90)) * TILE_MAP_SIZE / 7 + py;
	ft_draw_line_in_image(game, left, front, C_RED);
	ft_draw_line_in_image(game, right, front, C_RED);
	ft_draw_line_in_image(game, (t_vector2){px, py}, front, C_RED);
}

void ft_draw_map(t_game *game)
{
	int x;
	int y;
	int ry;
	int i;
	double fov = 45.0;
	int ray_count = 3200;
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
		ft_raycast(game, current_angle, 2.0);
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

