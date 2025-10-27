#include "../../includes/cub_3d_bonus.h"

static void	ft_draw_line_minimap(t_game *game, t_vector2 p1,
	t_vector2 p2, int color)
{
	t_vector2		delta;
	t_vector2		current;
	t_vector_int	abs_delta;
	int				steps;
	int				i;

	delta.x = p2.x - p1.x;
	delta.y = p2.y - p1.y;
	abs_delta.x = (int)delta.x;
	abs_delta.y = (int)delta.y;
	ft_vector_int_abs(&abs_delta);
	steps = ft_vector_int_max(abs_delta);
	delta.x /= steps;
	delta.y /= steps;
	current = p1;
	i = 0;
	while (i <= steps)
	{
		if (current.x >= 0 && current.x < WINDOW_WIDTH
			&& current.y >= 0 && current.y < WINDOW_HEIGHT)
			ft_draw_pixel_in_img(game->render->img,
				(int)current.x, (int)current.y, color);
		current.x += delta.x;
		current.y += delta.y;
		i++;
	}
}

static int	ft_get_angle_idx(double rotation)
{
	int		angle_idx;

	angle_idx = (int)(rotation * 100.0);
	while (angle_idx >= 36000)
		angle_idx -= 36000;
	while (angle_idx < 0)
		angle_idx += 36000;
	return (angle_idx);
}

static t_vector2	ft_world_corner_to_screen(t_game *game, double wx, double wy)
{
	t_vector2	relative;
	t_vector2	screen;
	int			angle_idx;
	double		cos_a;
	double		sin_a;

	relative.x = wx - game->player.position.x;
	relative.y = wy - game->player.position.y;
	angle_idx = ft_get_angle_idx(game->player.rotation.x);
	cos_a = ft_cos(angle_idx / 100.0);
	sin_a = ft_sin(angle_idx / 100.0);
	screen.x = MINIMAP_OFFSET_X + 100 + (relative.x * cos_a - relative.y
			* sin_a) * MINIMAP_TILE_SIZE;
	screen.y = MINIMAP_OFFSET_Y + 100 + (relative.x * sin_a + relative.y
			* cos_a) * MINIMAP_TILE_SIZE;
	return (screen);
}

static int	ft_get_tile_color(char tile_char)
{
	if (tile_char == '1')
		return (C_ALIEN_GREEN);
	else if (tile_char == '0')
		return (C_ALIEN_DARK);
	return (C_BLACK);
}

static void	ft_draw_tile_edges(t_game *game, int mx, int my, int color)
{
	t_vector2	corners[4];

	corners[0] = ft_world_corner_to_screen(game, mx, my);
	corners[1] = ft_world_corner_to_screen(game, mx + 1, my);
	corners[2] = ft_world_corner_to_screen(game, mx + 1, my + 1);
	corners[3] = ft_world_corner_to_screen(game, mx, my + 1);
	ft_draw_line_minimap(game, corners[0], corners[1], color);
	ft_draw_line_minimap(game, corners[1], corners[2], color);
	ft_draw_line_minimap(game, corners[2], corners[3], color);
	ft_draw_line_minimap(game, corners[3], corners[0], color);
}

static void	ft_draw_minimap_tile(t_game *game, int mx, int my)
{
	int	color;

	color = ft_get_tile_color(game->map[my][mx]);
	if (game->map[my][mx] == '1')
		ft_draw_tile_edges(game, mx, my, color);
}

static void	ft_draw_minimap_row(t_game *game, int my)
{
	int	mx;
	int	visible_range;

	visible_range = 10;
	mx = (int)game->player.position.x - visible_range;
	while (mx <= (int)game->player.position.x + visible_range)
	{
		if (mx >= 0 && mx < game->width_height[0]
			&& my >= 0 && my < game->width_height[1])
			ft_draw_minimap_tile(game, mx, my);
		mx++;
	}
}

static void	ft_draw_player_indicator(t_game *game)
{
	t_vector_int	p;
	t_vector_int	d;
	t_vector_int	center;

	center.x = MINIMAP_OFFSET_X + 100;
	center.y = MINIMAP_OFFSET_Y + 100;
	p.y = center.y - 4;
	while (p.y <= center.y + 4)
	{
		p.x = center.x - 4;
		while (p.x <= center.x + 4)
		{
			d.x = p.x - center.x;
			d.y = p.y - center.y;
			if (d.x * d.x + d.y * d.y <= 16)
				ft_draw_pixel_in_img(game->render->img, p.x, p.y,
					C_ALIEN_PLAYER);
			p.x++;
		}
		p.y++;
	}
}

static void	ft_draw_minimap_background(t_game *game)
{
	t_vector_int	p;

	p.y = MINIMAP_OFFSET_Y;
	while (p.y < MINIMAP_OFFSET_Y + 200)
	{
		p.x = MINIMAP_OFFSET_X;
		while (p.x < MINIMAP_OFFSET_X + 200)
		{
			if (p.x >= 0 && p.x < WINDOW_WIDTH && p.y >= 0
				&& p.y < WINDOW_HEIGHT)
				ft_draw_pixel_in_img(game->render->img, p.x, p.y,
					C_ALIEN_DARK);
			p.x++;
		}
		p.y++;
	}
}

static void	ft_draw_minimap_border(t_game *game)
{
	t_vector_int	offset;
	t_vector_int	end;
	int				i;

	i = 0;
	offset.x = MINIMAP_OFFSET_X;
	offset.y = MINIMAP_OFFSET_Y;
	end.x = MINIMAP_OFFSET_X + 200;
	end.y = MINIMAP_OFFSET_Y + 200;
	while (i < 200)
	{
		if (i < 2 || i > 198)
		{
			ft_draw_pixel_in_img(game->render->img, offset.x + i,
				offset.y, C_ALIEN_GRID);
			ft_draw_pixel_in_img(game->render->img, offset.x + i,
				end.y - 1, C_ALIEN_GRID);
		}
		if (i < 2 || i > 198)
		{
			ft_draw_pixel_in_img(game->render->img, offset.x,
				offset.y + i, C_ALIEN_GRID);
			ft_draw_pixel_in_img(game->render->img, end.x - 1,
				offset.y + i, C_ALIEN_GRID);
		}
		i++;
	}
}

void	ft_map2D(t_game *game)
{
	int	my;
	int	visible_range;

	ft_draw_minimap_background(game);
	visible_range = 10;
	my = (int)game->player.position.y - visible_range;
	while (my <= (int)game->player.position.y + visible_range)
	{
		if (my >= 0 && my < game->width_height[1])
			ft_draw_minimap_row(game, my);
		my++;
	}
	ft_draw_minimap_border(game);
	ft_draw_player_indicator(game);
}

