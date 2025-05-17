#include "../../includes/cub_3d.h"

int	ft_parse_single_texture(t_game *game, char *line, int texture_index)
{
	char *path;

    path = ft_add_to_alloc_lst_e(ft_strtrim(line + 3, " \t\n"));
	if (path != NULL)
	{
		game->textures[texture_index] = path;
		return (1);
	}
	else
		ft_dprintf(2, RED "Error: parse texture.\n" RESET);
	return (0);
}

void ft_parse_textures(t_game *game, t_file *map_file)
{
    int i; 
    int count; 

    i = 0; 
    count = 0; 

    while(map_file->array_content[i] && count < 4)
    {
            if (ft_strncmp_p(map_file->array_content[i], "NO ", 3) == 0)
            count += ft_parse_single_texture(game, map_file->array_content[i], NORTH);
        else if (ft_strncmp_p(map_file->array_content[i], "SO ", 3) == 0)
            count += ft_parse_single_texture(game, map_file->array_content[i], SOUTH);
        else if (ft_strncmp_p(map_file->array_content[i], "WE ", 3) == 0)
            count += ft_parse_single_texture(game, map_file->array_content[i], WEST);
        else if (ft_strncmp_p(map_file->array_content[i], "EA ", 3) == 0)
            count += ft_parse_single_texture(game, map_file->array_content[i], EAST);
        i++;
    }
    if (count != 4)
        ft_dprintf(2, RED "Error: Failed to load textures: missing elements" RESET); 
}
