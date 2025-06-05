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
    t_vector2	pixel;
    int         steps;
    int         i;
	t_vector2	increment;

	printf("Dibujando línea desde (%.2f, %.2f) hasta (%.2f, %.2f)\n", start.x, start.y, end.x, end.y);
    steps = ft_int_max(ft_int_diff(start.x, end.x), ft_int_diff(start.y, end.y));
    i = 0;
    pixel.x = start.x;
    pixel.y = start.y;
    increment.x = (start.x - end.x) / steps;
    increment.y = (start.y - end.y) / steps;
    while (i <= steps)
    {
        ft_draw_pixel_in_img(game, (int)pixel.x, (int)pixel.y, color);
        pixel.x += increment.x;
        pixel.y += increment.y;
        i++;
    }
}

double ft_angle_rad(double degrees)
{
    return degrees * M_PI / 180.0; 
}

char ft_get_cell_at(t_game *game, int x, int y)
{
    int map_x;
    int map_y;

    map_x = x / TILE_MAP_SIZE;
    map_y = y / TILE_MAP_SIZE;

    return game->map[map_y][map_x];
}

void ft_raycast(t_game *game, int color)
{
    double		angle_rad;
    t_vector2	distance;
	int			tile_xy[2];
	
	tile_xy[0] = (int)game->player.position.x ;
	tile_xy[1] = (int)game->player.position.y ;
	printf("posicion del jugador: (%.2f, %.2f)\n", game->player.position.x, game->player.position.y);
	printf("Coordenadas del jugador: (%.d, %.d)\n", tile_xy[0], tile_xy[1]);
	angle_rad = ft_angle_rad(game->player.rotation.x);
	printf("entro a la funcion"); 
	if (game->player.rotation.x > 0 && game->player.rotation.x <= 90)
	{
		distance.x = game->player.position.y - -cos(angle_rad) * (double)(tile_xy[1] + 1);
		if (distance.x < tile_xy[0] + 1)
		{
			printf("Colisión cos con pared en coordenadas (%.2f, %.d)\n", distance.x, tile_xy[1] + 1);
			printf("Colisión cos con pared en coordenadas (%.2f, %.d)\n", distance.x * + game->player.position.x, tile_xy[1] + 1);
			ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.position.y * TILE_MAP_SIZE}, (t_vector2){(distance.x + game->player.position.x) * TILE_MAP_SIZE, (tile_xy[1] + 1) * TILE_MAP_SIZE}, color);
		}
		else
		{
			distance.y = sin(angle_rad) * (double)(tile_xy[0] + 1) - game->player.position.x;
			printf("Colisión sin con pared en coordenadas (%.d, %.2f)\n", tile_xy[0] + 1, distance.y);
			ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.position.y * TILE_MAP_SIZE}, (t_vector2){(tile_xy[0] + 1) * TILE_MAP_SIZE, distance.y * TILE_MAP_SIZE}, color);
		}
	}
}


void ft_draw_map(t_game *game)
{
	int x;
    int px;
    int py;
    int y;
	
    y = 0;
    while (y < game->width_height[1])
    {
		x = 0;
        while (x < game->width_height[0])
        {
			if (game->map[y][x] == '1')
			ft_draw_sq(game, x * TILE_MAP_SIZE, y * TILE_MAP_SIZE, C_WHITE);
		else if (game->map[y][x] == '0')
			ft_draw_sq(game, x * TILE_MAP_SIZE, y * TILE_MAP_SIZE, C_GREY);
		else if (game->map[y][x] == ' ')
			ft_draw_sq(game, x * TILE_MAP_SIZE, y * TILE_MAP_SIZE, C_BLACK);
		x++;
	}
	y++;
	}
	printf("Rotación del jugador: (%.2f)\n", game->player.rotation.x);
	px = (int)(game->player.position.x * TILE_MAP_SIZE);
	py = (int)(game->player.position.y * TILE_MAP_SIZE);
	ft_raycast(game, C_YELLOW);
	// ft_draw_sq(game, px - 5, py - 5, C_RED);
    ft_draw_circle(game, px, py, C_RED);
	ft_draw_circle(game, 0, 0, C_RED);
    ft_draw_grid(game, C_BLUE);
    mlx_put_image_to_window(game->mlx, game->window, game->img_map->img, 0, 0);
}
