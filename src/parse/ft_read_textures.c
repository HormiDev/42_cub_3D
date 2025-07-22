#include "../../includes/cub_3d.h"

unsigned int parse_color_hex(const char *str)
{
	unsigned int color = 0;
	if (str[0] == '#')
		sscanf(str + 1, "%x", &color);
	return color;
}
int	parse_xpm_header(char *line, int *w, int *h, int *n_colors, int *cpp)
{
	char	*end = ft_strrchr(line, '"');
	if (end)
		*end = '\0';
	if (sscanf(line, "%d %d %d %d", w, h, n_colors, cpp) != 4 || *cpp != 1)
		return (-1);
	return (0);
}
int	parse_xpm_colors(char **lines, int *i, int n_colors, unsigned int *colors, char *symbols)
{
	int		color_idx = 0;
	char	*line;
	char	*end;
	char	sym;
	char	hexcode[16];

	while (color_idx < n_colors && lines[*i])
	{
		line = ft_strchr(lines[*i], '"') + 1;
		end = ft_strrchr(line, '"');
		if (end)
			*end = '\0';
		if (sscanf(line, "%c c #%s", &sym, hexcode) != 2)
			return (-1);
		symbols[(unsigned char)sym] = color_idx;
		colors[color_idx] = parse_color_hex(hexcode);
		(*i)++;
		color_idx++;
	}
	return (0);
}

int	parse_xpm_pixels(char **lines, int *i, int w, int h, int **pixels, char *symbols)
{
	int		y = 0, x;
	char	*line;
	char	*end;

	while (y < h && lines[*i])
	{
		line = ft_strchr(lines[*i], '"') + 1;
		end = ft_strrchr(line, '"');
		if (end)
			*end = '\0';
		pixels[y] = ft_alloc_lst(sizeof(int) * w, 4);
		if (!pixels[y])
			return (-1);
		x = 0;
		while (x < w)
		{
			pixels[y][x] = symbols[(unsigned char)line[x]];
			x++;
		}
		y++;
		(*i)++;
	}
	return (0);
}

int	parse_xpm_file_header_and_alloc(const char **lines, int *i, t_texture *tex, char *symbols)
{
	(void)symbols; //para futuro 
	int	w, h, n_colors, cpp;

	while (lines[*i] && lines[*i][0] != '"')
		(*i)++;
	if (!lines[*i] || lines[*i][0] != '"')
		return (-1);
	if (parse_xpm_header(ft_strchr(lines[*i], '"') + 1, &w, &h, &n_colors, &cpp) < 0)
		return (-1);

	tex->width = w;
	tex->height = h;
	tex->size_colors = n_colors;
	tex->colors = ft_alloc_lst(sizeof(unsigned int) * n_colors, 4);
	tex->pixels = ft_alloc_lst(sizeof(int *) * h, 4);
	if (!tex->colors || !tex->pixels)
		return (-1);
	return 0;
}

