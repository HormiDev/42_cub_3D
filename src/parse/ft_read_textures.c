#include "../../includes/cub_3d.h"
#include <errno.h>
#include <fcntl.h>

size_t	ft_count_char(const char *str, char c) // añadir a la libft
{
	size_t count;
	size_t i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

void		check_arguments_xpm(char *path)
{
	t_file			*file;
	t_strlist		*current;
	char			*start_quote;
	char			*sub_str;

	file = ft_create_file_from_filename(path);
	if (!file)
	{
		ft_dprintf(2, RED "Error: Failed to open XPM file: %s\n" RESET, path);
		ft_close_game(1);
	}
	current = file->list_content;
	while (current)
	{
		start_quote = ft_strchr(current->str, '\"');
		if (start_quote)
		{
			if (!ft_strchr(start_quote + 1, '\"'))
			{
				ft_dprintf(2, RED "Error: Invalid XPM: The quote is not closed: %s\n" RESET, current->str);
				ft_close_game(1);
			}
			sub_str = ft_substr_ae(start_quote + 1, 0, ft_strchr(start_quote + 1, '\"') - start_quote - 1);
			if (ft_splitlen(ft_split_ae(sub_str,' ')) < 4 || ft_splitlen(ft_split_ae(sub_str,' ')) > 4)

			{
				ft_dprintf(2, "Error: Invalid XPM file format in line: %s\n", current->str);
				ft_close_game(1);
			}
			return ;
		}
		current = current->next;
	}
}
