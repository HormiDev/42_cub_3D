/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu_buttons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 20:17:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * ft_start_button - Inicia el botón de inicio.
 * @game_ptr: estructura del juego.
 */

void	ft_start_button(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (!game)
		return ;
	if (game->game_state != GAME_PLAYING)
		ft_restart_match(game);
	audio_manager_send(game->audio_manager, "stop");
	game->show_menu = 0;
}

void	ft_settings_button(void *game_ptr)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	if (!game)
		return ;
	game->tmp_config = game->config;
	game->show_menu = 2;
}

void	ft_exit_button(void *game_ptr)
{
	(void)game_ptr;
	ft_close_game(0);
}

/**
 * ft_loading_texture_buttons - Carga las texturas de un botón.
 * @game: estructura del juego.
 * @button: Puntero al botón a configurar.
 * @base_texture: Ruta de la textura base del botón.
 * @hover_texture: Ruta de la textura de hover del botón.
 */
void	ft_loading_texture_buttons(t_game *game, t_button *button,
		char *base_texture, char *hover_texture)
{
	t_texture	*button_texture;

	button_texture = ft_loading_texture(game->mlx, base_texture);
	button->texture = ft_new_texture(game->mlx, button->size.x, button->size.y);
	ft_scale_t_image(button_texture, button->texture);
	button_texture = ft_loading_texture(game->mlx, hover_texture);
	button->hover_texture = ft_new_texture(game->mlx, button->size.x,
			button->size.y);
	ft_scale_t_image(button_texture, button->hover_texture);
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
		ft_init_timer(game);
	game->show_menu = 1;
}
