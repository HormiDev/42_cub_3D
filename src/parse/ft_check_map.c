#include "../../includes/cub_3d.h"

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