#include "../../includes/cub_3d.h"

static unsigned int parse_color_hex(const char *str)
{
	unsigned int color = 0;
	if (str[0] == '#')
		sscanf(str + 1, "%x", &color);
	return color;
}
int	extract_texture_from_xpm(const char *path, t_texture *tex)
{
	t_file	*file;
	char	**lines;
	char	*line, *end;
	int		w, h, n_colors, cpp;
	int		i = 0, x = 0, y = 0;
	char	symbols[256] = {0};

	file = ft_create_file_from_filename((char *)path);
	if (!file || !file->array_content)
		return (-1);
	lines = file->array_content;

	while (lines[i])
	{
		if (lines[i][0] == '"')
			break;
		i++;
	}
	if (!lines[i] || lines[i][0] != '"')
		return (ft_file_clear(&file), -1);

	line = ft_strchr(lines[i], '"') + 1;
	end = ft_strrchr(line, '"');
	if (end)
		*end = '\0';
	if (sscanf(line, "%d %d %d %d", &w, &h, &n_colors, &cpp) != 4 || cpp != 1)
		return (ft_file_clear(&file), -1);

	tex->width = w;
	tex->height = h;
	tex->size_colors = n_colors;
	tex->colors = ft_alloc_lst(sizeof(unsigned int) * n_colors, 4);
	tex->pixels = ft_alloc_lst(sizeof(int *) * h, 4);
	if (!tex->colors || !tex->pixels)
		return (ft_file_clear(&file), -1);

	i++; // Pasamos a las líneas de colores
	int color_idx = 0;
	while (color_idx < n_colors && lines[i])
	{
		line = ft_strchr(lines[i], '"') + 1;
		end = ft_strrchr(line, '"');
		if (end)
			*end = '\0';

		char sym;
		char hexcode[16];
		if (sscanf(line, "%c c #%s", &sym, hexcode) != 2)
			return (ft_file_clear(&file), -1);
		symbols[(unsigned char)sym] = color_idx;
		tex->colors[color_idx] = parse_color_hex(hexcode);
		i++;
		color_idx++;
	}

	y = 0;
	while (y < h && lines[i])
	{
		line = ft_strchr(lines[i], '"') + 1;
		end = ft_strrchr(line, '"');
		if (end)
			*end = '\0';

		tex->pixels[y] = ft_alloc_lst(sizeof(int) * w, 4);
		if (!tex->pixels[y])
			return (ft_file_clear(&file), -1);
		x = 0;
		while (x < w)
		{
			tex->pixels[y][x] = symbols[(unsigned char)line[x]];
			x++;
		}
		y++;
		i++;
	}

	ft_file_clear(&file);
	return (0);
}

int	ft_parse_single_texture(t_game *game, char *line, int texture_index)
{
	char		*path;
	t_texture	*tex;

	path = ft_add_to_alloc_lst_e(ft_strtrim(line + 3, " \t\n"));
	if (!path)
	{
		ft_dprintf(2, RED "Error: parsing texture path.\n" RESET);
		return (0);
	}
	tex = ft_alloc_lst(sizeof(t_texture), 4);
	if (!tex)
		return (0);
	tex->path = path;
	tex->width = 0;
	tex->height = 0;
	tex->size_colors = 0;
	tex->pixels = NULL;
	tex->colors = NULL;
	if (extract_texture_from_xpm(path, tex) < 0)
	{
		ft_dprintf(2, RED "Error: loading texture '%s'\n" RESET, path);
		return (0);
	}
	ft_lstadd_back(&game->textures[texture_index], ft_lstnew_a(tex));
	return (1);
}


void	ft_parse_textures(t_game *game, t_file *map_file)
{
	int	i;

	i = 0;
	while (map_file->array_content[i])
	{
		if (ft_strncmp_p(map_file->array_content[i], "NO ", 3) == 0)
			ft_parse_single_texture(game, map_file->array_content[i], WALL_NO);
		else if (ft_strncmp_p(map_file->array_content[i], "SO ", 3) == 0)
			ft_parse_single_texture(game, map_file->array_content[i], WALL_SO);
		else if (ft_strncmp_p(map_file->array_content[i], "WE ", 3) == 0)
			ft_parse_single_texture(game, map_file->array_content[i], WALL_EA);
		else if (ft_strncmp_p(map_file->array_content[i], "EA ", 3) == 0)
			ft_parse_single_texture(game, map_file->array_content[i], WALL_WE);
		i++;
		//BONUS: añadir cielo y techo de chill
	}
}