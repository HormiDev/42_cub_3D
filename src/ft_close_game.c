/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:25:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/17 01:43:50 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void	ft_close_game(int exit_code)
{
	ft_alloc_clear();
	exit(exit_code);
}

int	ft_close_game_for_mlx(void)
{
	ft_alloc_clear();
	exit(0);
}