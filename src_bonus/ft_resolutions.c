/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_resolutions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 01:16:45 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/12/17 02:56:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void ft_next_resolution(t_game *game)// debug function
{
	game->resolution_index++;
	if (game->resolution_index >= game->resolutions_size)
		game->resolution_index = 0;
	ft_loading_render(game, game->resolutions[game->resolution_index].height, game->resolutions[game->resolution_index].width);
}

void ft_init_resolutions(t_game *game)
{
	game->resolutions_size = 10;
	game->resolutions = ft_alloc_lst(sizeof(t_resolution) * game->resolutions_size, 4);
	game->resolutions[0].width = 160;
	game->resolutions[0].height = 90;
	game->resolutions[1].width = 240;
	game->resolutions[1].height = 135;
	game->resolutions[2].width = 320;
	game->resolutions[2].height = 180;
	game->resolutions[3].width = 480;
	game->resolutions[3].height = 270;
	game->resolutions[4].width = 640;
	game->resolutions[4].height = 360;
	game->resolutions[5].width = 960;
	game->resolutions[5].height = 540;
	game->resolutions[6].width = 1280;
	game->resolutions[6].height = 720;
	game->resolutions[7].width = 1920;
	game->resolutions[7].height = 1080;
	game->resolutions[8].width = 2560;
	game->resolutions[8].height = 1440;
	game->resolutions[9].width = 3840;
	game->resolutions[9].height = 2160;
}
