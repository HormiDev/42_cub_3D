#include "../../includes/cub_3d.h"

void ft_draw_pixel_3d(t_game *game, int x, int y, int color)
{
	char *pixel;
	if (!game || !game->img_map || !game->img_map->img_data)
		return;
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		pixel = game->img_map->img_data + (y * game->img_map->image_len + x * (game->img_map->bits_pixel / 8));
		*(unsigned int *)pixel = color;
	}
}

/**
 * @brief draw_background - Dibuja el fondo (techo y suelo) de la pantalla
 * @param game: Puntero a la estructura del juego
*/
 
void draw_background(t_game *game)
{
	int x, y;
	int ceiling_color, floor_color;
	
	if (!game)
		return;
	
	// Convertir colores RGB a formato de pixel
	ceiling_color = (game->ceiling_color[0] << 16) | 
					(game->ceiling_color[1] << 8) | 
					game->ceiling_color[2];
	floor_color = (game->floor_color[0] << 16) | 
				  (game->floor_color[1] << 8) | 
				  game->floor_color[2];
	
	// Dibujar el fondo píxel por píxel
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				ft_draw_pixel_3d(game, x, y, ceiling_color);
			else
				ft_draw_pixel_3d(game, x, y, floor_color);
			x++;
		}
		y++;
	}
}

/**
 * @brief get_draw_limits - Calcula las posiciones de inicio y fin para dibujar una columna de pared.
 * @param wall_height: Altura de la porción de pared a dibujar.
 * @param win_height: Altura de la ventana o pantalla.
 * @param draw_start: Puntero donde se almacena la coordenada y inicial de dibujo.
 * @param draw_end: Puntero donde se almacena la coordenada y final de dibujo.
 */
static void	get_draw_limits(int wall_height, int win_height, int *draw_start, int *draw_end)
{
	*draw_start = -wall_height / 2 + win_height / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	*draw_end = wall_height / 2 + win_height / 2;
	if (*draw_end >= win_height)
		*draw_end = win_height - 1;
}
/**
 * @brief get_tex_x - Calcula la coordenada x en la textura para el impacto actual de la pared.
 * @param ray: Puntero a la estructura de resultado del raycasting.
 * @param tex: Puntero a la estructura de textura.
 * @return La coordenada x en la textura a muestrear.
 */
/*
static double	get_tex_x(const t_raycast *ray, const t_texture *tex)
{
	double	tex_x;

	if (!tex || tex->width <= 0)
		return (0.0);
	if (ray->type == 0 || ray->type == 1)
		tex_x = ray->impact.x - floor(ray->impact.x);
	else
		tex_x = ray->impact.y - floor(ray->impact.y);
	tex_x *= tex->width;
	if (ray->type == 2 || ray->type == 0)
		tex_x = tex->width - tex_x - 1;
	// Asegurar que tex_x esté dentro de los límites válidos
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return tex_x;
}*/


/**
 * @brief draw_texture_column - Dibuja una columna vertical de la textura en la pantalla.
 * @param screen: Puntero al buffer de imagen de la pantalla.
 * @param tex: Puntero a la textura desde la que se dibuja.
 * @param x: Coordenada x en la pantalla donde se dibuja la columna.
 * @param draw_start: Coordenada y inicial para dibujar.
 * @param draw_end: Coordenada y final para dibujar.
 * @param tex_x: Coordenada x en la textura a muestrear.
 * @param wall_height: Altura de la porción de pared a dibujar.
 * @param win_height: Altura de la ventana o pantalla.
 */

/*static void	draw_texture_column(t_game *game, t_texture *tex, int x, int draw_start, int draw_end, double tex_x, int wall_height, int win_height)
{
	int		y;
	double  step; 
	double	tex_pos;
	int		tex_y;
	int		color;

	// Validaciones de seguridad
	if (!game || !tex || !tex->pixels || tex->width <= 0 || tex->height <= 0)
		return;
	if (x < 0 || x >= WINDOW_WIDTH)
		return;
	if (draw_start >= draw_end)
		return;
	if (tex_x < 0 || tex_x >= tex->width)
		return;

	step = (double)tex->height / wall_height;
	tex_pos = (draw_start - win_height / 2 + wall_height / 2) * step;
	y = draw_start;
	
	// Asegurar que y esté dentro de los límites de la pantalla
	if (y < 0)
		y = 0;
	if (draw_end > WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT;

	while (y < draw_end && y < WINDOW_HEIGHT)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		
		// Clamp tex_y a los límites válidos de la textura
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		
		// Verificar que los índices de la textura sean válidos
		if (tex->pixels[tex_y] && (int)tex_x < tex->width)
		{
			color = tex->pixels[tex_y][(int)tex_x];
			ft_draw_pixel_3d(game, x, y, color);
		}
		y++;
	}
}*/


/**
 * @brief draw_column - Dibuja una columna de pared en la pantalla usando datos de raycasting.
 * @param screen: Puntero al buffer de imagen de la pantalla.
 * @param textures: Arreglo de texturas para los diferentes tipos de pared.
 * @param x: Coordenada x en la pantalla donde se dibuja la columna.
 * @param ray: Estructura de resultado del raycasting para la columna actual.
 * @param game: Puntero a la estructura de estado del juego.
 */
 
void draw_column(t_game *game, int x, t_raycast ray, double ray_angle)
{
	int         wall_height;
	int         draw_start;
	int         draw_end;
	int         win_height;
	int         y;
	int         wall_color;

	if (!game || x < 0 || x >= WINDOW_WIDTH)
		return;
	
	if (ray.type < 0)
		return;

	win_height = WINDOW_HEIGHT;
	if (win_height <= 0)
		return;

	// Corrección del ángulo para evitar distorsión tipo "fish-eye"
	double angle_diff = ray_angle - game->player.rotation.x;
	
	// Normalizar diferencia de ángulo
	while (angle_diff < -180.0)
		angle_diff += 360.0;
	while (angle_diff > 180.0)
		angle_diff -= 360.0;

	// Aplicar corrección de distorsión coseno
	double corrected_dist = ray.distance * cos(angle_diff * M_PI / 180.0);
	if (corrected_dist <= 0.001)
		corrected_dist = 0.001;

	wall_height = (int)(win_height / corrected_dist);

	get_draw_limits(wall_height, win_height, &draw_start, &draw_end);
	
	if (ray.type == WALL_NO)
		wall_color = 0xFF4444; // Rojo
	else if (ray.type == WALL_SO)
		wall_color = 0x44FF44; // Verde
	else if (ray.type == WALL_EA)
		wall_color = 0x4444FF; // Azul
	else if (ray.type == WALL_WE)
		wall_color = 0xFFFFFF; // Blanco
	else
		wall_color = 0xFFFF44; // Amarillo


	// Dibujar la columna con color sólido
	y = draw_start;
	while (y <= draw_end && y < WINDOW_HEIGHT)
	{
		if (y >= 0)
			ft_draw_pixel_3d(game, x, y, wall_color);
		y++;
	}
}


void ft_render_3d(t_game *game)
{
	int ray_count = WINDOW_HEIGHT;
	double fov = 45.0;
	double angle_step = fov / (double)ray_count;
	double start_angle = game->player.rotation.x - (fov / 2.0);
	int i;

	// Validación básica
	if (!game || !game->raycasts)
		return;

	// 0. Dibujar fondo (techo y suelo) PRIMERO
	draw_background(game);

	// 1. Dibujo 3D principal usando raycasts ya calculados
	i = 0;
	while (i < ray_count)
	{
		double current_angle = start_angle + i * angle_step;
		// Calcular la columna correspondiente en pantalla
		int screen_x = (i * WINDOW_WIDTH) / ray_count;
		int column_width = WINDOW_WIDTH / ray_count;
		if (column_width < 1) column_width = 1;

		// Dibujar múltiples columnas si la resolución es baja
		int j = 0;
		while (j < column_width && screen_x + j < WINDOW_WIDTH)
		{
			draw_column(game, screen_x + j, game->raycasts[i], current_angle);
			j++;
		}
		i++;
	}
}
