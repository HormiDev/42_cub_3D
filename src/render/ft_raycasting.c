#include "../../includes/cub_3d.h"

/**
 * @brief Inicializa las variables necesarias para el raycasting.
 * @param game Puntero a la estructura del juego.
 * @param angle Ángulo del rayo a normalizar.
 * @param ray Estructura del rayo a inicializar.
 * @param init_data Array para almacenar datos iniciales [tile_x, tile_y, cuadrant].
 * @param sin_cos Array para almacenar sin y cos del ángulo.
 */
static void	ft_init_raycast_data(t_game *game, double *angle, t_raycast *ray, 
								int init_data[3], double sin_cos[2])
{
	// Normalizar ángulo entre 0 y 360 grados
	if (*angle < 0)
		*angle += 360;
	else if (*angle >= 360)
		*angle -= 360;
	
	// Determinar cuadrante y ajustar ángulo
	init_data[2] = 0; // cuadrante
	while (*angle >= 90)
	{
		*angle -= 90;
		init_data[2]++;
	}
	
	// Inicializar estructuras
	ft_bzero(ray, sizeof(t_raycast));
	init_data[0] = (int)game->player.position.x; // tile_x
	init_data[1] = (int)game->player.position.y; // tile_y
	sin_cos[0] = ft_sin(*angle);
	sin_cos[1] = ft_cos(*angle);
}

/**
 * @brief Procesa la colisión cuando el rayo impacta una pared vertical.
 * @param game Puntero a la estructura del juego.
 * @param ray Estructura del rayo donde almacenar el resultado.
 * @param distances Array con distancias [x, y].
 * @param data Array con datos [tile_x, tile_y, cuadrante].
 * @param max_size Tamaño máximo del rayo.
 * @return 1 si se encontró colisión, 0 si no.
 */
static int	ft_process_vertical_collision(t_game *game, t_raycast *ray,
										double distances[2], int data[3], double max_size)
{
	ft_ray_iter_up(data, data[2], 1);
	if (game->map[data[1]][data[0]] == '1')
	{
		ft_rotate_to_cuadrant(data[2], &distances[0], &distances[1]);
		ft_calc_ray_position(ray, &(game->player.position), distances[0], distances[1]);
		ft_ray_type(ray, data[2], 0);
		if (ray->distance > max_size)
			ft_raycast_max_size(game, 0, ray, max_size, data[2]);
		return (1);
	}
	return (0);
}

/**
 * @brief Procesa la colisión cuando el rayo impacta una pared horizontal.
 * @param game Puntero a la estructura del juego.
 * @param ray Estructura del rayo donde almacenar el resultado.
 * @param distances Array con distancias [x, y].
 * @param data Array con datos [tile_x, tile_y, cuadrante].
 * @param max_size Tamaño máximo del rayo.
 * @return 1 si se encontró colisión, 0 si no.
 */
static int	ft_process_horizontal_collision(t_game *game, t_raycast *ray,
										double distances[2], int data[3], double max_size)
{
	ft_ray_iter_right(data, data[2], 1);
	if (game->map[data[1]][data[0]] == '1')
	{
		ft_rotate_to_cuadrant(data[2], &distances[0], &distances[1]);
		ft_calc_ray_position(ray, &(game->player.position), distances[0], distances[1]);
		ft_ray_type(ray, data[2], 1);
		if (ray->distance > max_size)
			ft_raycast_max_size(game, 0, ray, max_size, data[2]);
		return (1);
	}
	return (0);
}

/**
 * @brief Realiza el raycasting para detectar colisiones con paredes en el mapa.
 * @param game Puntero a la estructura del juego.
 * @param angle Ángulo en el que se dispara el rayo.
 * @param ray Puntero a la estructura t_raycast donde se almacenará el resultado.
 * @param max_size Tamaño máximo permitido para el rayo.
 */
void ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size)
{
	int			data[3];		// [tile_x, tile_y, cuadrante]
	t_vector2	distance;
	double		sin_cos[2];		// [sin, cos]
	double		aux_distance;
	double		distances[2];	// [x, y] para pasar a funciones

	ft_init_raycast_data(game, &angle, ray, data, sin_cos);
	
	while (1)
	{
		ft_calc_distance(data[2], data, game->player.position, &distance);
		aux_distance = sin_cos[1] * (distance.y / sin_cos[0]);
		
		if (aux_distance < distance.x)
		{
			if (distance.x > max_size + 1)
			{
				ft_raycast_max_size(game, angle, ray, max_size, data[2]);
				break;
			}
			distances[0] = aux_distance;
			distances[1] = distance.y;
			if (ft_process_vertical_collision(game, ray, distances, data, max_size))
				break;
		}
		else
		{
			aux_distance = sin_cos[0] * (distance.x / sin_cos[1]);
			if (distance.y > max_size + 1)
			{
				ft_raycast_max_size(game, angle, ray, max_size, data[2]);
				break;
			}
			distances[0] = distance.x;
			distances[1] = aux_distance;
			if (ft_process_horizontal_collision(game, ray, distances, data, max_size))
				break;
		}
	}
}
