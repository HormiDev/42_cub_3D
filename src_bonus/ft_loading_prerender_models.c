/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_prerender_models.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:16:38 by nirmata           #+#    #+#             */
/*   Updated: 2026/04/06 18:15:35 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

static char *ft_get_next_file(DIR *dir, char *path_dir)
{
	struct dirent	*entry;
	struct stat		st;
	char			full_path[1024];

	entry = readdir(dir);
	while (entry)
	{
		ft_sprintf(full_path, "%s%s", path_dir, entry->d_name);
		if (stat(full_path, &st) == 0 && S_ISREG(st.st_mode))
			return (entry->d_name);
		entry = readdir(dir);
	}
	ft_printf("No more files to load.\n");
	return (NULL);
}

void	ft_loading_textures_with_path(t_game *game, t_prerender_model *pre, char *path_dir)
{
	int		i;
	DIR		*dir;
	char	cwd[1024];
	char	*file_name;

	dir = hd_alloc(opendir(path_dir), ft_hd_alloc_closedir);
	if (!dir)
	{
		ft_printf("Error opening directory: %s\n", path_dir);
		return ;
	}
	ft_printf("Loading prerender models from: %s\n", path_dir);
	i = 0;
	file_name = ft_get_next_file(dir, path_dir);
	while (file_name && i < (pre->n_angles * pre->n_frames))
	{
		ft_sprintf(cwd, "%s%s", path_dir, file_name);
		ft_printf("Loading texture: %s\n", file_name);
		pre->texture[i] = ft_loading_texture(game->mlx, cwd);
		if (!pre->texture[i])
		{
			ft_printf("Error loading texture: %s\n", file_name);
			return ;
		}
		i++;
		file_name = ft_get_next_file(dir, path_dir);
	}
	hd_free(dir);
}

void	ft_ordered_textures(t_prerender_model *pre)
{
	t_texture	*tmp;
	int i;
	int j;

	i = 0;
	while (i < (pre->n_angles * pre->n_frames) - 1)
	{
		j = i + 1;
		while (j < (pre->n_angles * pre->n_frames))
		{
			if (ft_strncmp_p(pre->texture[i]->path, pre->texture[j]->path, ft_strlen(pre->texture[j]->path)) > 0)
			{
				tmp = pre->texture[i];
				pre->texture[i] = pre->texture[j];
				pre->texture[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < (pre->n_angles * pre->n_frames) - 1)
	{
		ft_printf("Ordered texture: %s\n", pre->texture[i]->path);
		i++;
	}
}

t_prerender_model	*ft_init_prerender_model(t_game *game, int n_frames, int n_angles, char *path)
{
	t_prerender_model *pre;

	pre = hd_calloc(1, sizeof(t_prerender_model));
	pre->n_frames = n_frames;
	pre->n_angles = n_angles;
	pre->texture = hd_calloc(n_frames * n_angles, sizeof(t_texture *));
	ft_printf("Initializing prerender model with %d frames and %d angles\n", n_frames, n_angles);
	ft_loading_textures_with_path(game, pre, path);
	ft_ordered_textures(pre);
	return (pre);
}

void	ft_loading_prerender_models(t_game *game)
{
	game->alien_prerender = ft_init_prerender_model(game, 1, 36, "textures/prerender/");
}