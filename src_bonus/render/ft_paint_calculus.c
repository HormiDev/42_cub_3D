/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paint_calculus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:45 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/10 00:35:20 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

int	ft_calculate_wall_height(t_raycast *ray, int x, t_game *game)
{
	double	corrected_dist;
	int		wall_height;

	corrected_dist = ray->distance * game->fish_eye_correction[x];
	if (corrected_dist <= 0.01)
		corrected_dist = 0.01;
	wall_height = (int)(game->config.render_height
			/ corrected_dist) * game->config.render_width
		/ game->config.render_height * 1.275;
	if (wall_height % 2 != 0)
		wall_height++;
	return (wall_height + 2);
}

int	ft_calc_texture_x(t_raycast *ray, t_texture *texture)
{
	int		texture_x;

	if (ray->type == WALL_NO
		|| ray->type == WALL_SO || ray->type == DOOR_NO
		|| ray->type == DOOR_SO)
	{
		texture_x
			= (int)((ray->impact.x - (int)ray->impact.x)
				* texture->width);
		if (ray->type == WALL_SO || ray->type == DOOR_SO)
			texture_x = texture->width - texture_x - 1;
	}
	else
	{
		texture_x
			= (int)((ray->impact.y - (int)ray->impact.y) * texture->width);
		if (ray->type == WALL_EA || ray->type == DOOR_EA)
			texture_x = texture->width - texture_x - 1;
	}
	return (texture_x);
}

t_vector2	ft_reposition_vector2(t_game *game, t_vector2 vec)
{
	t_vector2	result;
	double		cos_angle;
	double		sin_angle;

	cos_angle = ft_format_cos(game->player->rotation.x);
	sin_angle = ft_format_sin(game->player->rotation.x);
	result.x = vec.x * cos_angle - vec.y * sin_angle + game->player->position.x;
	result.y = vec.x * sin_angle + vec.y * cos_angle + game->player->position.y;
	return (result);
}

void	draw_ceiling_and_floor(t_game *game, int x, int wall_start)
{
	int				y;
	t_texture		*ceiling_texture;
	t_texture		*floor_texture;
	t_vector2		ceiling_floor;
	unsigned int	color;

	y = 0;
	while (y < wall_start)
	{
		ceiling_floor = ft_reposition_vector2(game,
				game->prec_vector_cloud[y][x]);
		ceiling_texture = get_texture_for_ceiling(game, &ceiling_floor);
		floor_texture = get_texture_for_floor(game, &ceiling_floor);
		color = get_fc_color(ceiling_texture, &ceiling_floor);
		ft_mix_color(&game->render->cmx[y][x],
			&color, game->mist_density_fc[y]);
		color = get_fc_color(floor_texture, &ceiling_floor);
		ft_mix_color(&game->render->cmx[game->config.render_height - 1 - y][x],
			&color, game->mist_density_fc[y]);
		y++;
	}
}
