
#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"

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