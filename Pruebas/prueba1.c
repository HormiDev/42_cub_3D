#include "../includes/cub3d.h"

int key_hook(int keycode, t_data *data)
{
    if (keycode == 53)
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    else if (keycode == 69)
    {
        data->width += 50;
        data->height += 50;
    }
    else if (keycode == 78)
    {
        if (data->width > 50 && data->height > 50)
        {
            data->width -= 50;
            data->height -= 50;
        }
    }
    create_image(data);
    return (0);
}

void create_image(t_data *data)
{
	int y = 0;
	int x = 0;
	if(data->img)
		mlx_delete_image(data->mlx, data->img)

	data.img = mlx_new_image(data.mlx, data->width, data->height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_lenght, &data.endian);

	while (y < data->height)
    {
        while (x < data->width)
        {
            int pixel = (y * data->line_length) + (x * (data->bits_per_pixel / 8));
            data->addr[pixel] = (char)(x % 255);         // Rojo
            data->addr[pixel + 1] = (char)(y % 255);     // Verde
            data->addr[pixel + 2] = (char)(255 - x % 255); // Azul
			x++; 
        }
		y++; 
    }
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_data data;
	
	data.width = 500; 
	data.height = 500; 

	if(argc > 1)
		data.width = atoi(argv[1]); 
	if (argc > 2)
		data.height = atoi(argv[2]);

	data.mlx = mlx_init(); 
	data.win = mlx_new_image(data.mlx, data.width, data.height, "MLX Image Resize"); 
	data.img = NULL; 

	create_image(&data);
	mlx_key_hook(data.win, key_hook, &data); 
	mlx_loop(data.mlx);
	return (0);
}