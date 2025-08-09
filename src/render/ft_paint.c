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

 
/**
 * @brief get_texture_for_wall - Obtiene la textura correspondiente al tipo de pared
 * @param game: Puntero a la estructura del juego
 * @param wall_type: Tipo de pared (WALL_NO, WALL_SO, WALL_EA, WALL_WE)
 * @return Puntero a la textura o NULL si no se encuentra
 */
static t_texture *get_texture_for_wall(t_game *game, int wall_type)
{
	t_list *texture_list;
	
	if (!game || wall_type < 0 || wall_type > 3)
		return (NULL);
		
	texture_list = game->textures[wall_type];
	if (!texture_list || !texture_list->content)
		return (NULL);
		
	return ((t_texture *)texture_list->content);
}

/**
 * @brief get_texture_color - Obtiene el color de un píxel específico de la textura
 * @param texture: Puntero a la textura
 * @param tex_x: Coordenada X en la textura
 * @param tex_y: Coordenada Y en la textura
 * @return Color del píxel o color por defecto si hay error
 */
static unsigned int get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	int color_index;
	static int call_count = 0;
	
	if (!texture || !texture->pixels || !texture->colors)
	{
		return (0xFFFF00); // Amarillo por defecto si no hay textura
	}
		
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height)
	{
		return (0xFFFF00);
	}
		
	if (!texture->pixels[tex_y])
	{
		printf("DEBUG: pixels[%d] is null\n", tex_y);
		return (0xFFFF00);
	}
		
	color_index = texture->pixels[tex_y][tex_x];
	if (color_index < 0 || color_index >= texture->size_colors)
	{
		printf("DEBUG: color_index out of bounds - color_index=%d, size_colors=%d\n", 
			color_index, texture->size_colors);
		return (0xFFFF00);
	}
	
	unsigned int final_color = texture->colors[color_index];
	
	// Debug para las primeras 5 llamadas solamente
	if (call_count < 5)
	{
		printf("TEXTURE_COLOR %d: tex_pos=(%d,%d), color_idx=%d, final_color=0x%08X\n", 
			call_count, tex_x, tex_y, color_index, final_color);
		call_count++;
	}
		
	return (final_color);
}

void draw_column(t_game *game, int x, t_raycast ray, double ray_angle)
{
	int         wall_height;
	int         draw_start;
	int         draw_end;
	int         win_height;
	int         y;
	t_texture   *texture;
	int         tex_x;
	unsigned int pixel_color;
	static int debug_count = 0;

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
	
	// Obtener la textura correspondiente al tipo de pared
	texture = get_texture_for_wall(game, ray.type);
	
	// Calcular coordenada X en la textura basada en la posición del impacto del rayo
	tex_x = 0; // Valor por defecto
	if (texture)
	{
		// Usar la posición fraccionaria del impacto para mapear a la textura
		double wall_hit;
		
		// Dependiendo de la orientación de la pared, usar X o Y
		if (ray.type == WALL_NO || ray.type == WALL_SO)
		{
			// Paredes horizontales - usar coordenada X
			wall_hit = ray.impact.x - floor(ray.impact.x);
		}
		else
		{
			// Paredes verticales - usar coordenada Y
			wall_hit = ray.impact.y - floor(ray.impact.y);
		}
		
		tex_x = (int)(wall_hit * texture->width);
		
		// Asegurar que tex_x esté en rango válido
		if (tex_x >= texture->width)
			tex_x = texture->width - 1;
		if (tex_x < 0)
			tex_x = 0;
			
		// Debug para las primeras llamadas
		if (debug_count < 5)
		{
			printf("DEBUG %d: wall_type=%d, impact=(%.2f,%.2f), wall_hit=%.2f, tex_x=%d, texture_size=%dx%d\n", 
				debug_count, ray.type, ray.impact.x, ray.impact.y, wall_hit, tex_x, texture->width, texture->height);
			debug_count++;
		}
	}

	y = draw_start;
	while (y <= draw_end && y < WINDOW_HEIGHT)
	{
		if (y >= 0)
		{
			if (texture)
			{
				// Calcular coordenada Y en la textura
				double d = y - win_height / 2 + wall_height / 2;
				int tex_y = (int)((d * texture->height) / wall_height);
				
				// Asegurar que tex_y esté en rango válido
				if (tex_y >= texture->height)
					tex_y = texture->height - 1;
				if (tex_y < 0)
					tex_y = 0;
					
				// TEMPORAL: get_texture_color retorna color fijo para testing
				pixel_color = get_texture_color(texture, tex_x, tex_y);
			}
			else
			{
				// Colores por defecto si no hay textura cargada
				if (ray.type == WALL_NO)
					pixel_color = 0xFF0000;
				else if (ray.type == WALL_SO)
					pixel_color = 0x00FF00;
				else if (ray.type == WALL_EA)
					pixel_color = 0x0000FF;
				else if (ray.type == WALL_WE)
					pixel_color = 0xFFFFFF;
				else
					pixel_color = 0xFFFF00;
			}
			
			ft_draw_pixel_in_img(game->img_map->img, x, y, pixel_color);
		}
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
