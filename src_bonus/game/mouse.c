/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 02:56:43 by ismherna          #+#    #+#             */
/*   Updated: 2025/12/16 20:33:35 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"
/*
int ft_mouse_move(int x, int y, t_game *game)
{
    int center_x = 1920 / 2;
    int delta_x = x - center_x;
    double sensitivity = 0.003;

    game->player->rotation.x += delta_x * sensitivity;

    if (game->player->rotation.x < 0)
        game->player->rotation.x += 360;
    else if (game->player->rotation.x >= 360)
        game->player->rotation.x -= 360;

    mlx_mouse_move(game->window, center_x, y);

    return (0);
}*/

/**
 * @brief Maneja el movimiento del ratón y actualiza la rotación del jugador.
 *
 * Esta función es llamada cuando el ratón se mueve. Calcula la diferencia en la posición
 * horizontal del ratón respecto al centro de la ventana y actualiza la rotación del jugador.
 * Debido a que el sistema de coordenadas del mundo tiene el eje Y invertido en comparación
 * con las coordenadas de la ventana, invertimos la dirección del movimiento para una 
 * experiencia de control más intuitiva.
 *
 * @param x Posición horizontal del ratón en la ventana.
 * @param y Posición vertical del ratón en la ventana (no se utiliza).
 * @param game Puntero a la estructura del juego.
 * @return Siempre devuelve 0 (requerido por la API de minilibx).
 */
int ft_mouse_move(int x, int y, t_game *game)
{
    int center_x;
    int center_y; 
    int patata_x;
	
	center_x = WINDOW_WIDTH / 2;
	center_y = WINDOW_HEIGHT / 2;
    (void)y;

    if (!game->mouse_captured)
        return (0);

    patata_x = x - center_x;
    game->player->rotation.x -= patata_x * MOUSE_SENSITIVITY * game->delta_time;
    game->player->rotation.x = ft_normalize_angle(game->player->rotation.x);
    mlx_mouse_move(game->mlx, game->window, center_x, center_y);
    return (0);
}

void ft_toggle_mouse_capture(t_game *game)
{
    game->mouse_captured = !game->mouse_captured;

    if (game->mouse_captured)
    {
        mlx_mouse_move(game->mlx, game->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
        mlx_mouse_hide(game->mlx, game->window);
    }
    else
        mlx_mouse_show(game->mlx, game->window);
}

void ft_init_mouse(t_game *game)
{
    game->mouse_captured = true; 
    mlx_mouse_move(game->mlx, game->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
    mlx_mouse_hide(game->mlx, game->window);
}
