#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Convierte una coordenada horizontal normalizada a columna de pantalla.
 */
int	ft_projected_x_to_screen_col(double projected_x, int width)
{
	int	screen_col;

	screen_col = (int)(((projected_x + 1.0) * 0.5) * (double)width);
	if (screen_col < 0)
		return (0);
	if (screen_col >= width)
		return (width - 1);
	return (screen_col);
}

/**
 * @brief Proyecta un sprite a una columna de pantalla.
 */
int	ft_project_sprite_column(t_game *game, double dx, double dy)
{
	double	player_rot;
	double	sprite_ang;
	double	delta;

	player_rot = ft_normalize_angle(game->player->rotation.x);
	sprite_ang = ft_normalize_angle(atan2(dy, dx) * (180.0 / M_PI));
	delta = ft_normalize_angle(player_rot - sprite_ang);
	if (delta > 180.0)
		delta -= 360.0;
	if (ft_abs(delta) > (FOV * 0.5))
		return (-1);
	return (ft_projected_x_to_screen_col(delta / (FOV * 0.5),
			game->config.render_width));
}
