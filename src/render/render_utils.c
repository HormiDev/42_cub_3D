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