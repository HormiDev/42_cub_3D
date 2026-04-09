/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:54:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/09 18:24:36 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_game				*game;
	t_audio_manager		*audio_manager;

	hd_alloc_set_error_func(hd_alloc_error_func_d);
	audio_manager = init_audio_manager(env);
	if (!ft_check_args(argc, argv))
		return (1);
	ft_printf("Arguments are valid\n");
	game = ft_loading_game(argv[1]);
	game->env = env;
	game->audio_manager = audio_manager;
	game->show_menu = 1;
	ft_init_timer(game);
	audio_manager_send(game->audio_manager, "music&sounds/menu.wav");
	mlx_loop(game->mlx);
	return (0);
}
