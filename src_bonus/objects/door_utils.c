#include "../../includes/cub_3d_bonus.h"

int	ft_is_door(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->width_height[0])
		return (0);
	if (y < 0 || y >= game->width_height[1])
		return (0);
	return (game->map[y][x] == 'D');
}

t_door	*ft_get_door_at(t_game *game, int x, int y)
{
	t_list	*current;
	t_door	*door;

	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		if (door->position.x == x && door->position.y == y)
			return (door);
		current = current->next;
	}
	return (NULL);
}

double	ft_get_door_height(t_door *door)
{
	if (!door)
		return (1.0);
	if (door->state == DOOR_OPEN)
		return (0.0);
	if (door->state == DOOR_CLOSED)
		return (1.0);
	return (1.0 - door->animation_progress);
}

static double	ft_distance_to_door(t_vector2 pos, t_door *door)
{
	double	dx;
	double	dy;

	dx = pos.x - (door->position.x + 0.5);
	dy = pos.y - (door->position.y + 0.5);
	return (ft_sqrt(dx * dx + dy * dy));
}

static void	ft_trigger_door(t_door *door, double distance)
{
	if (distance < door->trigger_distance)
	{
		if (door->state == DOOR_CLOSED)
			door->state = DOOR_OPENING;
		else if (door->state == DOOR_CLOSING)
			door->state = DOOR_OPENING;
	}
	else
	{
		if (door->state == DOOR_OPEN)
			door->state = DOOR_CLOSING;
		else if (door->state == DOOR_OPENING)
			door->state = DOOR_CLOSING;
	}
}

void	ft_check_door_triggers(t_game *game)
{
	t_list	*current;
	t_door	*door;
	double	distance;

	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		distance = ft_distance_to_door(game->player.position, door);
		ft_trigger_door(door, distance);
		current = current->next;
	}
}
