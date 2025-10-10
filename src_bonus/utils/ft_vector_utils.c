/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/10/07 00:00:00 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_vector_int_abs(t_vector_int *v)
{
	v->x = ft_abs(v->x);
	v->y = ft_abs(v->y);
}

int	ft_vector_int_max(t_vector_int v)
{
	if (v.x > v.y)
		return (v.x);
	return (v.y);
}
