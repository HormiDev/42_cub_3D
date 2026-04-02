/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flamethrower_hud.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 16:22:20 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/02 16:36:40 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

void	ft_render_flamethrower_hud(t_game *game, int player_index)
{
    t_player_actions	*actions;
    t_vector_int		pos;
    char				str_charges[32];
    char				str_cooldown[32];

    actions = &game->actions[player_index];
    
    pos.x = game->render->width - (game->render->width / 3);
    pos.y = 10;
    ft_sprintf(str_charges, "CHARGES:%d / 3", actions->flamethrower_charges);
    ft_draw_string_hud(game->render, game->font, str_charges, &pos, 1);
    
    if (actions->flamethrower_cooldown_remaining > 0)
    {
        pos.x = game->render->width - (game->render->width / 3);
        pos.y = 25;
        ft_sprintf(str_cooldown, "COOLDOWN:%ds", 
            (int)actions->flamethrower_cooldown_remaining);
        ft_draw_string_hud(game->render, game->font, str_cooldown, &pos, 1);
    }
}
