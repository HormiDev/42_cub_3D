
#ifndef CUB3D_H
#define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdib.h>
# include <stdio.h>

typedef struct mlx_data
{
	void *mlx;
	void *win;
	void *img;
	char *addr; 
	int	 bits_per_pixel; 
	int  line_lenght; 
	int  endian; 
	int  width; 
	int  height; 
} t_data;

# endif