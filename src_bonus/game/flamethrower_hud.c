#include "../../includes/cub_3d_bonus.h"

void	ft_render_flamethrower_hud(t_game *game, int player_index)
{
    t_player_actions	*actions;
    t_vector_int		pos;
    char				str_charges[32];
    char				str_cooldown[32];

    actions = &game->actions[player_index];
    
    // Mostrar cargas
    pos.x = 10;
    pos.y = 10;
    ft_sprintf(str_charges, "CHARGES:%d/3", actions->flamethrower_charges);
    ft_draw_string_hud(game->render, game->font, str_charges, &pos, 1);
    
    if (actions->flamethrower_cooldown_remaining > 0)
    {
        pos.x = 10;
        pos.y = 30;
        ft_sprintf(str_cooldown, "COOLDOWN:%.1fs", 
            actions->flamethrower_cooldown_remaining);
        ft_draw_string_hud(game->render, game->font, str_cooldown, &pos, 1);
    }
}