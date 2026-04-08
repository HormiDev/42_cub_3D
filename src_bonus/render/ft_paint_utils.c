/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:45 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/08 02:36:08 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

/**
 * @brief draw_background - Dibuja el fondo (techo y suelo) de la pantalla
 * @param game: estructura del juego
*/ 
void draw_background(t_game *game)
{
	int					x;
	int					y;
	
	y = 0;
	while (y < game->config.render_height)
	{
		x = 0;
		while (x < game->config.render_width)
		{
			game->render->cmx[y][x] = MIST_COLOR;
			x++;
		}
		y++;
	}
}

/**
 * @brief get_texture_for_wall - Obtiene la textura correspondiente al tipo de pared
 * @param game: estructura del juego
 * @param wall_type: Tipo de pared (WALL_NO, WALL_SO, WALL_EA, WALL_WE)
 * @return textura o NULL si no se encuentra
 */
t_texture	*get_texture_for_wall(t_game *game, t_raycast *ray)
{
	if (ray->type == WALL_NO || ray->type == WALL_WE)
		return (game->arraytextures[ray->type][((int)(ray->impact.x)
			+ (int)(ray->impact.y)) % game->larraytex[ray->type]]);
	else if (ray->type == WALL_SO || ray->type == WALL_EA)
		return(game->arraytextures[ray->type][game->larraytex[ray->type]
			- 1 - (((int)(ray->impact.x) + (int)(ray->impact.y))
				% game->larraytex[ray->type])]);
	return (game->arraytextures[6][0]);
}

t_texture *get_texture_for_ceiling(t_game *game, t_vector2 *pos)
{
	int		texture_num;

	texture_num = ((int)pos->x + (int)pos->y) % game->larraytex[5];
	if (texture_num < 0)
		texture_num += game->larraytex[5];
	return (game->arraytextures[5][texture_num]);
}

t_texture	*get_texture_for_floor(t_game *game, t_vector2 *pos)
{
	int	texture_num;

	texture_num = ((int)pos->x + (int)pos->y) % game->larraytex[4];
	if (texture_num < 0)
		texture_num += game->larraytex[4];
	return (game->arraytextures[4][texture_num]);
}

unsigned int	get_fc_color(t_texture *texture, t_vector2 *pos)
{
    int		tx;
    int		ty;

	if (!texture->path)
		return (texture->texture_color);
	tx = (int)((texture->width) * (pos->x - (int)(pos->x)));
	ty = (int)((texture->height) * (pos->y - (int)(pos->y)));
	return (texture->cmx[ty][tx]);
}
