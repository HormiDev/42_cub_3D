
#include "../../includes/cub_3d.h"
#include <stdbool.h>

bool is_directive_line(char *line)
{
	int i;

	i = 0;
    const char *dirs[6] = {"NO ", "SO ", "EA ", "WE ", "F ", "C "};
    while (i < 6)
    {
        if (ft_strncmp_p(line, dirs[i], ft_strlen(dirs[i])) == 0)
            return true;
		i++;
    }
    return false;
}

static bool is_only_spaces(const char *line)
{
	int j = 0;
	while (line[j])
	{
		if (line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
			return false;
		j++;
	}
	return true;
}

static void check_all_directives_found(bool found[6], const char *dirs[6])
{
	int k = 0;
	while (k < 6)
	{
		if (!found[k])
		{
			ft_dprintf(2, RED "Error: Missing texture or color definition: %s\n" RESET, dirs[k]);
			exit(1);
		}
		k++;
	}
}

int ft_get_map_start_index(t_file *map_file)
{
	int i = 0, k;
	bool found[6] = {false, false, false, false, false, false};
	const char *dirs[6] = {"NO ", "SO ", "EA ", "WE ", "F ", "C "};

	while (map_file->array_content[i])
	{
		if (!is_only_spaces(map_file->array_content[i]))
		{
			k = 0;
			while (k < 6)
			{
				if (ft_strncmp_p(map_file->array_content[i], dirs[k], ft_strlen(dirs[k])) == 0)
				{
					found[k] = true;
					break;
				}
				k++;
			}
			if (k == 6)
				break;
		}
		i++;
	}
	check_all_directives_found(found, dirs);
	return i;
}
