#include "../../includes/cub_3d_bonus.h"

static void	ft_alloc_game_map(t_game *game)
{
	int	rows;
	int	cols;
	int	i;

	rows = game->width_height[1];
	cols = game->width_height[0];
	game->map = hd_calloc(rows + 1, sizeof(char *));
	i = 0;
	while (i < rows)
	{
		game->map[i] = hd_calloc(cols + 1, sizeof(char));
		i++;
	}
	game->map[rows] = NULL;
}

static void	ft_fill_game_map(t_game *game, t_file *map_file, const int *height_start_end, const int *width_start_end)
{
	int	i;
	int	j;
	int	rows;
	int	cols;

	rows = game->width_height[1];
	cols = game->width_height[0];
	i = 0;
	while (i < rows)
	{
		ft_strncpy(game->map[i], &(map_file->array_content)[height_start_end[0] + i][width_start_end[0]], cols);
		j = 0;
		while (j < cols)
		{
			if (game->map[i][j] == '\n')
				game->map[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	ft_create_map_transitable(t_game *game, t_file *map_file, const int *height_start_end, const int *width_start_end)
{
	ft_alloc_game_map(game);
	ft_fill_game_map(game, map_file, height_start_end, width_start_end);
}

