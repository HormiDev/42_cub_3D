/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precalc_rotated_squares.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 00:00:00 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/03 17:35:43 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * Rota un punto (x, y) alrededor del origen por un ángulo dado.
 * @param x Puntero al valor de la coordenada x.
 * @param y Puntero al valor de la coordenada y.
 * @param angle Ángulo de rotación en radianes.
 */
static void	ft_rotate_point(int *x, int *y, double angle)
{
	double	temp_x;
	double	temp_y;
	double	cos_a;
	double	sin_a;
	
	cos_a = ft_cos(angle);
	sin_a = ft_sin(angle);
	temp_x = *x * cos_a - *y * sin_a;
	temp_y = *x * sin_a + *y * cos_a;
	*x = (int)round(temp_x);
	*y = (int)round(temp_y);
}

/**
 * Inicializa las esquinas de un cuadrado centrado en el origen con un tamaño dado.
 * @param square Puntero a la estructura t_rotated_square donde se almacenarán las coordenadas.
 * @param size Tamaño del cuadrado.
 */
static void	ft_init_square_corners(t_rotated_square *square, int size)
{
	int	half;
	
	half = size / 2;
	square->x[0] = -half;
	square->y[0] = -half;
	square->x[1] = half;
	square->y[1] = -half;
	square->x[2] = half;
	square->y[2] = half;
	square->x[3] = -half;
	square->y[3] = half;
}

/**
 * Rota las esquinas de un cuadrado por un ángulo especificado.
 * @param square Puntero a la estructura t_rotated_square que contiene las esquinas.
 * @param angle Ángulo de rotación en radianes.
 * @param size Tamaño del cuadrado.
 */
static void	ft_rotate_square(t_rotated_square *square, double angle, int size)
{
	int	i;
	
	ft_init_square_corners(square, size);
	i = 0;
	while (i < 4)
	{
		ft_rotate_point(&square->x[i], &square->y[i], angle);
		i++;
	}
}

/**
 * Precalcula y retorna una lista de cuadrados rotados para cada ángulo de 0 a 359.99 grados.
 * @return Puntero a un arreglo de estructuras t_rotated_square con las coordenadas precalculadas.
 */
t_rotated_square	*ft_precalc_rotated_squares(void)
{
	t_rotated_square	*squares;
	int					angle_idx;
	double				angle;

	squares = ft_alloc_lst(sizeof(t_rotated_square) * 36000, 3);
	angle_idx = 0;
	while (angle_idx < 36000)
	{
		angle = angle_idx / 100.0;
		ft_rotate_square(&squares[angle_idx], angle, MINIMAP_TILE_SIZE);
		angle_idx++;
	}
	return (squares);
}
