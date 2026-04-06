/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_function_buttons.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 17:54:21 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 03:03:13 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_increase_players(void *game_ptr)
{
	t_game *game;

	game = (t_game *)game_ptr;
	if (game->config.n_players < 4)
		game->config.n_players++;
}

void	ft_decrease_players(void *game_ptr)
{
	t_game *game;

	game = (t_game *)game_ptr;
	if (game->config.n_players > 1)
		game->config.n_players--;
}

void	ft_decrease_charges(void *game_ptr)
{
	t_game *game;

	game = (t_game *)game_ptr;
	if (game->config.charges > 1)
		game->config.charges--;
}

void	ft_increase_charges(void *game_ptr)
{
	t_game *game;

	game = (t_game *)game_ptr;
	if (game->config.charges < 10)
		game->config.charges++;
}

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
	if (game->config.duration_index >= game->durations_size -1)
		return ;
	game->config.duration_index++;
}