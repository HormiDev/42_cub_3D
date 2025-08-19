/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:22:54 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/08/20 00:34:39 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief draw_background - Dibuja el fondo (techo y suelo) de la pantalla
 * @param game: Puntero a la estructura del juego
*/ 
void draw_background(t_game *game)
{
	int					x;
	int					y;
	unsigned int		floor_color;
	unsigned int		ceiling_color;
	
	y = 0;
	while (y < RENDER_HEIGHT)
	{
		x = 0;
		while (x < RENDER_WIDTH)
		{
			if (y < RENDER_HEIGHT / 2)
				game->render->colors_matrix[y][x] = game->ceiling_tex->texture_color;
			else
				game->render->colors_matrix[y][x] = game->floor_tex->texture_color;
			x++;
		}
		y++;
	}
}

/**
 * @brief get_draw_limits - Calcula las posiciones de inicio y fin para dibujar una columna de pared.
 * @param wall_height: Altura de la porción de pared a dibujar.
 * @param win_height: Altura de la ventana o pantalla.
 * @param draw_start: Puntero donde se almacena la coordenada y inicial de dibujo.
 * @param draw_end: Puntero donde se almacena la coordenada y final de dibujo.
 */
static void	get_draw_limits(int wall_height, int win_height, int *draw_start, int *draw_end)
{
	*draw_start = -wall_height / 2 + win_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = wall_height / 2 + win_height / 2;
	if (*draw_end >= win_height)
		*draw_end = win_height - 1;
}

 
/**
 * @brief get_texture_for_wall - Obtiene la textura correspondiente al tipo de pared
 * @param game: Puntero a la estructura del juego
 * @param wall_type: Tipo de pared (WALL_NO, WALL_SO, WALL_EA, WALL_WE)
 * @return Puntero a la textura o NULL si no se encuentra
 */
static t_texture *get_texture_for_wall(t_game *game, int wall_type)
{
	t_list		*texture_list;
	
	if (!game || wall_type < 0 || wall_type > 3)
		return (NULL);
		
	texture_list = game->textures[wall_type];
	if (!texture_list || !texture_list->content)
		return (NULL);
		
	return ((t_texture *)texture_list->content);
}

int ft_calculate_wall_height(t_game *game, t_raycast ray, int x)//pal ojo de pez <--
{
	double	column_angle;
	double	angle_rad;
	double	corrected_dist;
	int		wall_height;

	if (ray.type < 0 || ray.distance <= 0.0)
		return;

	column_angle = ((double)x / (double)RENDER_WIDTH - 0.5) * FOV;
	angle_rad = column_angle * M_PI / 180.0;
	if (angle_rad < 0.0)
		angle_rad = -angle_rad; // Asegurar que el ángulo sea positivo para el coseno
	corrected_dist = ray.distance * ft_cos(angle_rad);
	if (corrected_dist <= 0.01)
		corrected_dist = 0.01;
	wall_height = (int)(RENDER_HEIGHT / corrected_dist) * 2;
	if (wall_height > RENDER_HEIGHT * 3)
		wall_height = RENDER_HEIGHT * 3;
	if (wall_height < 1)
		wall_height = 1;
	return wall_height;
}

void draw_column(t_game *game, int x, t_raycast ray, double ray_angle)
{
	int         wall_height;
	int         y;
	double		texture_iteration;
	int			render_start;
	double		texture_start;

	if (ray.type < 0 || ray.distance <= 0.0)
		return;
	wall_height = ft_calculate_wall_height(game, ray, x);
	if (wall_height <= 0)
		return;
	texture_iteration = RENDER_HEIGHT / (double)wall_height;

	if (wall_height > RENDER_HEIGHT)
		render_start = 0;
	else 
}


void ft_render_3d(t_game *game)
{
	int			i;
	double		angle_step;
	double		start_angle;
	double		current_angle;

	angle_step = FOV / RENDER_WIDTH;
	start_angle =  -(FOV / 2);

	draw_background(game);
	i = 0;
	while (i < RENDER_WIDTH)
	{
		current_angle = start_angle + i * angle_step;
		draw_column(game, RENDER_WIDTH - i, game->raycasts[i], current_angle);
		i++;
	}
}
