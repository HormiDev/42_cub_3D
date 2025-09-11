/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_t_image.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:41:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/09/11 17:29:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void ft_scale_t_image(t_texture *tex_origin, t_texture *text_destiny)
{
	int 	dest_x;
	int 	dest_y;
	double	scale_x;
	double	scale_y;

	dest_x = 0;
	dest_y = 0;
	scale_x = (double)tex_origin->width / (double)text_destiny->width;
	scale_y = (double)tex_origin->height / (double)text_destiny->height;
	while (dest_y < text_destiny->height)
	{
		dest_x = 0;
		while (dest_x < text_destiny->width)
		{
			text_destiny->colors_matrix[dest_y][dest_x] = tex_origin->colors_matrix
				[(int)((double)dest_y * scale_y)]
				[(int)((double)dest_x * scale_x)];
			dest_x++;
		}
		dest_y++;
	}
}