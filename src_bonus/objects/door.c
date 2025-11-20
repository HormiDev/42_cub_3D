#include "../../includes/cub_3d_bonus.h"

static t_door	*ft_create_door(int x, int y)
{
	t_door	*door;

	door = ft_alloc_lst(sizeof(t_door), 4);
	if (!door)
		return (NULL);
	door->position.x = x;
	door->position.y = y;
	door->state = DOOR_CLOSED;
	door->animation_progress = 0.0;
	door->trigger_distance = 2.5;
	door->texture_index = 0;
	return (door);
}
void	ft_free_doors(t_game *game)
{
	if (game->doors)
		game->doors = NULL;
}

void	ft_init_doors(t_game *game)
{
	int		y;
	int		x;
	t_door	*door;

	game->doors = NULL;
	y = -1;
	while (++y < game->width_height[1])
	{
		x = -1;
		while (++x < game->width_height[0])
		{
			if (game->map[y][x] == 'D')
			{
				door = ft_create_door(x, y);
				if (!door)
					ft_close_game(1);
				ft_lstadd_back(&game->doors, ft_lstnew(door));
			}
		}
	}
}

void	ft_animate_door(t_door *door, double delta_time)
{
	if (door->state == DOOR_OPENING)
	{
		door->animation_progress += delta_time * 2.0;
		if (door->animation_progress >= 1.0)
		{
			door->animation_progress = 1.0;
			door->state = DOOR_OPEN;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->animation_progress -= delta_time * 2.0;
		if (door->animation_progress <= 0.0)
		{
			door->animation_progress = 0.0;
			door->state = DOOR_CLOSED;
		}
	}
}

void	ft_update_doors(t_game *game)
{
	t_list	*current;
	t_door	*door;

	ft_check_door_triggers(game);
	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		ft_animate_door(door, game->delta_time);
		current = current->next;
	}
}
