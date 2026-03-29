/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_alloc_mlx_destroy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 00:08:55 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/18 00:43:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

void	ft_hd_alloc_mlx_destroy(void *ptr)
{
	mlx_destroy_display(ptr);
	free(ptr);
}