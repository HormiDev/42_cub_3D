#include "includes/cub_3d.h"

static int	parse_xpm_pixel_line(const char *line, t_texture *texture, t_xpm_color *xpm_palette,
	int char_per_pixel, int row)
	{
		char	pixel_chars[8];
		int		j;
		int		color_idx;
		
		j = 0; 
		while (j < texture->width)
		{
			ft_strncpy(pixel_chars, line + (j * char_per_pixel), char_per_pixel);
			pixel_chars[char_per_pixel] = '\0';
			color_idx = find_palette_color(xpm_palette, texture->size_colors, pixel_chars);
			if (color_idx < 0)
			return (-1);
		texture->colors[row * texture->width + j] = xpm_palette[color_idx].value;
		j++; 
	}
	return (0);
}


static int	read_xpm_pixels_file(t_file *file, t_texture *texture, t_xpm_color *xpm_palette,
		int char_per_pixel, int *line_idx)
{
	int		i;
	char	*line;
	char	*start;
	char	*end;

	i = 0;
	while (i < texture->height && *line_idx < file->lines)
	{
		line = file->array_content[*line_idx];
		start = ft_strchr(line, '"');
		end = ft_strrchr(line, '"');
		if (!start || !end || end <= start)
			return (-1);
		*end = '\0';
		start++;
		if (parse_xpm_pixel_line(start, texture, xpm_palette, char_per_pixel, i) < 0)
			return (-1);
		i++;
		(*line_idx)++;
	}
	if (i != texture->height)
		return (-1);
	return (0);
}

static int	load_xpm_header_and_palette(const char *xpm_path, t_texture *texture, int *char_per_pixel, int *line_idx, t_file **file, t_xpm_color **xpm_palette, t_list ***alloc_list_ptr)
{
	*file = ft_create_file_from_filename((char *)xpm_path);
	if (!*file)
	{
		ft_dprintf(2, "Error: No se pudo abrir el archivo XPM '%s'\n", xpm_path);
		return (-1);
	}
	*alloc_list_ptr = ft_get_alloc_lst(5);
	if (read_xpm_header_file(*file, texture, char_per_pixel, line_idx) < 0)
	{
		ft_dprintf(2, "Error: Formato XPM inesperado o archivo vacío.\n");
		ft_file_clear(file);
		ft_alloc_lst(0, 0);
		return -1;
	}
	*xpm_palette = (t_xpm_color *)ft_malloc_lst_e(*alloc_list_ptr,
			sizeof(t_xpm_color) * texture->size_colors);
	if (read_xpm_palette_file(*file, *xpm_palette, texture->size_colors, *char_per_pixel, *alloc_list_ptr, line_idx) < 0)
	{
		ft_dprintf(2, "Error: No se pudo leer la paleta de colores.\n");
		ft_file_clear(file);
		ft_alloc_lst(0, 0);
		return -1;
	}
	return 0;
}

static int	load_xpm_pixels_and_finish(t_file *file, t_texture *texture, t_xpm_color *xpm_palette, int char_per_pixel, int *line_idx, t_list **alloc_list_ptr)
{
	texture->colors = (unsigned int *)ft_malloc_lst_e(alloc_list_ptr,
			sizeof(unsigned int) * texture->width * texture->height);
	if (read_xpm_pixels_file(file, texture, xpm_palette, char_per_pixel, line_idx) < 0)
	{
		ft_dprintf(2, "Error: No se pudo leer los datos de píxeles.\n");
		ft_file_clear(&file);
		ft_alloc_lst(0, 0);
		return -1;
	}
	texture->pixels = NULL;
	ft_file_clear(&file);
	return 0;
}

int	extract_texture_from_xpm(const char *xpm_path, t_texture *texture)
{
	t_file		*file = NULL;
	int			char_per_pixel;
	t_xpm_color	*xpm_palette = NULL;
	t_list		**alloc_list_ptr = NULL;
	int			line_idx = 0;

	if (load_xpm_header_and_palette(xpm_path, texture, &char_per_pixel, &line_idx, &file, &xpm_palette, &alloc_list_ptr) < 0)
		return -1;
	if (load_xpm_pixels_and_finish(file, texture, xpm_palette, char_per_pixel, &line_idx, alloc_list_ptr) < 0)
		return -1;
	return 0;
}
/*
int main()
{
	t_texture my_texture;
	if (extract_texture_from_xpm("example.xpm", &my_texture) == 0)
	{
		printf("Textura XPM cargada exitosamente:\n");
		printf("  Ancho: %d\n", my_texture.width);
		printf("  Alto: %d\n", my_texture.height);
		printf("  Número de colores en la paleta: %d\n", my_texture.size_colors);
		printf("  Primer pixel (ARGB): 0x%08X\n", my_texture.colors[0]);

		// Leer un píxel en la coordenada (2, 3) como ejemplo
		double coordinate[2] = {2.0, 3.0};
		unsigned int pixel = get_texture_pixel(&my_texture, coordinate);
		printf("Pixel en (%d, %d): 0x%08X\n", (int)coordinate[0], (int)coordinate[1], pixel);
	}
	else
	{
		printf("Fallo al cargar la textura XPM.\n");
	}
	return 0;
}*/
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define WIN_W 640
#define WIN_H 480

// put_pixel básico para escribir en la imagen de MLX
void put_pixel(t_image *img, int x, int y, int color)
{
	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return;
	char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

// Crea una imagen compatible con MLX
void	init_screen_image(void *mlx, void *win, t_image *screen)
{
	screen->mlx_img = mlx_new_image(mlx, WIN_W, WIN_H);
	screen->addr = mlx_get_data_addr(screen->mlx_img, &screen->bpp,
									 &screen->line_len, &screen->endian);
	screen->width = WIN_W;
	screen->height = WIN_H;
	screen->mlx = mlx;
	screen->win = win;
}

int main(void)
{
	void		*mlx = mlx_init();
	void		*win = mlx_new_window(mlx, WIN_W, WIN_H, "draw_column test");
	t_image		screen;
	t_game		game;
	t_texture	textures[4]; // Podés tener más, pero uno basta para la prueba
	t_raycast	ray;

	// Inicializa screen
	init_screen_image(mlx, win, &screen);

	// Inicializa game
	game.width_height[0] = WIN_W;
	game.width_height[1] = WIN_H;

	// Carga textura (usa un archivo válido en ../../textures/)
	if (extract_texture_from_xpm("../../textures/wall.xpm", &textures[1]) < 0)
	{
		ft_printf_fd(2, "Error: no se pudo cargar la textura.\n");
		return 1;
	}

	// Prepara raycast
	ray.type = 1;              // Usa la textura 1
	ray.distance = 1.0;        // Pared cercana → pared alta
	ray.impact.x = 2.3;
	ray.impact.y = 1.5;

	// Dibuja columna en x = 320
	draw_column(&screen, textures, WIN_W / 2, ray, &game);

	// Muestra imagen en ventana
	mlx_put_image_to_window(mlx, win, screen.mlx_img, 0, 0);

	// Espera evento de cierre
	mlx_loop(mlx);

	return 0;
}