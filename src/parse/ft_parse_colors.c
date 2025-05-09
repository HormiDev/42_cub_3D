#include "../../includes/cub_3d.h"

static void ft_set_color(int *target_color, int r, int g, int b)
{
    target_color[0] = r;
    target_color[1] = g;
    target_color[2] = b;
}

int ft_parse_rgb_values(t_game *game, char *color_str, int color_type)
{
    char **rgb_values;
    int r, g, b;
    int i;

    rgb_values = ft_split_ae(color_str, ',');
    if (!rgb_values)
        return (ft_dprintf(2, RED "Error: Failed to split color values.\n" RESET), 0);
    i = 0;
    while (rgb_values[i])
        i++;
    if (i != 3)
        return (ft_dprintf(2, RED "Error: Invalid color format. Expected R,G,B.\n" RESET), 0);
    r = ft_atoi(rgb_values[0]);
    g = ft_atoi(rgb_values[1]);
    b = ft_atoi(rgb_values[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        return (ft_dprintf(2, RED "Error: Color values must be between 0 and 255.\n" RESET), 0);

    if (color_type == FLOOR)
        ft_set_color(game->floor_color, r, g, b);
    else if (color_type == CEILING)
        ft_set_color(game->ceiling_color, r, g, b);
    return (1);
}

int ft_get_color_string(t_game *game, char *line, int color_type)
{
    char *color_str;

    if ((color_str = ft_strtrim(line + 2, " \t\n")) != NULL)
    {
        if (ft_parse_rgb_values(game, color_str, color_type))
            return (1);
        return (0);
    }
    else
    {
        ft_dprintf(2, RED "Error: Failed to trim color string.\n" RESET);
        return (0);
    }
}


void ft_parse_colors(t_game *game, t_file *map_file)
{
    int i; 
    int count; 

    i = 0; 
    count = 0; 
    while (map_file->array_content[i] && count < 2)
	{
		if (ft_strncmp_p(map_file->array_content[i], "F ", 2) == 0)
			count += ft_get_color_string(game, map_file->array_content[i], FLOOR);
		else if (ft_strncmp_p(map_file->array_content[i], "C ", 2) == 0)
			count += ft_get_color_string(game, map_file->array_content[i], CEILING);
		i++;
	}

	if (count != 2)
		ft_dprintf(2, RED "Error: Failed to load colors: missing elements \n" RESET);
}