/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:56:43 by ismherna          #+#    #+#             */
/*   Updated: 2025/06/08 18:48:26 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"
/*
int ft_mouse_move(int x, int y, t_game *game)
{
    int center_x = 1920 / 2;
    int delta_x = x - center_x;
    double sensitivity = 0.003;

    game->player.rotation.x += delta_x * sensitivity;

    if (game->player.rotation.x < 0)
        game->player.rotation.x += 360;
    else if (game->player.rotation.x >= 360)
        game->player.rotation.x -= 360;

    mlx_mouse_move(game->window, center_x, y);

    return (0);
}*/

int ft_mouse_move(int x, int y, t_game *game)
{
	game->mouse_xy[0] = x;
	game->mouse_xy[1] = y;
    game->player.rotation.x = 360 - (double)(360 / (double)WINDOW_WIDTH) * (double)x;
    if (y < 0)
        game->player.rotation.y += 1;
    else if (y > 0)
        game->player.rotation.y -= 1;
    return (0);
}
