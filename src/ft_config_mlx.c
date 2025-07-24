/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:42:30 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/07/24 19:13:50 by ide-dieg         ###   ########.fr       */
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
		ft_dprintf(2, RED "Error:\n Failed to initialize mlx\n" RESET);
		ft_close_game(1);
	}
	game->window = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->window)
	{
		ft_dprintf(2, RED "Error:\n Failed to create window\n" RESET);
		ft_close_game(1);
	}
	game->img_map = ft_alloc_lst(sizeof(t_image), 4);
	game->img_map->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT); // Tamaño de ventana para 3D
	if (!game->img_map->img)
	{
		ft_dprintf(2, RED "Error:\n Failed to create image\n" RESET);
		ft_close_game(1);
	}
	
	game->img_map->img_data = mlx_get_data_addr(game->img_map->img, &game->img_map->bits_pixel, &game->img_map->image_len, &game->img_map->end);
	mlx_hook(game->window, 17, 0, ft_close_game_for_mlx, 0);//close window
	mlx_hook(game->window, 6, 1L << 6, ft_mouse_move, game); //mouse hook	
	mlx_hook(game->window, 2, 1L<<0, ft_key_press, game);     // key down
	mlx_hook(game->window, 3, 1L<<1, ft_key_release, game);   // key up
	mlx_loop_hook(game->mlx, ft_update, game);               // frame update

	//mlx_loop_hook(game->mlx, ft_update_game, game);//loop
}
