#include "../../includes/cub_3d_bonus.h"

int	ft_is_wall_or_closed_door(t_game *game, int x, int y)
{
	t_door	*door;

	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'D')
	{
		door = ft_get_door_at(game, x, y);
		if (door && ft_get_door_height(door) > 0.0)
			return (1);
	}
	return (0);
}
