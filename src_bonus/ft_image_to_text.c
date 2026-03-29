#include "../includes/cub_3d_bonus.h"

static void	ft_font_process_line(t_texture *dst, t_texture *src,
		int src_x, int dst_x, int dst_y, int src_y)
{
	unsigned int	*src_ptr;
	unsigned int	*dst_ptr;
	unsigned int	src_color;
	int				alpha;
	int				x;

	src_ptr = (unsigned int *)(src->img->data + src_y * src->img->size_line);
	dst_ptr = (unsigned int *)(dst->img->data + dst_y * dst->img->size_line);
	x = 0;
	while (x < 5)
	{
		src_color = src_ptr[src_x + x];
		if (src_color != 0x00000000)
		{
			alpha = (src_color >> 24) & 0xFF;
			if (alpha == 0)
				alpha = 255;
			if (alpha == 255)
				dst_ptr[dst_x + x] = src_color;
			else
				ft_mix_color_alpha(&dst_ptr[dst_x + x], &src_color, alpha);
		}
		x++;
	}
}

static void	ft_draw_char(t_texture *dst, t_texture *font,
				int idx, int dst_x, int dst_y)
{
	int	src_x;
	int	y;

	if (idx < 0 || dst_x >= dst->width || dst_y >= dst->height)
	    return ;
	if (dst_x + 5 < 0 || dst_y + font->height < 0)
	    return ;
	src_x = 1 + idx * 6;
	y = 0;
	while (y < font->height)
	{
		if (dst_y + y >= 0 && dst_y + y < dst->height)
			ft_font_process_line(dst, font, src_x, dst_x, dst_y + y, y);
		y++;
	}
}

static int	ft_char_to_index(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a');
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= '0' && c <= '9')
		return (26 + (c - '0'));
	return (-1);
}

void	ft_draw_string_hud(t_texture *dst, t_texture *font,
			const char *str, int x, int y)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			ft_draw_char(dst, font, ft_char_to_index(str[i]), x, y);
		x += 6;
		i++;
	}
}