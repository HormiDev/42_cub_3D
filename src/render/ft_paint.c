#include "../../includes/cub_3d.h"

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
static double	get_tex_x(const t_raycast *ray, const t_texture *tex)
{
	double	tex_x;

	if (ray->type == 0 || ray->type == 1)
		tex_x = ray->impact.x - floor(ray->impact.x);
	else
		tex_x = ray->impact.y - floor(ray->impact.y);
	tex_x *= tex->width;
	if (ray->type == 2 || ray->type == 0)
		tex_x = tex->width - tex_x - 1;
	return tex_x;
}

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
static void	draw_texture_column(t_image *screen, t_texture *tex, int x, int draw_start, int draw_end, double tex_x, int wall_height, int win_height)
{
	double	step = (double)tex->height / wall_height;
	double	tex_pos = (draw_start - win_height / 2 + wall_height / 2) * step;
	int		y;

	for (y = draw_start; y < draw_end; y++)
	{
		int tex_y = (int)tex_pos;
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		int color = tex->pixels[tex_y][(int)tex_x];
		put_pixel(screen, x, y, color);
	}
}
/**
 * @brief draw_column - Dibuja una columna de pared en la pantalla usando datos de raycasting.
 * @param screen: Puntero al buffer de imagen de la pantalla.
 * @param textures: Arreglo de texturas para los diferentes tipos de pared.
 * @param x: Coordenada x en la pantalla donde se dibuja la columna.
 * @param ray: Estructura de resultado del raycasting para la columna actual.
 * @param game: Puntero a la estructura de estado del juego.
 */
void draw_column(t_image *screen, t_texture *textures, int x, t_raycast ray, t_game *game)
{
	int         wall_height;
	int         draw_start;
	int         draw_end;
	double      tex_x;
	t_texture   *tex;
	int         win_height = game->width_height[1];

	tex = &textures[ray.type];
	wall_height = (int)(win_height / ray.distance);
	get_draw_limits(wall_height, win_height, &draw_start, &draw_end);
	tex_x = get_tex_x(&ray, tex);
	draw_texture_column(screen, tex, x, draw_start, draw_end, tex_x, wall_height, win_height);
}
