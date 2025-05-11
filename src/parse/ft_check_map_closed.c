#include  "../../includes/cub_3d.h"

int ft_check_up_down(t_game *game)
{
    int i;

	i = 0;
	while (game->map[0][i])
	{
		if (game->map[0][i] != '1' && game->map[0][i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (game->map[game->width_height[1] - 1][i])
	{
		if (game->map[game->width_height[1] - 1][i] != '1' 
			&& game->map[game->width_height[1] - 1][i] != ' ')
			return (0);
		i++;
	}
    return (1); 
}

int ft_check_borders(char **map)
{
    int i;
    int len; 
    int j; 
    int last;

    i = 0; 
    while (map[i])
    {
        len = ft_strlen_p(map[i]);
        j = 0; 

        while(map[i][j] == ' ')
            j++; 
        if(map[i][j] != '1')
            return(0);
        last = len - 1;
        while (last > 0 && map[i][last] == ' ')
            last--;
        if (map[i][last] != '1')
            return (0);
        i++;
    }
    return (1); 
}

int	ft_check_map_closed_in(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (i != 0 && map[i - 1][j] != '1' && map[i - 1][j] != ' ')
					return (0);
				if (map[i + 1] != 0 && map[i + 1][j] != '1' && map[i + 1][j] != ' ')
					return (0);
				if (j != 0 && map[i][j - 1] != '1' && map[i][j - 1] != ' ')
					return (0);
				if (map[i][j + 1] != 0 && map[i][j + 1] != '1' && map[i][j + 1] != ' ')
					return (0);
			}	
			j++;
		}	
		i++;
	}
	return (1);
}

int ft_check_map_closed(t_game *game)
{
    if(!ft_check_up_down(game))
        return (0);
    if(!ft_check_borders(game->map))
        return (0);
    if(!ft_check_map_closed_in(game->map))
        return (0);
    return (1); 
}

