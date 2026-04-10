/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_settings.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:17:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 02:44:09 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_init_settings_button_assets(const char **right_btn,
		const char **left_btn, void (*callbacks[9])(void *),
		t_vector_int positions[9])
{
	right_btn[0] = "textures/menu/button_right.xpm";
	right_btn[1] = "textures/menu/button_right_hover.xpm";
	left_btn[0] = "textures/menu/button_left.xpm";
	left_btn[1] = "textures/menu/button_left_hover.xpm";
	ft_fill_settings_callbacks(callbacks);
	ft_fill_settings_positions(positions);
}

void	ft_menu_button(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (!game)
		return ;
	if (game->config.resolution_index != game->tmp_config.resolution_index)
		ft_loading_render(game,
			game->resolutions[game->config.resolution_index].height,
			game->resolutions[game->config.resolution_index].width);
	if (game->config.n_players != game->tmp_config.n_players)
	{
		ft_loading_render(game,
			game->resolutions[game->config.resolution_index].height,
			game->resolutions[game->config.resolution_index].width);
		ft_config_player(game);
		ft_config_alien(game);
		ft_remap_gamepads(game);
	}
	if (game->config.charges != game->tmp_config.charges)
		ft_config_player(game);
	if (game->config.duration_index != game->tmp_config.duration_index)
	{
		ft_init_timer(game);
	}
	game->show_menu = 1;
}

void	ft_loading_settings_buttons(t_game *game)
{
	const char		*right_btn[2];
	const char		*left_btn[2];
	void			(*callbacks[9])(void *);
	t_vector_int	positions[9];
	int				i;

	ft_init_settings_button_assets(right_btn, left_btn, callbacks, positions);
	game->menu_settings.n_buttons = 9;
	game->menu_settings.buttons = hd_calloc(game->menu_settings.n_buttons,
			sizeof(t_button));
	i = 0;
	while (i < game->menu_settings.n_buttons)
	{
		if (i == 0 || i % 2 == 1)
			ft_setup_settings_button(game, i, positions[i], right_btn,
				callbacks[i]);
		else
			ft_setup_settings_button(game, i, positions[i], left_btn,
				callbacks[i]);
		i++;
	}
}

void	ft_loading_menu_settings(t_game *game)
{
	ft_bzero(&game->menu_settings, sizeof(t_menu));
	game->menu_settings.current_frame = 0;
	game->menu_settings.render = game->menu.render;
	ft_loading_settings_buttons(game);
}
