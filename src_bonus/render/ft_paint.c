/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 18:22:54 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/25 00:58:31 by ide-dieg         ###   ########.fr       */
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
			game->render->colors_matrix[y][x] = MIST_COLOR;
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

static t_texture *get_texture_for_ceiling(t_game *game, t_vector2 *pos)
{
	int texture_num;

	texture_num = ((int)pos->x + (int)pos->y) % game->length_textures_array[5];
	if (texture_num < 0)
		texture_num += game->length_textures_array[5];
	//ft_printf(" %d ", texture_num);
	return (game->arraytextures[5][texture_num]);
}

static t_texture *get_texture_for_floor(t_game *game, t_vector2 *pos)
{
	int texture_num;

	texture_num = ((int)pos->x + (int)pos->y) % game->length_textures_array[4];
	if (texture_num < 0)
		texture_num += game->length_textures_array[4];
	return (game->arraytextures[4][texture_num]);
}

static unsigned int get_fc_color(t_texture *texture, t_vector2 *pos)
{
    int tx;
    int ty;

    if (!texture->path) // Si la textura es un color sólido
        return (texture->texture_color);

    tx = (int)((texture->width - 1) * (pos->x - (int)(pos->x)));
    ty = (int)((texture->height - 1) * (pos->y - (int)(pos->y)));
    return (texture->colors_matrix[ty][tx]);
}

int ft_calculate_wall_height(t_raycast *ray, int x, t_game *game)
{
	//double	column_angle;
	double	corrected_dist;
	int		wall_height;

	corrected_dist = ray->distance * game->fish_eye_correction[x];
	if (corrected_dist <= 0.01)
		corrected_dist = 0.01;
	wall_height = (int)(RENDER_HEIGHT / corrected_dist) * RENDER_WIDTH / RENDER_HEIGHT * 1.275;
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
	int				height_mid;

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
		
		int ys = 0;
		int yf = RENDER_HEIGHT - 1;
		t_texture *ceiling_texture;
		t_texture *floor_texture;
		//ft_printf("Drawing ceiling and floor for column %d\n", x);
		while (ys < y)
		{
			//ft_printf("%d a", ys);
			ceiling_texture = get_texture_for_ceiling(game, &game->render_cloud[ys][x]);
			floor_texture = get_texture_for_floor(game, &game->render_cloud[ys][x]);
			//ft_printf("b");
			//game->render->colors_matrix[ys][x] = get_fc_color(ceiling_texture, &game->render_cloud[ys][x]);
			unsigned int ceiling_color = get_fc_color(ceiling_texture, &game->render_cloud[ys][x]);
			ft_mix_color(&game->render->colors_matrix[ys][x], &ceiling_color, game->mist_density_fc[ys]);
			//ft_printf("c");
			//game->render->colors_matrix[yf][x] = get_fc_color(floor_texture, &game->render_cloud[yf][x]);
			unsigned int floor_color = get_fc_color(floor_texture, &game->render_cloud[yf][x]);
			ft_mix_color(&game->render->colors_matrix[yf][x], &floor_color, game->mist_density_fc[ys]);
			//ft_printf("d\n");
			ys++;
			yf--;
		}
		
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
		height_mid = RENDER_HEIGHT / 2;
		while (y < height_mid)
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
		texture_start = texture->height / 2.0;
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

t_vector2 ft_rotate_vector2(t_vector2 *vec, double angle)
{
	t_vector2	result;
	double		cos_angle;
	double		sin_angle;

	cos_angle = ft_format_cos(angle);
	sin_angle = ft_format_sin(angle);
	result.x = vec->x * cos_angle - vec->y * sin_angle;
	result.y = vec->x * sin_angle + vec->y * cos_angle;
	return (result);
}

static void ft_render_cloud(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < RENDER_HEIGHT / 2)
	{
		j = 0;
		while (j < RENDER_WIDTH)
		{
			game->render_cloud[i][j] = ft_rotate_vector2(&game->prec_vector_cloud[i][j], game->player.rotation.x);
			game->render_cloud[i][j].y += game->player.position.y;
			game->render_cloud[i][j].x += game->player.position.x;
			j++;
		}
		i++;
	}
}

void ft_render_3d(t_game *game)
{
	int			i;

	draw_background(game);
	ft_render_cloud(game);
	i = 0;
	while (i < RENDER_WIDTH)
	{
		draw_column(game, RENDER_WIDTH - i - 1, &game->raycasts[i]);
		i++;
	}
	
}
