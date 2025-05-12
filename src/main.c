/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:54:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/12 00:55:52 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"



int main(int argc, char **argv)
{
	t_game	*game;

	if (!ft_check_args(argc, argv))
		return (1);
	ft_printf("Arguments are valid\n");
	
	game = ft_loading_game(argv[1]);
	ft_configure_mlx(game);
	return (0);
}
