/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_hd_alloc_mlx_destroy.c                         :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/18 00:08:55 by username         #+#    #+#              */
/*   Updated: 2026/04/07 23:25:04 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_hd_alloc_mlx_destroy(void *ptr)
{
	mlx_destroy_display(ptr);
	free(ptr);
}
