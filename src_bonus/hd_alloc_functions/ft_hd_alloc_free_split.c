/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_alloc_free_split.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 01:48:37 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/04 21:09:02 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_hd_alloc_free_split(void *ptr)
{
	ft_free_split((char **)ptr);
}