/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nirmata <nirmata@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:22:54 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/06 22:58:38 by nirmata          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d.h"

/**
 * @brief draw_background - Dibuja el fondo (techo y suelo) de la pantalla
 * @param game: estructura del juego
 */
void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < RENDER_HEIGHT)
	{
		x = 0;
		while (x < RENDER_WIDTH)
		{
			if (y < RENDER_HEIGHT / 2)
				game->render->cmx[y][x] = game->ceiling_tex->texture_color;
			else
				game->render->cmx[y][x] = game->floor_tex->texture_color;
			x++;
		}
		y++;
	}
}

/**
 * @brief get_texture_for_wall
	- Obtiene la textura correspondiente al tipo de pared
 * @param game: estructura del juego
 * @param wall_type: Tipo de pared (WALL_NO, WALL_SO, WALL_EA, WALL_WE)
 * @return textura o NULL si no se encuentra
 */
t_texture	*get_texture_for_wall(t_game *game, t_raycast *ray)
{
	if (ray->type == 0 || ray->type == 3)
		return (game->arraytextures[ray->type][((int)(ray->impact.x)
			+ (int)(ray->impact.y)) % game->larraytex[ray->type]]);
	return (game->arraytextures[ray->type][game->larraytex[ray->type] - 1
		- (((int)(ray->impact.x) + (int)(ray->impact.y))
			% game->larraytex[ray->type])]);
}

int	ft_calculate_wall_height(t_raycast *ray, int x)
{
	double	angle_rad;
	double	corrected_dist;
	double	wall_height_calc;
	double	height_ratio;
	int		wall_height;

	angle_rad = ((double)x / (double)RENDER_WIDTH * FOV) - (FOV / 2.0);
	if (angle_rad < 0.0)
		angle_rad = -angle_rad;
	corrected_dist = ray->distance * ft_cos(angle_rad);
	if (corrected_dist <= 0.01)
		corrected_dist = 0.01;
	height_ratio = (double)RENDER_WIDTH / (double)RENDER_HEIGHT;
	wall_height_calc = RENDER_HEIGHT / corrected_dist;
	wall_height = (int)(wall_height_calc * height_ratio);
	if (wall_height % 2 != 0)
		wall_height--;
	return (wall_height);
}

int	ft_calc_texture_x(t_raycast *ray, t_texture *texture)
{
	int	texture_x;

	if (ray->type == WALL_NO || ray->type == WALL_SO)
	{
		texture_x = (int)((ray->impact.x - (int)ray->impact.x)
				* texture->width);
		if (ray->type == WALL_SO)
			texture_x = texture->width - texture_x - 1;
	}
	else
	{
		texture_x = (int)((ray->impact.y - (int)ray->impact.y)
				* texture->width);
		if (ray->type == WALL_EA)
			texture_x = texture->width - texture_x - 1;
	}
	return (texture_x);
}
