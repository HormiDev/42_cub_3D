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

void	ft_rotate_map_y(t_game *game)
{
	char	*tmp;
	int		start;
	int		end;

	start = 0;
	end = game->width_height[1] - 1;
	while (start < end)
	{
		tmp = game->map[start];
		game->map[start] = game->map[end];
		game->map[end] = tmp;
		start++;
		end--;
	}
}
