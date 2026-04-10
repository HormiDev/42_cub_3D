/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:35:28 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:30:47 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_check_and_correct_door_textures(t_game *game, t_list **list)
{
	ft_printf("Checking and correcting door textures...\n");
	while (ft_lstsize(*list) < 3)
		ft_lstadd_back(list, hd_alloc(ft_lstnew(game->null_texture), free));
}

void	ft_build_array_textures(t_game *game)
{
	int		i;
	t_list	*list;
	int		j;

	i = 0;
	while (i < 7)
	{
		list = game->textures[i];
		if (i == 6)
			ft_check_and_correct_door_textures(game, &list);
		game->larraytex[i] = ft_lstsize(list);
		if (game->larraytex[i] > 0)
		{
			game->arraytextures[i] = hd_calloc(game->larraytex[i],
					sizeof(t_texture *));
			j = 0;
			while (list)
			{
				game->arraytextures[i][j] = (t_texture *)list->content;
				list = list->next;
				j++;
			}
		}
		i++;
	}
}

void	ft_create_render(t_game *game)
{
	int	i;

	game->render = hd_calloc(1, sizeof(t_texture));
	game->render->img = ft_create_image(game->mlx, game->config.render_width,
			game->config.render_height);
	if (!game->render->img)
	{
		ft_dprintf(2, "Error: Failed to create render image\n");
		ft_close_game(1);
	}
	game->render->width = game->config.render_width;
	game->render->height = game->config.render_height;
	game->render->cmx = hd_calloc(game->config.render_height,
			sizeof(unsigned int *));
	i = 0;
	while (i < game->config.render_height)
	{
		game->render->cmx[i] = (unsigned int *)(game->render->img->data + (i
					* sizeof(unsigned int) * game->config.render_width));
		i++;
	}
}

void	ft_create_window_img(t_game *game)
{
	int	i;

	game->window_img = hd_calloc(1, sizeof(t_texture));
	game->window_img->img = ft_create_image(game->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (!game->window_img->img)
	{
		ft_dprintf(2, "Error: Failed to create window image\n");
		ft_close_game(1);
	}
	game->window_img->width = WINDOW_WIDTH;
	game->window_img->height = WINDOW_HEIGHT;
	game->window_img->cmx = hd_calloc(WINDOW_HEIGHT, sizeof(unsigned int *));
	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		game->window_img->cmx[i] = (unsigned int *)(game->window_img->img->data
				+ (i * sizeof(unsigned int) * WINDOW_WIDTH));
		i++;
	}
}

/**
 * @brief Crea la imagen del minimapa.
 * @param game estructura del juego.
 * @details La función crea una imagen de 200x200 píxeles para el minimapa.
 */

void	ft_create_minimap(t_game *game)
{
	int	i;
	int	size;

	size = WINDOW_HEIGHT / 5;
	game->minimap = hd_calloc(1, sizeof(t_texture));
	game->minimap->img = ft_create_image(game->mlx, size, size);
	if (!game->minimap->img)
	{
		ft_dprintf(2, "Error: Failed to create minimap image\n");
		ft_close_game(1);
	}
	game->minimap->width = size;
	game->minimap->height = size;
	game->minimap->cmx = hd_calloc(size, sizeof(unsigned int *));
	i = 0;
	while (i < size)
	{
		game->minimap->cmx[i] = (unsigned int *)(game->minimap->img->data + (i
					* sizeof(unsigned int) * size));
		i++;
	}
}
