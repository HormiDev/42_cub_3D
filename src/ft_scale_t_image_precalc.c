/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_t_image_precalc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:41:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/27 15:35:38 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

int *ft_scale_precalc_y(void)
{
	int *scale_y_table;
	int i;

	printf("Creating scale_y_table with size: %d\n", WINDOW_HEIGHT);
	scale_y_table = ft_alloc_lst(sizeof(int) * WINDOW_HEIGHT, 3);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		scale_y_table[i] = (int)((double)i * (double)RENDER_HEIGHT / (double)WINDOW_HEIGHT);
		i++;
	}
	return scale_y_table;
}

int	*ft_scale_precalc_x(void)
{
	int *scale_x_table;
	int i;

	printf("Creating scale_x_table with size: %d\n", WINDOW_WIDTH);
	scale_x_table = ft_alloc_lst(sizeof(int) * WINDOW_WIDTH, 3);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		scale_x_table[i] = (int)((double)i * (double)RENDER_WIDTH / (double)WINDOW_WIDTH);
		i++;
	}
	return scale_x_table;
}

void ft_scale_t_image_precalc(t_texture *tex_origin, t_texture *text_destiny, t_game *game)
{
	int 	dest_x;
	int 	dest_y;

	dest_x = 0;
	dest_y = 0;
	while (dest_y < text_destiny->height)
	{
		dest_x = 0;
		while (dest_x < text_destiny->width)
		{
			text_destiny->colors_matrix[dest_y][dest_x] = tex_origin->colors_matrix
				[game->precalc.scale_y_table[dest_y]]
				[game->precalc.scale_x_table[dest_x]];
			dest_x++;
		}
		dest_y++;
	}
}