/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 18:32:16 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/20 00:20:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

/**
 * @brief Obtiene el tiempo actual en milisegundos.
 *
 * Esta función utiliza la función gettimeofday para obtener el tiempo actual
 * y lo convierte a milisegundos. Se utiliza para medir el tiempo transcurrido
 * en el juego, como el tiempo de renderizado o la duración de eventos.
 *
 * @return El tiempo actual en milisegundos desde la época (epoch).
 */
long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
