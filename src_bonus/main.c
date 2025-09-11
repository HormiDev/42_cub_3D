/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:54:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/09/11 17:29:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"


int main(int argc, char **argv)
{
	t_game	*game;

	if (!ft_check_args(argc, argv))
		return (1);
	ft_printf("Arguments are valid\n");
	game = ft_loading_game(argv[1]);
	mlx_loop(game->mlx);
	return (0);
}
