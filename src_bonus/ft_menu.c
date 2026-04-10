/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_menu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by username          #+#    #+#             */
/*   Updated: 2026/04/10 02:49:17 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

void	ft_restart_match(t_game *game)
{
	int		i;
	t_list	*current;
	t_door	*door;

	if (!game)
		return ;
	ft_init_timer(game);
	i = 0;
	while (i < MAX_GAMEPADS)
	{
		input_reset_actions(game, i);
		i++;
	}
	ft_config_player(game);
	if (game->player_spawn_initialized)
	{
		game->players[0].position = game->player_spawn_position;
		game->players[0].rotation.x = game->player_spawn_rotation;
	}
	ft_config_alien(game);
	current = game->doors;
	while (current)
	{
		door = (t_door *)current->content;
		door->state = DOOR_OPEN;
		door->auto_reopen_timer = -1.0;
		game->map[door->position.y][door->position.x] = 'd';
		current = current->next;
	}
	game->player = &game->players[0];
}

static void	ft_load_menu_logo(t_game *game)
{
	game->menu.logo = ft_loading_texture(game->mlx, "textures/Alien_logo.xpm");
	if (!game->menu.logo)
	{
		ft_dprintf(2, RED "Error: Failed to load menu logo texture\n" RESET);
	}
}

void	ft_draw_buttons_menu(t_menu *menu)
{
	int	i;

	i = 0;
	while (i < menu->n_buttons)
	{
		if (menu->buttons[i].is_hovered && menu->buttons[i].hover_texture)
		{
			ft_draw_image_rgba(menu->render, menu->buttons[i].hover_texture,
				menu->buttons[i].position.x, menu->buttons[i].position.y);
		}
		else if (menu->buttons[i].texture)
		{
			ft_draw_image_rgba(menu->render, menu->buttons[i].texture,
				menu->buttons[i].position.x, menu->buttons[i].position.y);
		}
		i++;
	}
}

void	ft_draw_menu_background(t_game *game)
{
	long	time_diff;

	time_diff = ft_long_diff(game->menu.last_frame_time, game->current_time);
	if (time_diff > MENU_FRAME_MS)
	{
		game->menu.current_frame++;
		if (game->menu.current_frame >= game->menu.total_frames
			&& game->menu.total_frames > 0)
			game->menu.current_frame = 0;
		game->menu.last_frame_time = game->current_time;
	}
	if (game->menu.total_frames > 0)
	{
		ft_scale_t_image(game->menu.frames_textures[game->menu.current_frame],
			game->menu.render);
	}
}

void	ft_update_menu(t_game *game)
{
	char	resolution[12];
	char	players[20];
	char	charges[20];
	char	timer[20];

	ft_draw_menu_background(game);
	if (game->show_menu == 1)
	{
		if (game->menu.logo)
			ft_draw_image_rgba(game->menu.render, game->menu.logo, MENU_WIDTH
				/ 2 - game->menu.logo->width / 2, MENU_HEIGHT / 6);
		ft_draw_buttons_menu(&game->menu);
	}
	else if (game->show_menu == 2)
	{
		ft_draw_buttons_menu(&game->menu_settings);
		ft_draw_string_hud(game->menu_settings.render, game->font, "Resolution",
			&(t_vector_int){MENU_WIDTH / 2 - (6 * 6 * 10 / 2), 30}, 6);
		ft_snprintf(resolution, sizeof(resolution), "%d x %d",
			game->resolutions[game->config.resolution_index].width,
			game->resolutions[game->config.resolution_index].height);
		ft_draw_string_hud(game->menu_settings.render, game->font, resolution,
			&(t_vector_int){MENU_WIDTH / 2 - (6 * 6 * ft_strlen(resolution)
				/ 2), 110}, 6);
		ft_snprintf(players, sizeof(players), "players %d",
			game->config.n_players);
		ft_draw_string_hud(game->menu_settings.render, game->font, players,
			&(t_vector_int){MENU_WIDTH / 2 - (6 * 6 * ft_strlen(players) / 2),
			210}, 6);
		ft_snprintf(charges, sizeof(charges), "charges %d",
			game->config.charges);
		ft_draw_string_hud(game->menu_settings.render, game->font, charges,
			&(t_vector_int){MENU_WIDTH / 2 - (6 * 6 * ft_strlen(charges) / 2),
			310}, 6);
		ft_snprintf(timer, sizeof(timer), "timer %d",
			game->durations[game->config.duration_index]);
		ft_draw_string_hud(game->menu_settings.render, game->font, timer,
			&(t_vector_int){MENU_WIDTH / 2 - (6 * 6 * ft_strlen(timer) / 2),
			410}, 6);
	}
	ft_draw_string_hud(game->menu.render, game->font,
		"42 cub3d by hormidev and ismaelucky342", &(t_vector_int){10,
		MENU_HEIGHT - 30}, 2);
	ft_scale_t_image(game->menu.render, game->window_img);
	mlx_clear_window(game->mlx, game->window);
	mlx_put_image_to_window(game->mlx, game->window, game->window_img->img, 0,
		0);
}

void	ft_loading_menu_frames(t_game *game)
{
	char		path[256];
	int			i;
	t_texture	*frame;

	i = 0;
	hd_alloc_set_error_func(0);
	while (i < 200)
	{
		ft_snprintf(path, sizeof(path), "menu_frames/frame_%d.xpm", i);
		frame = ft_loading_texture(game->mlx, path);
		if (frame)
			game->menu.frames_textures[i] = frame;
		else
			game->menu.frames_textures[i] = game->null_texture;
		i++;
	}
	hd_alloc_set_error_func(hd_alloc_error_func_d);
	game->menu.total_frames = i;
}

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
/**
 * ft_button_position_size - Establece la posición y el tamaño de un botón.
 * @button: Puntero al botón a configurar.
 * @x: Coordenada x de la posición del botón.
 * @y: Coordenada y de la posición del botón.
 * @width: Ancho del botón.
 * @height: Alto del botón.

	* Descripción: Esta función asigna las coordenadas de posición y las dimensiones
 * especificadas al botón proporcionado.
 */

void	ft_button_position_size(t_button *button, int x, int y, int width,
		int height)
{
	button->position.x = x;
	button->position.y = y;
	button->size.x = width;
	button->size.y = height;
}

void	ft_loading_menu_buttons(t_game *game)
{
	game->menu.n_buttons = 3;
	// Actualizar si se añaden más botones
	game->menu.buttons = hd_calloc(game->menu.n_buttons, sizeof(t_button));
	// Play Button
	ft_button_position_size(&game->menu.buttons[0], (MENU_WIDTH / 2)
		- (MENU_BUTTON_WIDTH / 2), (MENU_HEIGHT / 2), MENU_BUTTON_WIDTH,
		MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu.buttons[0],
		"textures/menu/button_play.xpm", "textures/menu/button_play_hover.xpm");
	game->menu.buttons[0].on_click = ft_start_button;
	// Settings Button
	ft_button_position_size(&game->menu.buttons[1], (MENU_WIDTH / 2)
		- (MENU_BUTTON_WIDTH / 2), (MENU_HEIGHT / 2) + MENU_BUTTON_HEIGHT + 20,
		MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu.buttons[1],
		"textures/menu/button_settings.xpm",
		"textures/menu/button_settings_hover.xpm");
	game->menu.buttons[1].on_click = ft_settings_button;
	// Implementar función de opciones
	// Exit Button
	ft_button_position_size(&game->menu.buttons[2], (MENU_WIDTH / 2)
		- (MENU_BUTTON_WIDTH / 2), (MENU_HEIGHT / 2) + 2 * (MENU_BUTTON_HEIGHT
			+ 20), MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT);
	ft_loading_texture_buttons(game, &game->menu.buttons[2],
		"textures/menu/button_exit.xpm", "textures/menu/button_exit_hover.xpm");
	game->menu.buttons[2].on_click = ft_exit_button;
}

void	ft_loading_menu(t_game *game)
{
	ft_bzero(&game->menu, sizeof(t_menu));
	game->menu.current_frame = 0;
	game->menu.last_frame_time = game->current_time;
	game->menu.render = ft_new_texture(game->mlx, MENU_WIDTH, MENU_HEIGHT);
	ft_loading_menu_frames(game);
	ft_load_menu_logo(game);
	ft_loading_menu_buttons(game);
}
