/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 23:21:04 by username          #+#    #+#             */
/*   Updated: 2026/04/08 00:49:57 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

long	ft_long_diff(long a, long b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int	ft_int_diff(int a, int b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int	ft_int_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
