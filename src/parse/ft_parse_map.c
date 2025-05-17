#include "../../includes/cub_3d.h"

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
	return (0);
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

int	ft_end_column_map(t_file *map_file, const int *height_start_end)
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

void	ft_parse_map(t_game *game, t_file *map_file)
{
	int height_start_end[2];
	int width_start_end[2];

	height_start_end[0] = ft_start_line_map(map_file);
	height_start_end[1] = ft_end_line_map(map_file, height_start_end[0]);
	game->width_height[1] = height_start_end[1] - height_start_end[0] + 1;
	width_start_end[0] = ft_start_column_map(map_file, height_start_end);
	width_start_end[1] = ft_end_column_map(map_file, height_start_end);
	game->width_height[0] = width_start_end[1] - width_start_end[0] + 1;
	if (game->width_height[0] < 3 || game->width_height[1] < 3)
	{
		ft_dprintf(2, "%sError: Failed to load map: it's small\n%s", RED, RESET);
		ft_close_game(1);
	}
	ft_create_game_map(game, map_file, height_start_end, width_start_end);
	ft_check_map(game);
}