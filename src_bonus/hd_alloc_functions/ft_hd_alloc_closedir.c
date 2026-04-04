/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hd_alloc_closedir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 20:58:40 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/04 21:09:02 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void	ft_hd_alloc_closedir(void *ptr)
{
	if (ptr)
		closedir((DIR *)ptr);
}
