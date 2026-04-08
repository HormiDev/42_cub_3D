/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_null_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:18:30 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/08 17:28:34 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_create_null_texture(t_game *game)
{
	unsigned int null_color = 0xFFD400FF;
	unsigned int black = 0xFF000000;

	game->null_texture = ft_new_texture(game->mlx, 2, 2);
	game->null_texture->cmx[0][0] = null_color;
	game->null_texture->cmx[0][1] = black;
	game->null_texture->cmx[1][0] = black;
	game->null_texture->cmx[1][1] = null_color;
}
