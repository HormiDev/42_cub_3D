/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_prerender_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 03:05:00 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 03:09:33 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

char	*ft_get_next_file(DIR *dir, char *path_dir)
{
	struct dirent	*entry;
	struct stat		st;
	char			full_path[1024];

	entry = readdir(dir);
	while (entry)
	{
		ft_snprintf(full_path, sizeof(full_path), "%s%s", path_dir,
			entry->d_name);
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode))
			return (entry->d_name);
		entry = readdir(dir);
	}
	ft_printf("No more files to load.\n");
	return (NULL);
}

void	ft_load_prerender_texture(t_game *game, t_prerender_model *pre,
		t_prerender_load load_ctx)
{
	char	cwd[1024];

	if (!load_ctx.file_name)
		pre->texture[load_ctx.idx] = game->null_texture;
	else if (ft_strnstr(load_ctx.file_name + ft_strlen(load_ctx.file_name) - 4,
		".xpm", 4))
	{
		ft_snprintf(cwd, sizeof(cwd), "%s%s", load_ctx.path_dir,
			load_ctx.file_name);
		ft_printf("Loading texture: %s\n", load_ctx.file_name);
		pre->texture[load_ctx.idx] = ft_loading_texture(game->mlx, cwd);
		if (!pre->texture[load_ctx.idx])
			pre->texture[load_ctx.idx] = game->null_texture;
	}
}

void	ft_sort_textures_bubble(t_prerender_model *pre)
{
	t_texture	*tmp;
	int			i;
	int			j;
	int			size;

	size = pre->n_angles * pre->n_frames;
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (pre->texture[i]->path && pre->texture[j]->path
				&& ft_strncmp_p(pre->texture[i]->path, pre->texture[j]->path,
					ft_strlen(pre->texture[j]->path)) > 0)
			{
				tmp = pre->texture[i];
				pre->texture[i] = pre->texture[j];
				pre->texture[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_sorted_textures(t_prerender_model *pre)
{
	int	i;
	int	size;

	size = pre->n_angles * pre->n_frames;
	ft_printf("Ordered textures: %d   %d\n", size - 1, size);
	i = 0;
	while (i < size - 1)
	{
		ft_printf("Ordered texture: %s\n", pre->texture[i]->path);
		i++;
	}
}
