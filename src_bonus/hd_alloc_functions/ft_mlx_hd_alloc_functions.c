/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_mlx_hd_alloc_functions.c                       :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/17 19:12:03 by username         #+#    #+#              */
/*   Updated: 2026/04/07 23:25:04 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static void	ft_free_mlx_window(void *ptr)
{
	void	**mlx_window;

	mlx_window = (void **) ptr;
	if (mlx_window[0] && mlx_window[1])
		mlx_destroy_window(mlx_window[0], mlx_window[1]);
	free(mlx_window);
}

void	*ft_create_window(void *mlx, int size_x, int size_y, char *title)
{
	void	**mlx_window;

	mlx_window = hd_alloc(ft_calloc(1, sizeof(void *) * 2), ft_free_mlx_window);
	if (!mlx_window)
		return (NULL);
	mlx_window[0] = mlx;
	mlx_window[1] = mlx_new_window(mlx, size_x, size_y, title);
	if (!mlx_window[1])
	{
		hd_alloc(0, 0);
		return (NULL);
	}
	return (mlx_window[1]);
}

static void	ft_free_mlx_image(void *ptr)
{
	void	**mlx_image;

	mlx_image = (void **) ptr;
	if (mlx_image[0] && mlx_image[1])
		mlx_destroy_image(mlx_image[0], mlx_image[1]);
	free(mlx_image);
}

void	*ft_create_image(void *mlx, int size_x, int size_y)
{
	void	**mlx_image;

	mlx_image = hd_alloc(ft_calloc(1, sizeof(void *) * 2), ft_free_mlx_image);
	if (!mlx_image)
		return (NULL);
	mlx_image[0] = mlx;
	mlx_image[1] = mlx_new_image(mlx, size_x, size_y);
	if (!mlx_image[1])
	{
		hd_alloc(0, 0);
		return (NULL);
	}
	return (mlx_image[1]);
}

void * ft_mlx_xpm_file_to_image(void * mlx, char * filename,
	int	*width, int *height)
{
	void	**mlx_image;

	mlx_image = hd_alloc(ft_calloc(1, sizeof(void *) * 2), ft_free_mlx_image);
	if (!mlx_image)
		return (NULL);
	mlx_image[0] = mlx;
	mlx_image[1] = mlx_xpm_file_to_image(mlx, filename, width, height);
	if (!mlx_image[1])
	{
		hd_alloc(0, 0);
		return (NULL);
	}
	return (mlx_image[1]);
}
