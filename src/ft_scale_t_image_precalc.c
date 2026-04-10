/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_t_image_precalc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:41:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 02:55:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

int	*ft_scale_precalc_y(void)
{
	int	*syt;
	int	i;

	printf("Creating syt with size: %d\n", WINDOW_HEIGHT);
	syt = hd_malloc(sizeof(int) * WINDOW_HEIGHT);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		syt[i] = (int)((double)i * (double)RENDER_HEIGHT
				/ (double)WINDOW_HEIGHT);
		i++;
	}
	return (syt);
}

int	*ft_scale_precalc_x(void)
{
	int	*sxt;
	int	i;

	printf("Creating sxt with size: %d\n", WINDOW_WIDTH);
	sxt = hd_malloc(sizeof(int) * WINDOW_WIDTH);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		sxt[i] = (int)((double)i * (double)RENDER_WIDTH
				/ (double)WINDOW_WIDTH);
		i++;
	}
	return (sxt);
}

void	ft_scale_t_image_precalc(t_texture *tex_origin, t_texture *text_destiny,
		t_game *game)
{
	int		dest_x;
	int		dest_y;

	dest_x = 0;
	dest_y = 0;
	while (dest_y < text_destiny->height)
	{
		dest_x = 0;
		while (dest_x < text_destiny->width)
		{
			text_destiny->cmx[dest_y][dest_x]
				= tex_origin->cmx[game->precalc.syt[dest_y]]
			[game->precalc.sxt[dest_x]];
			dest_x++;
		}
		dest_y++;
	}
}
