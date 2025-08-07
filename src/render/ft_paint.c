#include "../../includes/cub_3d.h"
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
	
	// Valores por defecto si los colores no están configurados
	if (game->ceiling_color[0] == 0 && game->ceiling_color[1] == 0 && game->ceiling_color[2] == 0)
	{
		game->ceiling_color[0] = 135; // Azul cielo
		game->ceiling_color[1] = 206;
		game->ceiling_color[2] = 235;
	}
	if (game->floor_color[0] == 0 && game->floor_color[1] == 0 && game->floor_color[2] == 0)
	{
		game->floor_color[0] = 139; // Marrón tierra
		game->floor_color[1] = 69;
		game->floor_color[2] = 19;
	}
	
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
				ft_draw_pixel_in_img(game->img_map->img, x, y, ceiling_color);
			else
				ft_draw_pixel_in_img(game->img_map->img, x, y, floor_color);
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

 
void draw_column(t_game *game, int x, t_raycast ray, double ray_angle)
{
	int         wall_height;
	int         draw_start;
	int         draw_end;
	int         win_height;
	int         y;
	int         wall_color;

	(void)ray_angle;

	if (!game || x < 0 || x >= WINDOW_WIDTH)
		return;
	
	if (ray.type < 0 || ray.distance <= 0.0)
		return;

	win_height = WINDOW_HEIGHT;
	if (win_height <= 0)
		return;

	double fov = 45.0; 
	double column_angle = ((double)x / (double)WINDOW_WIDTH - 0.5) * fov;
	double angle_rad = column_angle * M_PI / 180.0;

	double corrected_dist = ray.distance * cos(angle_rad);
	
	if (corrected_dist <= 0.01)
		corrected_dist = 0.01;

	wall_height = (int)(win_height / corrected_dist);
	
	if (wall_height > win_height * 3)
		wall_height = win_height * 3;
	if (wall_height < 1)
		wall_height = 1;

	get_draw_limits(wall_height, win_height, &draw_start, &draw_end);
	
	//intensidad dependiendo distancia
	if (ray.type == WALL_NO)
		wall_color = 0xFF0000;
	else if (ray.type == WALL_SO)
		wall_color = 0x00FF00;
	else if (ray.type == WALL_EA)
		wall_color = 0x0000FF;
	else if (ray.type == WALL_WE)
		wall_color = 0xFFFFFF;
	else
		wall_color = 0xFFFF00;

	y = draw_start;
	while (y <= draw_end && y < WINDOW_HEIGHT)
	{
		if (y >= 0)
			ft_draw_pixel_in_img(game->img_map->img, x, y, wall_color);
		y++;
	}
}


void ft_render_3d(t_game *game)
{
	int ray_count = WINDOW_HEIGHT;
	double fov = 45.0; 
	int i;

	if (!game || !game->raycasts)
		return;

	draw_background(game);

	i = 0;
	while (i < ray_count)
	{
		double angle_offset = ((double)i / (double)ray_count - 0.5) * fov;
		double current_angle = game->player.rotation.x + angle_offset;
		
		int screen_x = (i * WINDOW_WIDTH) / ray_count;
	
		if (game->raycasts[i].distance > 0.0 && game->raycasts[i].type >= 0)
		{
			draw_column(game, screen_x, game->raycasts[i], current_angle);
			
			int next_x = ((i + 1) * WINDOW_WIDTH) / ray_count;
			int x = screen_x + 1;
			while (x < next_x && x < WINDOW_WIDTH)
			{
				draw_column(game, x, game->raycasts[i], current_angle);
				x++;
			}
		}
		
		i++;
	}
}
