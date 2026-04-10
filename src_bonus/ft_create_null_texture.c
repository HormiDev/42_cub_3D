/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_null_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 17:18:30 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 02:48:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_create_null_texture(t_game *game)
{
	unsigned int	null_color;
	unsigned int	black;

	null_color = 0xFFD400FF;
	black = 0xFF000000;
	game->null_texture = ft_new_texture(game->mlx, 2, 2);
	game->null_texture->cmx[0][0] = null_color;
	game->null_texture->cmx[0][1] = black;
	game->null_texture->cmx[1][0] = black;
	game->null_texture->cmx[1][1] = null_color;
}
