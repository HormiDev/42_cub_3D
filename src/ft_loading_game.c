/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:17:36 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/08 01:54:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

int	ft_start_line_map(t_file *map_file)
{
	int i;
	int j;

	i = 6;
	while (map_file->array_content[i])
	{
		j = 0;
		while (map_file->array_content[i][j])
		{
			if (map_file->array_content[i][j] != ' ' 
				&& map_file->array_content[i][j] != '\n')
				return (i);
			j++;
		}
		i++;
	}
	ft_dprintf(2, "%sError: Failed to load map: start not found%s", RED, RESET);
	ft_close_game(1);
}

int	ft_end_line_map(t_file *map_file, int start_line)
{
	int j;
	int last_line;

	last_line = start_line;
	while (map_file->array_content[start_line])
	{
		j = 0;
		while (map_file->array_content[start_line][j])
		{
			if (map_file->array_content[start_line][j] != ' ' 
				&& map_file->array_content[start_line][j] != '\n')
				last_line = start_line;
			j++;
		}
		start_line++;
	}
	return (last_line);
}

int	ft_start_column_map(t_file *map_file, const int *height_start_end)//corregir
{
	int i;
	int j;

	j = height_start_end[0];
	while (map_file->array_content[i])
	{
		i = 0;
		while (map_file->array_content[j][i])
		{
			if (map_file->array_content[j][i] != ' ' 
				&& map_file->array_content[j][i] != '\n')
				return (i);
			i++;
		}
		j++;
	}
	ft_dprintf(2, "%sError: Failed to load map: start not found%s", RED, RESET);
	ft_close_game(1);
}

int	ft_end_column_map(t_file *map_file, const int *height_start_end, int start_column)//corregir
{
	int j;
	int last_column;

	last_column = start_column;
	while (map_file->array_content[height_start_end[1]])
	{
		j = 0;
		while (map_file->array_content[height_start_end[1]][j])
		{
			if (ma
	}
	return (last_column);
}

void	ft_parse_map(t_game *game, t_file *map_file)
{
	int height_start_end[2];
	int width_start_end[2];

	height_start_end[0] = ft_start_line_map(map_file);
	height_start_end[1] = ft_end_line_map(map_file, height_start_end[0]);
	game->width_height[0] = height_start_end[1] - height_start_end[0] + 1;
	width_start_end[0] = ft_start_column_map(map_file, height_start_end);
	width_start_end[1] = ft_end_column_map(map_file, height_start_end, width_start_end[0]);
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
	//ft_parse_map(game, map_file);
}
