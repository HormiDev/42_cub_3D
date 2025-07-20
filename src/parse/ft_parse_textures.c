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
	FILE	*fp;
	char	buffer[1024];
	char	*line, *end;
	int		w, h, n_colors, cpp;
	int		i = 0, x = 0, y = 0;

	fp = fopen(path, "r");
	if (!fp)
		return (-1);

	while (fgets(buffer, sizeof(buffer), fp)) {
		if (buffer[0] == '"')
			break;
	}
	if (buffer[0] != '"')
		return (fclose(fp), -1);

	line = strchr(buffer, '"') + 1;
	end = strrchr(line, '"');
	if (end)
		*end = '\0';
	if (sscanf(line, "%d %d %d %d", &w, &h, &n_colors, &cpp) != 4 || cpp != 1)
		return (fclose(fp), -1);

	tex->width = w;
	tex->height = h;
	tex->size_colors = n_colors;
	tex->colors = malloc(sizeof(unsigned int) * n_colors);
	tex->pixels = malloc(sizeof(int *) * h);
	if (!tex->colors || !tex->pixels)
		return (fclose(fp), -1);

	char symbols[256] = {0};
	i = 0;
	while (i < n_colors)
	{
		if (!fgets(buffer, sizeof(buffer), fp))
			return (fclose(fp), -1);
		line = strchr(buffer, '"') + 1;
		end = strrchr(line, '"');
		if (end)
			*end = '\0';

		char sym;
		char hexcode[16];
		if (sscanf(line, "%c c #%s", &sym, hexcode) != 2)
			return (fclose(fp), -1);
		symbols[(unsigned char)sym] = i;
		tex->colors[i] = parse_color_hex(hexcode);
		i++;
	}

	y = 0;
	while (y < h)
	{
		if (!fgets(buffer, sizeof(buffer), fp))
			return (fclose(fp), -1);
		line = strchr(buffer, '"') + 1;
		end = strrchr(line, '"');
		if (end)
			*end = '\0';

		tex->pixels[y] = malloc(sizeof(int) * w);
		if (!tex->pixels[y])
			return (fclose(fp), -1);
		x = 0;
		while (x < w)
		{
			tex->pixels[y][x] = symbols[(unsigned char)line[x]];
			x++;
		}
		y++;
	}
	fclose(fp);
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