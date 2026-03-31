#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Convierte una coordenada horizontal normalizada a columna de pantalla.
 */
int	ft_projected_x_to_screen_col(double projected_x, int width)
{
	int	screen_col;

	screen_col = (int)(((projected_x + 1.0) * 0.5) * (double)width);
	return (screen_col);
}

/**
 * @brief Proyecta un sprite a una columna de pantalla.
 */
int	ft_project_sprite_column(t_game *game, double dx, double dy, double *distance)
{
	double	player_rot;
	double	sprite_ang;
	double	delta;
	double	delta_tmp;

	player_rot = ft_normalize_angle(game->player->rotation.x);
	sprite_ang = ft_normalize_angle(atan2(dy, dx) * (180.0 / M_PI));
	delta = ft_normalize_relative_angle(player_rot - sprite_ang);
	delta_tmp = delta;
	if (delta_tmp < 0)
		delta_tmp = delta_tmp * -1;
	*distance = *distance * ft_cos(delta_tmp);
	if (ft_abs(delta) > (FOV * 0.7))// agragar proteccion contra popeo lateral
		return (INT_MIN);
	return (ft_projected_x_to_screen_col(delta / (FOV * 0.5),
			game->config.render_width));
}
