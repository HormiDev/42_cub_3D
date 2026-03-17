/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:25:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/15 22:41:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

/**
 * @brief Libera la memoria asignada y cierra el juego.
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
int	ft_close_game_for_mlx(void)
{
	hd_alloc_clear();
	exit(0);
}
