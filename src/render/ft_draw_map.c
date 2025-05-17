#include "../../includes/cub_3d.h"


void ft_draw_ray()
{

}

void ft_draw_pixel_in_img(t_game *game,int x, int y, int color)
{
    char *pixel; 
    if(x >= 0 && (x < game->width_height[0] * TILE_MAP_SIZE) &&
        y >= 0 && (y < game->width_height[1] * TILE_MAP_SIZE))
    {
        pixel = game->img_map->img_data + (y * game->img_map->image_len + x * (game->img_map->bits_pixel / 8));
        *(unsigned int *)pixel = color; 
    }
}

void ft_draw_circle(t_game *game , int cx, int cy , int color)
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
    while(i < TILE_MAP_SIZE)
    {
        j = 0;
        while(j < TILE_MAP_SIZE)
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
    while(i <= aux_w)
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
    while(i <= aux_h)
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

void    ft_draw_map(t_game *game)
{
    int x; 
    int px;
    int py;
    int y; 

    y = 0; 
    while(y < game->width_height[1])
    {
        x = 0; 
        while(x < game->width_height[0])
        {
            if(game->map[y][x] == '1')
                ft_draw_sq(game, x * TILE_MAP_SIZE, y * TILE_MAP_SIZE, C_WHITE);
            else if(game->map[y][x] == '0')
                ft_draw_sq(game,  x * TILE_MAP_SIZE, y * TILE_MAP_SIZE, C_GREY);
			else if(game->map[y][x] == ' ')
				ft_draw_sq(game, x * TILE_MAP_SIZE, y * TILE_MAP_SIZE, C_BLACK);
			x++;
        }
        y++;
    }
    px = (int)game->player.position.x;
    py = (int)game->player.position.y;
    //ft_draw_sq(game, px - 5, py - 5, C_RED);
    ft_draw_circle(game, px, py, C_RED);
    ft_draw_grid(game, C_BLUE);
    mlx_put_image_to_window(game->mlx, game->window, game->img_map->img, 0, 0); 
}
