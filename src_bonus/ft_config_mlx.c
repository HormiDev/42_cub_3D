/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:42:30 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/01/03 19:44:52 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Libera la memoria asignada a la estructura mlx y cierra la ventana.
 *
 * Esta función libera la memoria asignada a la estructura mlx y cierra la ventana del juego.
 * Se utiliza para limpiar los recursos antes de cerrar el juego.
 *
 * @param game Puntero a la estructura del juego que contiene la información de mlx.
 */
void	ft_free_mlx(t_game *game)
{
	if (game->mlx)
	{
		if (game->window)
			mlx_destroy_window(game->mlx, game->window);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

/**
 * @brief Inicializa MLX y crea la ventana del juego.
 *
 * Esta función inicializa la biblioteca mlx y crea una nueva ventana.
 * Si ocurre algún error durante la inicialización, se imprime un mensaje de error y se cierra el juego.
 *
 * @param game Puntero a la estructura del juego que contiene la información de mlx y la ventana.
 */
static void	ft_init_mlx_window(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		ft_dprintf(2, RED "Error:\n Failed to initialize mlx\n" RESET);
		ft_close_game(1);
	}
	game->window = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!game->window)
	{
		ft_dprintf(2, RED "Error:\n Failed to create window\n" RESET);
		ft_close_game(1);
	}
}

/**
 * @brief Configura la imagen y los hooks de eventos para MLX.
 *
 * Esta función crea la imagen para el mapa del juego y configura los hooks 
 * para eventos de teclado, ratón y gamepad. También inicializa el tiempo del frame.
 *
 * @param game Puntero a la estructura del juego que contiene la información de mlx.
 */
static void	ft_setup_mlx_hooks(t_game *game)
{
	game->img_map = ft_alloc_lst(sizeof(t_image), 4);
	game->img_map->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img_map->img)
	{
		ft_dprintf(2, RED "Error:\n Failed to create image\n" RESET);
		ft_close_game(1);
	}
	game->img_map->img_data = mlx_get_data_addr(game->img_map->img, &game->img_map->bits_pixel, &game->img_map->image_len, &game->img_map->end);
	mlx_hook(game->window, 17, 0, ft_close_game_for_mlx, game);
	mlx_hook(game->window, 6, 1L << 6, ft_mouse_move, game);
	mlx_hook(game->window, 2, 1L<<0, ft_key_press, game);
	mlx_hook(game->window, 3, 1L<<1, ft_key_release, game);
	mlx_hook(game->window, 4, 1L<<2, ft_mouse_click, game);
	game->last_frame_time = ft_get_time();
	mlx_loop_hook(game->mlx, ft_update, game);
	ft_init_gamepad(game);
}

/**
 * @brief Configura la biblioteca mlx y crea una ventana para el juego.
 *
 * Esta función inicializa completamente MLX llamando a las funciones auxiliares
 * para inicializar la ventana y configurar los hooks de eventos.
 *
 * @param game Puntero a la estructura del juego que contiene la información de mlx y la ventana.
 */
void	ft_config_mlx(t_game *game)
{
	ft_init_mlx_window(game);
	ft_setup_mlx_hooks(game);
}
