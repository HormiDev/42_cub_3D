/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_alloc_mlx_destroy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:53:51 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 20:00:17 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_hd_alloc_mlx_destroy(void *ptr)
{
	mlx_destroy_display(ptr);
	free(ptr);
}
