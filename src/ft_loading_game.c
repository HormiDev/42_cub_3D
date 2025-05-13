/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:17:36 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/09 01:36:556 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void	ft_parse_map(t_game *game, t_file *map_file)
{
	int height_start_end[2];
	int width_start_end[2];

	height_start_end[0] = ft_start_line_map(map_file);
	height_start_end[1] = ft_end_line_map(map_file, height_start_end[0]);
	game->width_height[1] = height_start_end[1] - height_start_end[0] + 1;
	width_start_end[0] = ft_start_column_map(map_file, height_start_end);
	width_start_end[1] = ft_end_column_map(map_file, height_start_end, width_start_end[0]);
	game->width_height[0] = width_start_end[1] - width_start_end[0] + 1;
	if (game->width_height[0] < 3 || game->width_height[1] < 3)
	{
		ft_dprintf(2, "%sError: Failed to load map: it's small\n%s", RED, RESET);
		ft_close_game(1);
	}
	ft_create_game_map(game, map_file, height_start_end, width_start_end);
	ft_check_map(game);
}

t_game	*ft_loading_game(char *path_map)
{
	t_game *game;
	t_file *map_file;
    
    game = ft_alloc_lst(sizeof(t_game), 4);
	map_file = ft_create_file_from_filename(path_map);//revisar si esta protegida e integrar en ft alloc
	if (!map_file)
	{
		ft_dprintf(2, "Error\n");
		return (0);
	}
	//ft_file_print(map_file);
	ft_parse_textures(game, map_file);
    ft_parse_colors(game, map_file); 
	ft_parse_map(game, map_file);
	ft_config_player(game);
	ft_debug_game(game);
	ft_file_clear(&map_file);
	ft_printf("Map loaded successfully\n");
	return (game);
}
