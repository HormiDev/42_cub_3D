/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_t_image_precalc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:41:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 02:58:06 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static void	ft_scale_precalc_two_bounds(int player, t_texture *text_destiny,
		t_vector_int *dest, int *dest_end_y)
{
	*dest = (t_vector_int){0, 0};
	if (player == 0)
		*dest_end_y = text_destiny->height / 2;
	else
	{
		*dest_end_y = text_destiny->height;
		dest->y = text_destiny->height / 2;
	}
}

void	ft_scale_t_image_precalc_two(t_texture *tex_origin,
		t_texture *text_destiny, t_game *game, int player)
{
	t_vector_int	dest;
	t_vector_int	ori;
	int				dest_end_y;

	ft_scale_precalc_two_bounds(player, text_destiny, &dest, &dest_end_y);
	ori.y = 0;
	while (dest.y < dest_end_y)
	{
		dest.x = 0;
		while (dest.x < text_destiny->width)
		{
			text_destiny->cmx[dest.y][dest.x]
				= tex_origin->cmx[game->precalc.syt[ori.y]]
			[game->precalc.sxt[dest.x]];
			dest.x++;
		}
		dest.y++;
		ori.y++;
	}
}

static void	ft_scale_precalc_three_bounds(int player, t_texture *text_destiny,
		t_vector_int *dest, t_vector_int *dest_end)
{
	*dest = (t_vector_int){0, 0};
	*dest_end = (t_vector_int){0, 0};
	if (player == 0 || player == 2)
		dest_end->y = text_destiny->height / 2;
	else
	{
		dest_end->y = text_destiny->height;
		dest->y = text_destiny->height / 2;
	}
	if (player == 0 || player == 1)
		dest_end->x = text_destiny->width / 2;
	else
	{
		dest_end->x = text_destiny->width;
		dest->x = text_destiny->width / 2;
	}
}

void	ft_scale_t_image_precalc_three(t_texture *tex_origin,
		t_texture *text_destiny, t_game *game, int player)
{
	t_vector_int	dest;
	t_vector_int	ori;
	t_vector_int	dest_end;

	ft_scale_precalc_three_bounds(player, text_destiny, &dest, &dest_end);
	ori = (t_vector_int){0, 0};
	while (dest.y < dest_end.y)
	{
		dest.x = 0;
		ori.x = 0;
		while (dest.x < dest_end.x)
		{
			text_destiny->cmx[dest.y][dest.x]
				= tex_origin->cmx[game->precalc.syt[ori.y]]
			[game->precalc.sxt[ori.x]];
			dest.x++;
			ori.x++;
		}
		dest.y++;
		ori.y++;
	}
}
