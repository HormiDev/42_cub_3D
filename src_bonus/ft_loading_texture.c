/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:02:05 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/27 04:26:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void ft_texture_matrix(t_texture *texture)
{
	int i;

	texture->colors_matrix = ft_alloc_lst(sizeof(unsigned int *) * texture->height, 4);// usar hd_alloc
	i = 0;
	while (i < texture->height)
	{
		texture->colors_matrix[i] = (unsigned int *)(texture->img->data +
				(i * sizeof(unsigned int) * texture->width));
		i++;
	}
}

t_texture *ft_loading_texture(void *mlx_ptr, char *path)
{
	int width;
	int height;
	t_img *img;
	t_texture *texture;

	img = (t_img *)mlx_xpm_file_to_image(mlx_ptr, path, &width, &height);// usar hd alloc
	if (!img)
	{
		ft_dprintf(2, RED "Error: Failed to load texture from path: %s\n" RESET, path);
		return (NULL);
	}
	texture = ft_alloc_lst(sizeof(t_texture), 4);// usar hd alloc
	texture->path = ft_strdup_ae(path);//usar hd_alloc
	texture->img = img;
	texture->width = width;
	texture->height = height;
	ft_texture_matrix(texture);
	return (texture);
}

t_texture *ft_new_texture(void *mlx_ptr, int width, int height)
{
	t_texture *texture;

	texture = ft_alloc_lst(sizeof(t_texture), 4);// usar hd_alloc
	texture->img = mlx_new_image(mlx_ptr, width, height);// usar hd_alloc
	if (!texture->img)
	{
		ft_dprintf(2, RED "Error: Failed to create new texture image\n" RESET);
		return (NULL);
	}
	texture->width = width;
	texture->height = height;
	ft_texture_matrix(texture);
	return (texture);
}
