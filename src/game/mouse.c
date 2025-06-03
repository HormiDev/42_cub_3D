/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:56:43 by ismherna          #+#    #+#             */
/*   Updated: 2025/06/03 16:31:37 by ide-dieg         ###   ########.fr       */
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

int ft_mouse_move(t_game *game)
{
    double sensitivity;
    int mouse_position_x;
    int mouse_position_y;
    
    mouse_position_x = 0;
    mouse_position_y = 0;
    sensitivity = 0.003;
    mlx_mouse_get_pos(game->mlx, game->window, &mouse_position_x,
        &mouse_position_y);
    game->player.rotation.x += (mouse_position_x - (WINDOW_WIDTH / 2 ))* sensitivity;
    if (game->player.rotation.x < 0)
        game->player.rotation.x += 360;
    else if (game->player.rotation.x >= 360)
        game->player.rotation.x -= 360;
    mlx_mouse_move(game->mlx, game->window, WINDOW_WIDTH/ 2, WINDOW_HEIGHT / 2);
    return (0);
}