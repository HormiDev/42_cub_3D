#include "../../includes/cub_3d.h"

int	extract_texture_from_xpm(const char *path, t_texture *tex)
{
	t_file	*file;
	char	**lines;
	int		i = 0;
	char	symbols[256] = {0};

	file = ft_create_file_from_filename((char *)path);
	if (!file || !file->array_content)
		return (-1);
	lines = file->array_content;
	if (parse_xpm_file_header_and_alloc((const char **)lines, &i, tex, symbols) < 0)
		return (ft_file_clear(&file), -1);
	i++;
	if (parse_xpm_colors(lines, &i, tex->size_colors, tex->colors, symbols) < 0)
		return (ft_file_clear(&file), -1);
	if (parse_xpm_pixels(lines, &i, tex->width, tex->height, tex->pixels, symbols, tex->colors) < 0)
		return (ft_file_clear(&file), -1);
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