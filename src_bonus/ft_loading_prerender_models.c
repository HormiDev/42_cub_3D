/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_prerender_models.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:16:38 by nirmata           #+#    #+#             */
/*   Updated: 2026/04/10 03:09:52 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_loading_textures_with_path(t_game *game,
									t_prerender_model *pre,

									char *path_dir)
{
	int		i;
	DIR		*dir;
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
	while (i < (pre->n_angles * pre->n_frames))
	{
		ft_load_prerender_texture(game, pre,
			(t_prerender_load){i, file_name, path_dir});
		i++;
		file_name = ft_get_next_file(dir, path_dir);
	}
	hd_free(dir);
}

void	ft_ordered_textures(t_prerender_model *pre)
{
	ft_sort_textures_bubble(pre);
	ft_print_sorted_textures(pre);
}

t_prerender_model	*ft_init_prerender_model(t_game *game, int n_frames,
		int n_angles, char *path)
{
	t_prerender_model	*pre;

	pre = hd_calloc(1, sizeof(t_prerender_model));
	pre->n_frames = n_frames;
	pre->n_angles = n_angles;
	pre->texture = hd_calloc(n_frames * n_angles, sizeof(t_texture *));
	ft_printf("Initializing prerender model with %d frames and %d angles\n",
		n_frames, n_angles);
	ft_loading_textures_with_path(game, pre, path);
	ft_ordered_textures(pre);
	if (n_frames)
		pre->active_frame = n_frames;
	return (pre);
}

void	ft_loading_prerender_models(t_game *game)
{
	game->alien_prerender = ft_init_prerender_model(game, 12, 36,
			"textures/prerender_alien/");
}
