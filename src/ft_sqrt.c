/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:57:27 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/07/25 01:48:38 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

double ft_sqrt(double value)
{
	static double *sqrt_table;
	int i;
	static int table_size;

	if (sqrt_table == NULL)
	{
		i = 0;
		table_size = MAX_RAY_SIZE * MAX_RAY_SIZE * 2 * 100;
		printf("Creating sqrt table with size: %d\n", table_size);
		sqrt_table = ft_alloc_lst(sizeof(double) * table_size, 3);
		while (i < table_size)
		{
			sqrt_table[i] = sqrt(i / 100.0);
			i++;
		}
	}
	value = value * 100;
	if (value < 0)
		value = -value;
	if (value >= table_size)
		value = table_size - 1;
	return sqrt_table[(int)(value) % table_size];
}