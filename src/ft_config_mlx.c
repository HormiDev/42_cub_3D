/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:42:30 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/12 14:08:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"


void	ft_free_mlx(t_game *game)
{
	if (game->mlx)
	{
		if (game->window)
			mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	ft_config_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_dprintf(2, "Error: Failed to initialize mlx\n");
		ft_close_game(1);
	}
	game->window = mlx_new_window(game->mlx, game->width_height[0] * 30, game->width_height[1] * 30, "Cub3D");
	if (!game->window)
	{
		ft_dprintf(2, "Error: Failed to create window\n");
		ft_close_game(1);
	}
	game->img_map = mlx_new_image(game->mlx, game->width_height[0] * 30, game->width_height[1] * 30);
	if (!game->img_map)
	{
		ft_dprintf(2, "Error: Failed to create image\n");
		ft_close_game(1);
	}
	
	mlx_hook(game->window, 17, 0, ft_close_game, game);//close window
	mlx_key_hook(game->window, ft_handle_key, game);//key pressed
	mlx_loop_hook(game->mlx, ft_update_game, game);//loop
    ft_draw_map(game); 
}