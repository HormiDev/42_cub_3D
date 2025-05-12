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

int	ft_start_line_map(t_file *map_file)
{
	int i;
	int j;

	i = ft_get_map_start_index(map_file);
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
	ft_dprintf(2, "%sError: Failed to load map: start not found\n%s", RED, RESET);
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

int	ft_start_column_map(t_file *map_file, const int *height_start_end)
{
	int i;
	int j;
	int	start_column;

	i = height_start_end[0];
	start_column = INT_MAX;
	while (i <= height_start_end[1])
	{
		j = 0;
		while (map_file->array_content[i][j])
		{
			if (map_file->array_content[i][j] != ' ' 
				&& map_file->array_content[i][j] != '\n')
				if (j < start_column)
					start_column = j;
			j++;
		}
		i++;
	}
	return (start_column);
}


int	ft_end_column_map(t_file *map_file, const int *height_start_end, int start_column)
{
	int i;
	int j;
	int end_column;

	end_column = 0;
	i = height_start_end[0];
	while (i <= height_start_end[1])
	{
		j = ft_strlen(map_file->array_content[i]) - 1;
		while (j >= 0)
		{
			if (map_file->array_content[i][j] != ' ' 
				&& map_file->array_content[i][j] != '\n')
			{
				if (j > end_column)
					end_column = j;
				break ;
			}	
			j--;
		}
		i++;
	}
	return (end_column);
}

void	ft_create_game_map(t_game *game, t_file *map_file, const int *height_start_end, const int *width_start_end)
{
	int i;
	int j;

	game->map = ft_alloc_lst(sizeof(char *) * (game->width_height[1] + 1), 4);
	i = 0;
	while (i < game->width_height[1])
	{
		game->map[i] = ft_alloc_lst(sizeof(char) * (game->width_height[0] + 1), 4);
		ft_strncpy(game->map[i], &(map_file->array_content)[height_start_end[0] + i][width_start_end[0]], game->width_height[0]);
		j = 0;
		while (j < game->width_height[0])
		{
			if (game->map[i][j] == '\n')
				game->map[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	ft_check_map_valid_characters(char **map)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'N' 
				&& map[i][j] != 'S' && map[i][j] != 'E' && map[i][j] != 'W'
				&& map[i][j] != ' ')
			{
				ft_dprintf(2, "%sError: %c Invalid character in map\n%s", RED, map[i][j], RESET);
				ft_close_game(1);
			}
			j++;
		}
		i++;
	}
}

int	ft_check_map_count_player(t_game *game)
{
	int i;
	int j;
	int player_count;

	i = 0;
	player_count = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' 
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	return (player_count);
}

void	ft_check_map(t_game *game)
{
	int player_count;

	ft_check_map_valid_characters(game->map);
	player_count = ft_check_map_count_player(game);
	if (player_count != 1)
	{
		if (player_count < 1)
			ft_dprintf(2, "%sError: No player found in map%s", RED, RESET);
		else
		{
			ft_dprintf(2, "%sError: More than one player found in map\n", RED);
			ft_dprintf(2, RESET);
		}
		ft_close_game(1);
	}
	
	if(!ft_check_map_closed(game))
	{
		ft_dprintf(2, RED "Error: Map is not closed\n" RESET);
		ft_close_game(1);
	}	
}

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
	ft_debug_game(game); 
	ft_file_clear(&map_file);
	ft_printf("Map loaded successfully\n");
	return (game);
}
