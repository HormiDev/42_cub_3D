/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   ft_hd_alloc_free_split.c                          :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/18 01:48:37 by username         #+#    #+#              */
/*   Updated: 2026/04/07 23:25:04 by username        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_hd_alloc_free_split(void *ptr)
{
	ft_free_split((char **) ptr);
}
