/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   hd_alloc_free_t_file.c                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/17 22:07:37 by username         #+#    #+#              */
/*   Updated: 2026/04/07 23:25:04 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	hd_alloc_free_t_file(void *ptr)
{
	ft_file_clear((t_file *) ptr);
}
