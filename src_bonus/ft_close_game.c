/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:25:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/09 00:35:30 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Libera la memoria asignada y cierra el juego.
 *
 * Esta función libera toda la memoria asignada por el juego y finaliza el programa
 * con el código de salida especificado.
 *
 * @param exit_code Código de salida del programa.
 */
void	ft_close_game(int exit_code)
{
	hd_alloc_clear();
	exit(exit_code);
}

/**
 * @brief Libera la memoria del gamepad y cierra el juego.
 *
 * Esta función libera la memoria asignada al gamepad y finaliza el programa.
 * Se utiliza para limpiar los recursos antes de cerrar el juego.
 *
 * @param game estructura del juego que contiene el gamepad.
 */
int	ft_close_game_for_mlx(t_game *game)
{
	if (game)
	{
		audio_manager_stop(game->audio_manager);
		ft_free_gamepad(game);
		ft_free_doors(game);
	}
	hd_alloc_clear();
	exit(0);
}
