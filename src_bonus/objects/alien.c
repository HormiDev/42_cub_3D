#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Inicializa el alien del juego.
 * 
 * Crea un alien con ruta de patrullaje definida.
 * ft_alloc_lst gestiona la memoria automaticamente.
 * 
 * @param game Puntero a la estructura principal del juego.
 */
static void	ft_init_alien_data(t_alien *alien, double x, double y)
{
	alien->position.x = x;
	alien->position.y = y;
	alien->state = ALIEN_IDLE;
	alien->size = 2.0;
}

void	ft_init_aliens(t_game *game)
{
	game->aliens = NULL;
}

void	ft_config_aliens(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'A')
			{
				game->aliens = ft_alloc_lst(sizeof(t_alien), 4);
				ft_init_alien_data((t_alien *)game->aliens, j + 0.5, i + 0.5);
				t_alien *alien = (t_alien *)game->aliens;
				alien->texture = ft_alloc_lst(sizeof(t_texture), 4);
				check_arguments_xpm("textures/alien.xpm");
				alien->texture->path = ft_strdup("textures/alien.xpm");
				alien->texture->img = (t_img *)mlx_xpm_file_to_image(game->mlx, alien->texture->path, &alien->texture->width, &alien->texture->height);
				if (!alien->texture->img)
				{
					ft_dprintf(2, RED "Error: Failed to load alien texture\n" RESET);
					ft_close_game(1);
				}
				alien->texture->colors_matrix = ft_alloc_lst(sizeof(unsigned int *) * alien->texture->height, 4);
				int k = 0;
				while (k < alien->texture->height)
				{
					alien->texture->colors_matrix[k] = (unsigned int *)(alien->texture->img->data + (k * sizeof(char) * 4 * alien->texture->width));
					k++;
				}
				game->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Actualiza el alien del juego.
 * 
 * @param game Puntero a la estructura principal del juego.
 */
void	ft_update_aliens(t_game *game)
{
	(void)game;
}

/**
 * @brief Encuentra el mejor angulo que minimiza el error de posicion.
 * 
 * @param dx Diferencia en X.
 * @param dy Diferencia en Y.
 * @param distance Distancia al alien.
 * @return Mejor angulo encontrado.
 */
static double	ft_find_best_angle(double dx, double dy, double distance)
{
	double	angle;
	double	step;
	double	test_cos;
	double	test_sin;
	double	best_angle;
	double	best_error;
	double	error;

	angle = 0;
	step = 0.1;
	best_angle = 0;
	best_error = 999999;
	while (angle < 360)
	{
		test_cos = ft_format_cos(angle) * distance;
		test_sin = ft_format_sin(angle) * distance;
		error = ft_sqrt((test_cos - dx) * (test_cos - dx)
			+ (test_sin - dy) * (test_sin - dy));
		if (error < best_error)
		{
			best_error = error;
			best_angle = angle;
		}
		angle += step;
	}
	return (best_angle);
}

/**
 * @brief Calcula el angulo del alien respecto al jugador.
 * 
 * @param player Posicion del jugador.
 * @param alien Posicion del alien.
 * @param player_angle Angulo de rotacion del jugador en grados.
 * @return Angulo relativo del alien.
 */
static double	ft_calc_alien_angle(t_vector2 player, t_vector2 alien,
	double player_angle)
{
	double	dx;
	double	dy;
	double	distance;
	double	best_angle;
	double	relative_angle;

	dx = alien.x - player.x;
	dy = alien.y - player.y;
	distance = ft_sqrt(dx * dx + dy * dy);
	if (distance < 0.001)
		return (0);
	best_angle = ft_find_best_angle(dx, dy, distance);
	relative_angle = best_angle - player_angle;
	while (relative_angle > 180)
		relative_angle -= 360;
	while (relative_angle <= -180)
		relative_angle += 360;
	return (relative_angle);
}

/**
 * @brief Dibuja el sprite del alien en la textura de renderizado.
 * 
 * @param game Puntero a la estructura principal del juego.
 * @param x Coordenada X inicial.
 * @param y Coordenada Y inicial.
 * @param width Ancho del sprite.
 * @param height Alto del sprite.
 * @param texture Textura del alien.
 * @param alien_distance Distancia del alien al jugador.
 */
static void	ft_draw_alien_sprite(t_game *game, int x, int y, int w, int h,
	t_texture *texture, double alien_distance)
{
	int	i;
	int	j;
	int	ray_index;
	int	tex_x;
	int	tex_y;

	i = 0;
	while (i < h && (y + i) < RENDER_HEIGHT)
	{
		if ((y + i) >= 0)
		{
			j = 0;
			while (j < w && (x + j) < RENDER_WIDTH
				&& (x + j) >= 0)
			{
				ray_index = RENDER_WIDTH - (x + j) - 1;
				if (ray_index >= 0 && ray_index < RENDER_WIDTH
					&& (alien_distance - 0.3) < game->raycasts[ray_index].distance)
				{
					tex_x = (j * texture->width) / w;
					tex_y = (i * texture->height) / h;
					if (tex_x < texture->width && tex_y < texture->height
						&& texture->colors_matrix[tex_y][tex_x] != 0xFFFFFF)
						game->render->colors_matrix[y + i][x + j] = texture->colors_matrix[tex_y][tex_x];
				}
				j++;
			}
		}
		i++;
	}
}

/**
 * @brief Renderiza el alien en la pantalla.
 * 
 * @param game Puntero a la estructura principal del juego.
 */
void	ft_render_aliens(t_game *game)
{
	t_alien	*alien;
	double	distance;
	double	angle;
	int		screen_x;
	int		size;

	if (!game->aliens)
		return ;
	alien = (t_alien *)game->aliens;
	distance = ft_vector_distance(game->player.position, alien->position);
	if (distance < 0.3 || distance > (MAX_RAY_SIZE - 0.5))
		return ;
	angle = ft_calc_alien_angle(game->player.position, alien->position,
			game->player.rotation.x);
	screen_x = (int)((FOV / 2.0 - angle) * RENDER_WIDTH / FOV);
	size = (int)((alien->size * RENDER_HEIGHT) / distance);
	if (size < 15)
		size = 15;
	if (size > RENDER_HEIGHT)
		size = RENDER_HEIGHT;
	ft_draw_alien_sprite(game, screen_x - size / 2,
		RENDER_HEIGHT / 2 - size / 2, size, size, alien->texture, distance);
}
