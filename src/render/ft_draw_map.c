#include "../../includes/cub_3d.h"

void ft_draw_pixel_in_img(int x, int y, int color)
{
    char *img_data;
	

	img_data = mlx_get_data_addr(game->img_map, &bpp, &size_line, &endian);
	if (x >= 0 && x < game->width_height[0] * 30 && y >= 0 && y < game->width_height[1] * 30)
		*(unsigned int *)(img_data + (y * size_line + x * (bpp / 8))) = color;
}
void ft_draw_sq(t_game *game, int x, int y, int color)
{
    int i; 
    int j; 
    int size;

    i = 0;
    size = 30;

    while(i < size)
    {
        j = 0;
        while(j < size)
        {
            ft_draw_pixel_in_img(game->mlx, game->window,  x + j, y + i, color);
            j++;
        }
        i++;
    }
}
void    ft_draw_map(t_game *game)
{
    int x; 
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
			else if(game->map[y][x] == 'N' || game->map[y][x] == 'S'
				|| game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{	
				ft_draw_sq(game, x * cuadrado, y * cuadrado, C_GREY);
				ft_draw_sq(game, x * cuadrado, y * cuadrado, C_RED);
			} 
			x++;
        }
        y++;
    }
}
