/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 17:38:41 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/06 22:44:40 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

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
