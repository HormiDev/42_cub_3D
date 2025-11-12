/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:22:54 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/12 12:06:02 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief draw_background - Dibuja el fondo (techo y suelo) de la pantalla
 * @param game: Puntero a la estructura del juego
*/ 
void draw_background(t_game *game)
{
	int					x;
	int					y;
	
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
 * @brief get_texture_for_wall - Obtiene la textura correspondiente al tipo de pared
 * @param game: Puntero a la estructura del juego
 * @param wall_type: Tipo de pared (WALL_NO, WALL_SO, WALL_EA, WALL_WE)
 * @return Puntero a la textura o NULL si no se encuentra
 */
static t_texture *get_texture_for_wall(t_game *game, t_raycast *ray)
{
	if (ray->type == 0 || ray->type == 3)
		return (game->arraytextures[ray->type][((int)(ray->impact.x) + (int)(ray->impact.y)) % game->length_textures_array[ray->type]]);
	return(game->arraytextures[ray->type][game->length_textures_array[ray->type] - 1 - (((int)(ray->impact.x) + (int)(ray->impact.y)) % game->length_textures_array[ray->type])]);
}

int ft_calculate_wall_height(t_raycast *ray, int x, t_game *game)
{
	//double	column_angle;
	double	corrected_dist;
	int		wall_height;

	corrected_dist = ray->distance * game->fish_eye_correction[x];
	if (corrected_dist <= 0.01)
		corrected_dist = 0.01;
	wall_height = (int)(RENDER_HEIGHT / corrected_dist) * RENDER_WIDTH / RENDER_HEIGHT;
	/*
	if (wall_height > RENDER_HEIGHT * 3)
		wall_height = RENDER_HEIGHT * 3;
	if (wall_height < 1)
		wall_height = 1;
	*/
	if (wall_height % 2 != 0)
		wall_height--;
	return wall_height;
}

int ft_calc_texture_x(t_raycast *ray, t_texture *texture)
{
	int texture_x;

	if (ray->type == WALL_NO || ray->type == WALL_SO)
	{
		texture_x = (int)((ray->impact.x - (int)ray->impact.x) * texture->width);
		if (ray->type == WALL_SO)
			texture_x = texture->width - texture_x - 1; // Invertir para el sur
	}
	else
	{
		texture_x = (int)((ray->impact.y - (int)ray->impact.y) * texture->width);
		if (ray->type == WALL_EA)
			texture_x = texture->width - texture_x - 1; // Invertir para el este
	}
	return texture_x;
}

void draw_column(t_game *game, int x, t_raycast *ray)
{
	int				wall_height;
	int				y;
	double			texture_iteration;
	int				render_end;
	double			texture_start;
	int				texture_x;
	t_texture		*texture;
	int				mist_density;
	int				last_texture_pixel;

	if (ray->type < 0 || ray->type > 3 || ray->distance <= 0.0)
		return;
	wall_height = ft_calculate_wall_height(ray, x, game);
	if (wall_height <= 0)
		return;
	texture = get_texture_for_wall(game, ray);
	texture_iteration = (double)texture->height / (double)wall_height;
	if (wall_height > RENDER_HEIGHT)
	{
		y = 0;
		render_end = RENDER_HEIGHT - 1;
		texture_start = (double)((wall_height - RENDER_HEIGHT) / 2.0) / (double)wall_height * (double)texture->height;
	}
	else
	{
		y = (RENDER_HEIGHT - wall_height) / 2;
		render_end = y + wall_height - 1;
		texture_start = 0.0;
	}
	mist_density = -(ray->distance / MAX_RAY_SIZE * 100) + 100;
	last_texture_pixel = -1;
	if (texture->path == NULL) // Si la textura es un color sólido
	{
		ft_mix_color(&game->render->colors_matrix[y++][x], &texture->texture_color, mist_density);
		while (y < render_end)
		{
			//ft_mix_color_precalc(&game->render->colors_matrix[y][x], &texture->texture_color, mist_density, game);
			game->render->colors_matrix[y][x] = game->render->colors_matrix[y - 1][x];
			y++;
		}
	}
	else
	{
		texture_x = ft_calc_texture_x(ray, texture);
		while (y < render_end)
		{
			if (last_texture_pixel == (int)texture_start)
			{
				game->render->colors_matrix[y][x] = game->render->colors_matrix[y - 1][x];
			}
			else
			{
				//ft_mix_color_precalc(&game->render->colors_matrix[y][x], &texture->colors_matrix[(int)texture_start][texture_x], mist_density, game);
				ft_mix_color(&game->render->colors_matrix[y][x], &texture->colors_matrix[(int)texture_start][texture_x], mist_density);
				last_texture_pixel = (int)texture_start;
			}
			texture_start += texture_iteration;
			y++;
		}
	}
}


void ft_render_3d(t_game *game)
{
	int			i;

	draw_background(game);
	i = 0;
	while (i < RENDER_WIDTH)
	{
		draw_column(game, RENDER_WIDTH - i - 1, &game->raycasts[i]);
		i++;
	}
	
}
