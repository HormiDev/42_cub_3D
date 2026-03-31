/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/31 20:46:27 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Devuelve el valor absoluto de un entero.
 * @param n El entero del cual obtener el valor absoluto.
 * @return El valor absoluto de n.
 */
int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/**
 * @brief Devuelve el valor absoluto de un vector de enteros.
 * @param v El vector del cual obtener el valor absoluto.
 */
void	ft_vector_int_abs(t_vector_int *v)
{
	v->x = ft_abs(v->x);
	v->y = ft_abs(v->y);
}

/**
 * @brief Devuelve el valor máximo de un vector de enteros.
 * @param v El vector del cual obtener el valor máximo.
 * @return El valor máximo de v.
 */
int	ft_vector_int_max(t_vector_int v)
{
	if (v.x > v.y)
		return (v.x);
	return (v.y);
}
