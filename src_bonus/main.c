/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:54:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 23:20:07 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_game	*game;

	hd_alloc_set_error_func(hd_alloc_error_func_d);
	if (!ft_check_args(argc, argv))
		return (1);
	ft_printf("Arguments are valid\n");
	game = ft_loading_game(argv[1]);
	game->env = env;
	game->show_menu = 1;
	ft_init_timer(game);
	mlx_loop(game->mlx);
	return (0);
}
