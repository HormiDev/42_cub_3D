/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_t_image_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:41:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

int	*ft_scale_precalc_y(t_game *game)
{
	int	*syt;
	int	i;

	printf("Creating syt with size: %d\n", WINDOW_HEIGHT);
	syt = hd_malloc(sizeof(int) * WINDOW_HEIGHT);
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		syt[i] = (int)((double)i * (double)game->config.render_height
				/ (double)WINDOW_HEIGHT);
		i++;
	}
	return (syt);
}

int	*ft_scale_precalc_x(t_game *game)
{
	int	*sxt;
	int	i;

	printf("Creating sxt with size: %d\n", WINDOW_WIDTH);
	sxt = hd_malloc(sizeof(int) * WINDOW_WIDTH);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		sxt[i] = (int)((double)i * (double)game->config.render_width
				/ (double)WINDOW_WIDTH);
		i++;
	}
	return (sxt);
}

void	ft_scale_t_image_precalc(t_texture *to, t_texture *text_destiny,
		t_game *game)
{
	t_vector_int	dest;

	dest = (t_vector_int){0, 0};
	while (dest.y < text_destiny->height)
	{
		dest.x = 0;
		while (dest.x < text_destiny->width)
		{
			text_destiny->cmx[dest.y][dest.x]
				= to->cmx[game->precalc.syt[dest.y]][game->precalc.sxt[dest.x]];
			dest.x++;
		}
		dest.y++;
	}
}
