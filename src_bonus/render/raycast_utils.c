#include "../../includes/cub_3d_bonus.h"

long ft_long_diff(long a, long b) // llevar a la libft
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int ft_int_diff(int a, int b) // llevar a la libft
{
	if (a > b)
		return (a - b);
	return (b - a);
}

int ft_int_max(int a, int b) // llevar a la libft
{
	if (a > b)
		return a;
	return b;
}

/**
 * @brief Dibuja una línea en la imagen del mapa.
 *
 * Esta función dibuja una línea entre dos puntos en la imagen del mapa utilizando el algoritmo de Bresenham.
 * Se utiliza para representar rayos o líneas de visión en el mapa.
 *
 * @param game Puntero a la estructura del juego que contiene la imagen del mapa.
 * @param start Punto de inicio de la línea.
 * @param end Punto final de la línea.
 * @param color Color de la línea a dibujar.
 */
void ft_draw_line_in_image(t_game *game, t_vector2 start, t_vector2 end, int color)
{
	t_vector2 pixel;
	int steps;
	int i;
	t_vector2 increment;

	steps = ft_int_max(ft_int_diff(start.x, end.x), ft_int_diff(start.y, end.y));
	i = 0;
	pixel.x = start.x;
	pixel.y = start.y;
	increment.x = (start.x - end.x) / steps;
	increment.y = (start.y - end.y) / steps;
	while (i <= steps)
	{
		ft_draw_pixel_in_img(game->img_map->img, (int)pixel.x, (int)pixel.y, color);
		pixel.x -= increment.x;
		pixel.y -= increment.y;
		i++;
	}
}

/**
 * @brief Calcula la diferencia absoluta entre dos números de tipo double.
 *
 * Esta función devuelve la diferencia absoluta entre dos números de tipo double.
 * Se utiliza para calcular distancias y diferencias en coordenadas.
 *
 * @param a Primer número.
 * @param b Segundo número.
 * @return La diferencia absoluta entre a y b.
 */
double ft_double_diff(double a, double b)
{
	if (a > b)
		return (a - b);
	return (b - a);
}

/**
 * @brief Calcula la distancia entre dos puntos en un espacio bidimensional.
 *
 * Esta función calcula la distancia euclidiana entre dos puntos representados por estructuras t_vector2.
 * Se utiliza para determinar la distancia entre el jugador y un impacto de rayo.
 *
 * @param a Primer punto (vector).
 * @param b Segundo punto (vector).
 * @return La distancia entre los puntos a y b.
 */
double ft_vector_distance(t_vector2 a, t_vector2 b)
{
	t_vector2 diff;

	diff.x = ft_double_diff(a.x, b.x);
	diff.y = ft_double_diff(a.y, b.y);
	return ft_sqrt(pow(diff.x, 2) + pow(diff.y, 2));
}