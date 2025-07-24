#include "../../includes/cub_3d.h"

int ft_int_diff(int a, int b) // llevar a la libft
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int ft_int_max(int a, int b) // llevar a la libft
{
	if (a > b)
		return a;
	return b;
}

void ft_draw_line_in_image(t_game *game, t_vector2 start, t_vector2 end, int color)
{
	t_vector2 pixel;
	int steps;
	int i;
	t_vector2 increment;

	steps = ft_int_max(ft_int_diff(start.x, end.x), ft_int_diff(start.y, end.y));
	i = 0;
	pixel.x = start.x;
	pixel.y = start.y;
	increment.x = (start.x - end.x) / steps;
	increment.y = (start.y - end.y) / steps;
	while (i <= steps)
	{
		ft_draw_pixel_in_img(game, (int)pixel.x, (int)pixel.y, color);
		pixel.x -= increment.x;
		pixel.y -= increment.y;
		i++;
	}
}

double ft_double_diff(double a, double b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

double ft_vector_distance(t_vector2 a, t_vector2 b)
{
	t_vector2 diff;

	diff.x = ft_double_diff(a.x, b.x);
	diff.y = ft_double_diff(a.y, b.y);
	return ft_sqrt(pow(diff.x, 2) + pow(diff.y, 2));
}