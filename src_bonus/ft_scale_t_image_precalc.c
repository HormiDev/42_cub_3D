/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scale_t_image_precalc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:41:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
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

void	ft_scale_t_image_precalc_two(t_texture *to,
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
				= to->cmx[game->precalc.syt[ori.y]]
			[game->precalc.sxt[dest.x]];
			dest.x++;
		}
		dest.y++;
		ori.y++;
	}
}

static void	ft_scale_t_image_precalc_three_aux(t_texture **to_td, t_game *game,
				int player, t_vector_int *d_e_o)
{
	while (d_e_o[0].y < d_e_o[1].y)
	{
		d_e_o[0].x = 0;
		d_e_o[2].x = 0;
		if (player == 0 || player == 1)
			d_e_o[1].x = to_td[1]->width / 2;
		else
		{
			d_e_o[1].x = to_td[1]->width;
			d_e_o[0].x = to_td[1]->width / 2;
		}
		while (d_e_o[0].x < d_e_o[1].x)
		{
			to_td[1]->cmx[d_e_o[0].y][d_e_o[0].x]
				= to_td[0]->cmx[game->precalc.syt[d_e_o[2].y]]
			[game->precalc.sxt[d_e_o[2].x]];
			d_e_o[0].x++;
			d_e_o[2].x++;
		}
		d_e_o[0].y++;
		d_e_o[2].y++;
	}
}

/*
 * deo es dest end y origin 
*/
void	ft_scale_t_image_precalc_three(t_texture *to, t_texture *text_destiny,
			t_game *game, int player)
{
	t_vector_int	d_e_o[3];
	t_texture		*to_td[2];

	to_td[0] = to;
	to_td[1] = text_destiny;
	d_e_o[0].y = 0;
	d_e_o[2].y = 0;
	if (player == 0 || player == 2)
		d_e_o[1].y = to_td[1]->height / 2;
	else
	{
		d_e_o[1].y = to_td[1]->height;
		d_e_o[0].y = to_td[1]->height / 2;
	}
	ft_scale_t_image_precalc_three_aux(to_td, game, player, d_e_o);
}
