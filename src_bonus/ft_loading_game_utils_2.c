/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_game_utils_2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:35:28 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:35:04 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_load_all_textures(t_game *game)
{
	game->font = ft_loading_texture(game->mlx, "textures/fuente.xpm");
	if (!game->font)
		ft_dprintf(2, RED "Error: Failed to load font texture\n" RESET);
	game->screen_end_img = ft_loading_texture(game->mlx,
			"textures/PANTALLA-WIN.xpm");
	if (!game->screen_end_img)
		ft_dprintf(2, RED "Error: Failed to load end screen texture\n" RESET);
	game->screen_alien_img = ft_loading_texture(game->mlx,
			"textures/Alien-win.xpm");
	if (!game->screen_alien_img)
		ft_dprintf(2, RED "Error: Failed to load end screen texture\n" RESET);
	game->dead_image = ft_loading_texture(game->mlx, "textures/dead_image.xpm");
	if (!game->dead_image)
		ft_dprintf(2, RED "Error: Failed to load dead image texture\n" RESET);
	game->flamethrower_frames[0] = ft_loading_texture(game->mlx,
			"textures/AlienIsolation/lanzallamas/lanzallamas quieto.xpm");
	if (!game->flamethrower_frames[0])
		ft_dprintf(2, RED "Error: Failed to load flamethrower texture\n" RESET);
	game->flamethrower_frames[1] = ft_loading_texture(game->mlx,
			"textures/AlienIsolation/lanzallamas/lanzallamas disparo 1.xpm");
	game->flamethrower_frames[2] = ft_loading_texture(game->mlx,
			"textures/AlienIsolation/lanzallamas/lanzallamas disparo 2.xpm");
	game->flamethrower_frames[3] = ft_loading_texture(game->mlx,
			"textures/AlienIsolation/lanzallamas/lanzallamas disparo 3.xpm");
}

void	ft_setup_map_and_ui(t_game *game, t_file *map_file)
{
	ft_parse_map(game, map_file);
	ft_read_textures_in_map(game, map_file);
	ft_build_array_textures(game);
	ft_loading_menu(game);
	ft_loading_menu_settings(game);
}

void	ft_init_game(t_game *game)
{
	game->config.n_players = 1;
	game->config.duration_index = 2;
	game->config.charges = 3;
	game->config.resolution_index = RES_540;
	game->game_state = GAME_PLAYING;
	ft_init_durations(game);
	ft_init_timer(game);
	ft_init_resolutions(game);
	ft_sin(0);
	ft_cos(0);
	ft_sqrt(0);
	game->precalc.rotated_squares = ft_precalc_rotated_squares();
}
