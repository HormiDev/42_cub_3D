/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pueba.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 16:54:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/18 19:59:04 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_prueba
{
	void *mlx;
	void *window;
	void *img;
	void *img2;
	int imgwidth;
	int imgheight;
	long last_frame_time;
	double delta_time;

	double img_x;
	double img_y;
} t_prueba;

long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int ft_update(void *param)
{
	t_prueba *prueba = (t_prueba *)param;
	long current_time;
	current_time = ft_get_time();
	prueba->delta_time = (current_time - prueba->last_frame_time) / 1000.0;
	prueba->last_frame_time = current_time;
	//printf("FPS: %d\n", (int)(1 / prueba->delta_time));

	prueba->img_x += (prueba->delta_time * 100); // Mueve la imagen a la derecha
	if (prueba->img_x > 800) // Resetea la posición si sale
		prueba->img_x = 0;
	prueba->img_y += (prueba->delta_time * 373); // Mueve la imagen hacia abajo
	if (prueba->img_y > 800) // Resetea la posición si sale
		prueba->img_y = 0;

	usleep(1000); // Espera 10 ms para limitar la velocidad de actualización
	//mlx_clear_window(prueba->mlx, prueba->window);
	mlx_put_image_to_window(prueba->mlx, prueba->window, prueba->img2, 0, 0);
	//mlx_put_image_to_window(prueba->mlx, prueba->window, prueba->img, prueba->img_x, prueba->img_y);
	return (0);
}

int main(void)
{
	t_prueba prueba;

	prueba.mlx = mlx_init();
	prueba.window = mlx_new_window(prueba.mlx, 800, 800, "Test Window");
	prueba.img = mlx_xpm_file_to_image(prueba.mlx, "textures/ladrillos_este.xpm", &prueba.imgwidth, &prueba.imgheight);
	prueba.img2 = mlx_xpm_file_to_image(prueba.mlx, "textures/ladrillos1.xpm", &prueba.imgwidth, &prueba.imgheight);
	prueba.img_x = 0;
	prueba.img_y = 0;
	if (!prueba.img !prueba.img2)
	{
		fprintf(stderr, "Error loading image 1\n");
		return (1);
	}
	printf("bits_per_pixel: %d\n", ((t_img *)(prueba.img2))->bpp);
	prueba.last_frame_time = ft_get_time();
	mlx_loop_hook(prueba.mlx, ft_update, &prueba);
	mlx_loop(prueba.mlx);
	return (0);
}