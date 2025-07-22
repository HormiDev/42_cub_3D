/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sin_cos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 18:02:32 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/07/22 19:57:37 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

double ft_angle_rad(double degrees)
{
	return (degrees) * M_PI / 180.0;
}

double ft_sin(double angle)
{
	static double *sin_table;
	int i;
	
	if (sin_table == NULL)
	{
		i = 0;
		sin_table = ft_alloc_lst(sizeof(double) * 9000, 3);
		while (i < 9000)
		{
			sin_table[i] = sin(ft_angle_rad(i / 100.0));
			i++;
		}
	}
	angle = angle * 100;
	if (angle < 0)
		angle += 9000;
	if (angle >= 9000)
		angle -= 9000;
	return sin_table[(int)(angle) % 9000];
}

double ft_cos(double angle)
{
	static double *cos_table; 
	int i; 
	if (cos_table == NULL)
	{
		i = 0;

		cos_table = ft_alloc_lst(sizeof(double) * 9000, 3);
		while(i < 9000)
		{
			cos_table[i] = cos(ft_angle_rad(i / 100.0));
			i++;
		}
	}
	angle = angle * 100;
	if (angle < 0)
		angle += 9000;
	if (angle >= 9000)
		angle -= 9000;
	return cos_table[(int)(angle) % 9000];
}