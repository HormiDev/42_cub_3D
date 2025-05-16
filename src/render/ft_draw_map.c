#include "../../includes/cub_3d.h"

void ft_draw_pixel_in_img(t_game *game,int x, int y, int color)
{
    char *pixel; 
    if(x >= 0 && game->width_height[0] * 30 && y >= 0 && game->width_height[1] * 30)
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

    radius = 10; 
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
    int size; 

    size = 30; 
    i = 0;
    while(i < size)
    {
        j = 0;
        while(j < size)
        {
            ft_draw_pixel_in_img(game, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void    ft_draw_map(t_game *game)
{
    int x; 
    int px;
    int py;
    int y; 
    int cuadrado; 

    cuadrado = 30; 
    y = 0; 
    while(y < game->width_height[1])
    {
        x = 0; 
        while(x < game->width_height[0])
        {
            if(game->map[y][x] == '1')
                ft_draw_sq(game, x * cuadrado, y * cuadrado, C_WHITE);
            else if(game->map[y][x] == '0')
                ft_draw_sq(game,  x * cuadrado, y * cuadrado, C_GREY);
			else if(game->map[y][x] == ' ')
				ft_draw_sq(game, x * cuadrado, y * cuadrado, C_BLACK);
			x++;
        }
        y++;
    }
    px = (int)game->player.position.x;
    py = (int)game->player.position.y;
    //ft_draw_sq(game, px - 5, py - 5, C_RED);
    ft_draw_circle(game, px, py, C_RED);
    mlx_put_image_to_window(game->mlx, game->window, game->img_map->img, 0, 0); 
}
