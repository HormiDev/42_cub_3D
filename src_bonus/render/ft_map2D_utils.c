/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2D_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:25:45 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/07 22:07:56 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static void	ft_draw_minimap_point(t_game *game, t_vector2 world_pos,
    int radius, int color)
{
    t_vector2		screen;
    t_vector_int	p;
    t_vector_int	d;
    int				cx;
    int				cy;

    screen = ft_world_corner_to_screen(game, world_pos.x, world_pos.y);
    cx = (int)screen.x;
    cy = (int)screen.y;
    p.y = cy - radius;
    while (p.y <= cy + radius)
    {
        p.x = cx - radius;
        while (p.x <= cx + radius)
        {
            d.x = p.x - cx;
            d.y = p.y - cy;
            if (d.x * d.x + d.y * d.y <= radius * radius
                && p.x >= 0 && p.x < game->minimap->width
                && p.y >= 0 && p.y < game->minimap->height)
                ft_draw_pixel_in_img(game->minimap->img, p.x, p.y, color);
            p.x++;
        }
        p.y++;
    }
}

static void	ft_draw_minimap_alien_x(t_game *game, t_vector2 world_pos)
{
    t_vector2		center;
    int				size;

    center = ft_world_corner_to_screen(game, world_pos.x, world_pos.y);
    size = 4;
    ft_draw_line_minimap(game, (t_vector2){center.x - size, center.y - size},
        (t_vector2){center.x + size, center.y + size}, C_RED);
    ft_draw_line_minimap(game, (t_vector2){center.x + size, center.y - size},
        (t_vector2){center.x - size, center.y + size}, C_RED);
}

void	ft_draw_minimap_doors(t_game *game)
{
    int			my;
    int			mx;
    int			visible_range;

    visible_range = (int)(MAX_RAY_SIZE * 1.4);
    my = (int)game->player->position.y - visible_range;
    while (my <= (int)game->player->position.y + visible_range)
    {


        mx = (int)game->player->position.x - visible_range;
        while (mx <= (int)game->player->position.x + visible_range)
        {
            if (mx >= 0 && mx < game->width_height[0]
                && my >= 0 && my < game->width_height[1]
                && game->map[my][mx] == 'D')
                ft_draw_tile_edges(game, mx, my, C_YELLOW);
            mx++;
        }
        my++;
    }
}

void	ft_draw_objects(t_game *game)
{
	int	i;

	i = 0; 
	while (i < game->config.n_players)
	{
		 if (game->players[i].active && game->players[i].alive
            && &game->players[i] != game->player)
        {
            if (game->players[i].type == ENTITY_ALIEN)
                ft_draw_minimap_alien_x(game, game->players[i].position);
            else if (game->players[i].type == ENTITY_PLAYER)
                ft_draw_minimap_point(game, game->players[i].position, 2, C_ALIEN_PLAYER);
        }
        i++;
	}
}