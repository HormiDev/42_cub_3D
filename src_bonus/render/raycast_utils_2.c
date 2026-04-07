/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   raycast_utils_2.c                                 :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/04/07 23:21:04 by username         #+#    #+#              */
/*   Updated: 2026/04/07 23:21:04 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

long	ft_long_diff(long a, long b) // llevar a la libft
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int	ft_int_diff(int a, int b) // llevar a la libft
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int	ft_int_max(int a, int b) // llevar a la libft
{
	if (a > b)
		return (a);
	return (b);
}
