#include "includes/cub_3d.h"

unsigned int hex_to_uint(const char *hex_str)
{
	unsigned int val = 0;
	while (*hex_str)
	{
		val <<= 4;
		if (*hex_str >= '0' && *hex_str <= '9')
			val |= *hex_str - '0';
		else if (*hex_str >= 'a' && *hex_str <= 'f')
			val |= *hex_str - 'a' + 10;
		else if (*hex_str >= 'A' && *hex_str <= 'F')
			val |= *hex_str - 'A' + 10;
		hex_str++;
	}
	return val;
}


static char *skip_whitespace(char *s)
{
	while (*s == ' ' || *s == '\t') 
		s++;
	return s;
}

static int	read_xpm_header_file(t_file *file, t_texture *texture, int *char_per_pixel, int *line_idx)
{
	char *line;
	char *start;
	char *end;

	while (*line_idx < file->lines)
	{
		line = file->array_content[*line_idx];
		if (ft_strchr(line, '"'))
			break;
		(*line_idx)++;
	}
	if (*line_idx >= file->lines)
		return (-1);
	line = file->array_content[*line_idx];
	start = ft_strchr(line, '"');
	end = ft_strrchr(line, '"');
	if (!start || !end || end <= start)
		return (-1);
	*end = '\0';
	start++;

	/*ESTO ME VOY A HACER MI VERSIÓN*/
	if (sscanf(start, "%d %d %d %d", &texture->width, &texture->height,
			&texture->size_colors, char_per_pixel) != 4)
		return (-1);
	(*line_idx)++;
	return (0);
}

static int	parse_palette_line(char *line, int char_per_pixel, t_xpm_color *color, t_list **alloc_list_ptr)
{
	char	*start = ft_strchr(line, '"');
	char	*end, *hex_start;
	unsigned int rgb_val;

	if (!start || !(end = ft_strrchr(line, '"')) || end <= start)
		return (-1);
	*end = '\0';
	start++;
	color->chars = (char *)ft_malloc_lst_e(alloc_list_ptr, char_per_pixel + 1);
	ft_strncpy(color->chars, start, char_per_pixel);
	color->chars[char_per_pixel] = '\0';
	hex_start = ft_strnstr(start + char_per_pixel, "#", ft_strlen(start + char_per_pixel));
	if (hex_start)
	{
		rgb_val = hex_to_uint(hex_start + 1);
		color->value = 0xFF000000 | rgb_val;
	}
	else if (ft_strnstr(start + char_per_pixel, "None", ft_strlen(start + char_per_pixel)))
		color->value = 0x00000000;
	else
		return (-1);
	return (0);
}

static int	read_xpm_palette_file(t_file *file, t_xpm_color *xpm_palette, int size_colors,
		int char_per_pixel, t_list **alloc_list_ptr, int *line_idx)
{
	int	i;

	i = 0;
	while (i < size_colors && *line_idx < file->lines)
	{
		if (parse_palette_line(file->array_content[*line_idx], char_per_pixel,
				&xpm_palette[i], alloc_list_ptr) < 0)
			return (-1);
		i++;
		(*line_idx)++;
	}
	if (i != size_colors)
		return (-1);
	return (0);
}

static int find_palette_color(t_xpm_color *xpm_palette, int size_colors, 
								const char *pixel_chars)
{
	int i = 0;

	while (i < size_colors)
	{
		if (ft_strncmp(pixel_chars, xpm_palette[i].chars, strlen(xpm_palette[i].chars)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	read_xpm_pixels_file(t_file *file, t_texture *texture, t_xpm_color *xpm_palette,
		int char_per_pixel, int *line_idx)
{
	int		i;
	int		j;
	char	*line;
	char	*start;
	char	*end;
	char	pixel_chars[8];
	int		color_idx;

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
		j = 0;
		while (j < texture->width)
		{
			ft_strncpy(pixel_chars, start + (j * char_per_pixel), char_per_pixel);
			pixel_chars[char_per_pixel] = '\0';
			color_idx = find_palette_color(xpm_palette, texture->size_colors, pixel_chars);
			if (color_idx < 0)
				return (-1);
			texture->colors[i * texture->width + j] = xpm_palette[color_idx].value;
			j++;
		}
		i++;
		(*line_idx)++;
	}
	if (i != texture->height)
		return (-1);
	return (0);
}

int	extract_texture_from_xpm(const char *xpm_path, t_texture *texture)
{
	t_file		*file;
	int			char_per_pixel;
	t_xpm_color	*xpm_palette;
	t_list		**alloc_list_ptr;
	int			line_idx = 0;
	int			ret = -1;

	file = ft_create_file_from_filename((char *)xpm_path);
	if (!file)
	{
		ft_dprintf(2, "Error: No se pudo abrir el archivo XPM '%s'\n", xpm_path);
		return (-1);
	}
	alloc_list_ptr = ft_get_alloc_lst(5);

	if (read_xpm_header_file(file, texture, &char_per_pixel, &line_idx) < 0)
	{
		ft_dprintf(2, "Error: Formato XPM inesperado o archivo vacío.\n");
		ft_file_clear(&file);
		ft_alloc_lst(0, 0);
		return -1;
	}

	xpm_palette = (t_xpm_color *)ft_malloc_lst_e(alloc_list_ptr,
			sizeof(t_xpm_color) * texture->size_colors);
	if (read_xpm_palette_file(file, xpm_palette, texture->size_colors, char_per_pixel, alloc_list_ptr, &line_idx) < 0)
	{
		ft_dprintf(2, "Error: No se pudo leer la paleta de colores.\n");
		ft_file_clear(&file);
		ft_alloc_lst(0, 0);
		return -1;
	}

	texture->colors = (unsigned int *)ft_malloc_lst_e(alloc_list_ptr,
			sizeof(unsigned int) * texture->width * texture->height);
	if (read_xpm_pixels_file(file, texture, xpm_palette, char_per_pixel, &line_idx) < 0)
	{
		ft_dprintf(2, "Error: No se pudo leer los datos de píxeles.\n");
		ft_file_clear(&file);
		ft_alloc_lst(0, 0);
		return -1;
	}
	texture->pixels = NULL;
	ret = 0;
	ft_file_clear(&file);
	return ret;
}

unsigned int get_texture_pixel(const t_texture *texture, int x, int y)
{
	if (!texture || !texture->colors)
		return 0;
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return 0;
	return texture->colors[y * texture->width + x];
}

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
		int x = 0, y = 0;
		unsigned int pixel = get_texture_pixel(&my_texture, x, y);
		printf("Pixel en (%d, %d): 0x%08X\n", y, x, pixel);
	}
	else
	{
		printf("Fallo al cargar la textura XPM.\n");
	}
	return 0;
}