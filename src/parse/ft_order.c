
#include "../../includes/cub_3d.h"
#include <stdbool.h>

int ft_directives(char *line, const char *directive, bool *found_flag)
{
    if (ft_strncmp_p(line, directive, ft_strlen(directive)) == 0 && !(*found_flag))
    {
        *found_flag = true;
        return 1;
    }
    return 0;
}

int ft_check_all_directives(t_file *map_file, bool *found_flags)
{
    int i = 0;
    int count = 0;
    const char *dirs[6] = {"NO ", "SO ", "EA ", "WE ", "F ", "C "};
    char **array = map_file->array_content;

    while (map_file->array_content[i])
    {
        count += ft_directives(array[i], dirs[0], &found_flags[0]);
        count += ft_directives(array[i], dirs[1], &found_flags[1]);
        count += ft_directives(array[i], dirs[2], &found_flags[2]);
        count += ft_directives(array[i], dirs[3], &found_flags[3]);
        count += ft_directives(array[i], dirs[4], &found_flags[4]);
        count += ft_directives(array[i], dirs[5], &found_flags[5]);

        if (count == 6)
            return i + 1;
        i++;
    }
    return -1;
}

int ft_get_map_start_index(t_file *map_file)
{
    int i;
    bool found[6] = {false, false, false, false, false, false};

    i = ft_check_all_directives(map_file, found);
    if (i == -1)
    {
        ft_dprintf(2, RED "Error: Missing texture or color definition.\n" RESET);
        exit (1);
    }

    while (map_file->array_content[i])
    {
        int j = 0;
        while (map_file->array_content[i][j])
        {
            if (map_file->array_content[i][j] != ' ' && map_file->array_content[i][j] != '\t' && map_file->array_content[i][j] != '\n')
                return i;
            j++;
        }
        i++;
    }
    return i;
}
