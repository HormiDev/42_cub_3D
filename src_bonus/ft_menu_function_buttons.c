/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_function_buttons.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:54:21 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 03:03:51 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_decrease_timer(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (game->config.duration_index > 0)
		game->config.duration_index--;
}

void	ft_increase_timer(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (game->config.duration_index >= game->durations_size - 1)
		return ;
	game->config.duration_index++;
}
