#include "../../includes/cub_3d.h"

/**
 * @brief Itera la posición del rayo hacia arriba o abajo según el cuadrante.
 *
 * Esta función ajusta la posición del rayo en el eje Y dependiendo del cuadrante
 * en el que se encuentre. Se utiliza para avanzar el rayo en la dirección correcta.
 *
 * @param position_xy Puntero a un array que contiene las coordenadas X e Y del rayo.
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param iter Valor de iteración para avanzar el rayo.
 */
void ft_ray_iter_up(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[1] += iter;
	else if (cuadrant == 1)
		position_xy[0] -= iter;
	else if (cuadrant == 2)
		position_xy[1] -= iter;
	else
		position_xy[0] += iter;
}

/**
 * @brief Itera la posición del rayo hacia la derecha o izquierda según el cuadrante.
 *
 * Esta función ajusta la posición del rayo en el eje X dependiendo del cuadrante
 * en el que se encuentre. Se utiliza para avanzar el rayo en la dirección correcta.
 *
 * @param position_xy Puntero a un array que contiene las coordenadas X e Y del rayo.
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param iter Valor de iteración para avanzar el rayo.
 */
void ft_ray_iter_right(int *position_xy, int cuadrant, int iter)
{
	if (cuadrant == 0)
		position_xy[0] += iter;
	else if (cuadrant == 1)
		position_xy[1] += iter;
	else if (cuadrant == 2)
		position_xy[0] -= iter;
	else
		position_xy[1] -= iter;
}

/**
 * @brief Calcula la distancia desde la posición del jugador hasta el tile del rayo.
 *
 * Esta función calcula la distancia en los ejes X e Y desde la posición del jugador
 * hasta el tile donde impacta el rayo, dependiendo del cuadrante en el que se encuentre.
 *
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param tile_ray_xy Array que contiene las coordenadas X e Y del tile del rayo.
 * @param player_position Posición actual del jugador.
 * @param distance Puntero a una estructura t_vector2 donde se almacenarán las distancias calculadas.
 */
void ft_calc_distance(int cuadrant, int *tile_ray_xy, t_vector2 player_position, t_vector2 *distance)
{
	if (cuadrant == 0)
	{
		distance->x = tile_ray_xy[0] + 1 - player_position.x;
		distance->y = tile_ray_xy[1] + 1 - player_position.y;
	}
	else if (cuadrant == 1)
	{
		distance->x = tile_ray_xy[1] + 1 - player_position.y;
		distance->y = player_position.x - tile_ray_xy[0];
	}
	else if (cuadrant == 2)
	{
		distance->x = player_position.x - tile_ray_xy[0];
		distance->y = player_position.y - tile_ray_xy[1];
	}
	else
	{
		distance->x = player_position.y - tile_ray_xy[1];
		distance->y = tile_ray_xy[0] + 1 - player_position.x;
	}
}

/**
 * @brief Rota las distancias del rayo al cuadrante correspondiente.
 *
 * Esta función ajusta las distancias en los ejes X e Y según el cuadrante en el que se encuentre el rayo.
 * Se utiliza para asegurar que las distancias se calculen correctamente en función de la dirección del rayo.
 *
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param distance_x Puntero a la distancia en el eje X.
 * @param distance_y Puntero a la distancia en el eje Y.
 */
void ft_rotate_to_cuadrant(int cuadrant, double *distance_x, double *distance_y)
{
	double aux_distance_x;

	aux_distance_x = *distance_x;
	if (cuadrant == 0)
		return ;
	else if (cuadrant == 1)
	{
		*distance_x = -(*distance_y);
		*distance_y = aux_distance_x;
	}
	else if (cuadrant == 2)
	{
		*distance_x = -(*distance_x);
		*distance_y = -(*distance_y);
	}
	else
	{
		*distance_x = *distance_y;
		*distance_y = -aux_distance_x;
	}
}

/**
 * @brief Calcula la posición del impacto del rayo.
 *
 * Esta función calcula la posición del impacto del rayo en el mapa, sumando las distancias
 * calculadas a la posición del jugador. También calcula la distancia total desde el jugador
 * hasta el impacto.
 *
 * @param ray Puntero a la estructura t_raycast donde se almacenará el resultado.
 * @param player_position Posición actual del jugador.
 * @param distance_x Distancia en el eje X al impacto.
 * @param distance_y Distancia en el eje Y al impacto.
 */
void ft_calc_ray_position(t_raycast *ray, t_vector2 *player_position, double distance_x, double distance_y)
{
	ray->impact.x = player_position->x + distance_x;
	ray->impact.y = player_position->y + distance_y;
	ray->distance = ft_vector_distance(*player_position, ray->impact);
}

/**
 * @brief Asigna el tipo de pared al rayo según el cuadrante y la dirección.
 *
 * Esta función determina el tipo de pared (Norte, Sur, Este, Oeste) en función del cuadrante
 * y si el rayo se mueve hacia arriba/derecha o hacia abajo/izquierda.
 *
 * @param ray Puntero a la estructura t_raycast donde se almacenará el tipo de pared.
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 * @param up_right Indica si el rayo se mueve hacia arriba/derecha (0) o hacia abajo/izquierda (1).
 */
void ft_ray_type(t_raycast *ray, int cuadrant, int up_right)
{
	if (up_right == 0)
	{
		if (cuadrant == 0)
			ray->type = WALL_NO;
		else if (cuadrant == 1)
			ray->type = WALL_WE;
		else if (cuadrant == 2)
			ray->type = WALL_SO;
		else
			ray->type = WALL_EA;
	}
	else
	{
		if (cuadrant == 0)
			ray->type = WALL_EA;
		else if (cuadrant == 1)
			ray->type = WALL_NO;
		else if (cuadrant == 2)
			ray->type = WALL_WE;
		else
			ray->type = WALL_SO;
	}
}

/**
 * @brief Calcula el impacto del rayo cuando se alcanza el tamaño máximo.
 *
 * Esta función calcula la posición de impacto del rayo en el mapa cuando se alcanza
 * el tamaño máximo permitido. Se utiliza para evitar que el rayo se extienda más allá
 * de los límites establecidos.
 *
 * @param game Puntero a la estructura del juego que contiene la información del jugador.
 * @param angle Ángulo del rayo.
 * @param ray Puntero a la estructura t_raycast donde se almacenará el resultado.
 * @param max_size Tamaño máximo permitido para el rayo.
 * @param cuadrant Cuadrante actual del rayo (0, 1, 2 o 3).
 */
void ft_raycast_max_size(t_game *game, double angle, t_raycast *ray, double max_size, int cuadrant)
{
	t_vector2	distance;
	double		sin_cos[2];

	sin_cos[0] = ft_cos(angle);
	sin_cos[1] = ft_sin(angle);
	distance.x = sin_cos[0] * max_size;
	distance.y = sin_cos[1] * max_size;
	ft_rotate_to_cuadrant(cuadrant, &distance.x, &distance.y);
	ray->impact.x = game->player.position.x + distance.x;
	ray->impact.y = game->player.position.y + distance.y;
	ray->distance = max_size;
	ray->type = -1;
}



/**
 * @brief Dibuja el jugador en el mapa.
 *
 * Esta función dibuja un círculo rojo en la posición del jugador en el mapa.
 * También puede dibujar líneas que representan la dirección del jugador, aunque
 * esta funcionalidad está comentada actualmente.
 *
 * @param game Puntero a la estructura del juego que contiene la información del jugador.
 */
void ft_draw_player(t_game *game)
{
	int px;
	int py;
	//t_vector2 front;
	//t_vector2 right;
	//t_vector2 left;
	//double angle;
	
	px = (int)(game->player.position.x * TILE_MAP_SIZE);
	py = (int)(game->player.reverse_y_position * TILE_MAP_SIZE);
	ft_draw_circle(game, px, py, C_RED);
	/*
	angle = game->player.rotation.x;
	if (angle < 0)
		angle += 360;
	else if (angle >= 360)
		angle -= 360;
	while (angle > 90)
		angle -= 90;

	
	front.x = ft_cos((game->player.rotation.x)) * TILE_MAP_SIZE / 3 + px;
	front.y = -ft_sin((game->player.rotation.x)) * TILE_MAP_SIZE / 3 + py;
	right.x = ft_cos((game->player.rotation.x + 90)) * TILE_MAP_SIZE / 7 + px;
	right.y = -ft_sin((game->player.rotation.x + 90)) * TILE_MAP_SIZE / 7 + py;
	left.x = ft_cos((game->player.rotation.x - 90)) * TILE_MAP_SIZE / 7 + px;
	left.y = -ft_sin((game->player.rotation.x - 90)) * TILE_MAP_SIZE / 7 + py;
	ft_draw_line_in_image(game, left, front, C_RED);
	ft_draw_line_in_image(game, right, front, C_RED);
	ft_draw_line_in_image(game, (t_vector2){px, py}, front, C_RED);*/
}

/**
 * @brief Dibuja un rayo en el mapa.
 *
 * Esta función dibuja una línea en el mapa que representa el rayo lanzado desde la posición del jugador.
 * El color del rayo depende del tipo de pared con la que impacta.
 *
 * @param game Puntero a la estructura del juego que contiene la información del jugador y los raycasts.
 * @param ray Puntero a la estructura t_raycast que contiene la información del rayo.
 */
void ft_draw_raycast(t_game *game, t_raycast *ray)
{
	int color;

	if (ray->type == WALL_NO)
		color = C_GREEN;
	else if (ray->type == WALL_SO)
		color = C_YELLOW;
	else if (ray->type == WALL_EA)
		color = C_BLUE;
	else if (ray->type == WALL_WE)
		color = C_RED;
	else
		color = C_WHITE;

	ft_draw_line_in_image(game, (t_vector2){game->player.position.x * TILE_MAP_SIZE, game->player.reverse_y_position * TILE_MAP_SIZE},
		(t_vector2){ray->impact.x * TILE_MAP_SIZE, (-ray->impact.y + game->width_height[1]) * TILE_MAP_SIZE}, color);
}

/**
 * @brief Dibuja el mapa del juego.
 *
 * Esta función recorre el mapa y dibuja cada tile según su tipo (pared, espacio vacío, etc.).
 * También dibuja los raycasts y el jugador en el mapa, así como líneas que representan
 * los bordes del mapa y la posición del ratón.
 *
 * @param game Puntero a la estructura del juego que contiene la información del mapa y el jugador.
 */
void ft_draw_map(t_game *game)
{
	int			x;
	int			y;
	int			ry;
	int			i;

	y = 0;
	ry = game->width_height[1] - 1;
	while (y < game->width_height[1])
	{
		x = 0;
		while (x < game->width_height[0])
		{
			if (game->map[y][x] == '1')
				ft_draw_sq(game, x * TILE_MAP_SIZE, ry * TILE_MAP_SIZE, C_WHITE);
			else if (game->map[y][x] == '0')
				ft_draw_sq(game, x * TILE_MAP_SIZE, ry * TILE_MAP_SIZE, C_GREY);
			else if (game->map[y][x] == ' ')
				ft_draw_sq(game, x * TILE_MAP_SIZE, ry * TILE_MAP_SIZE, C_BLACK);
			x++;
		}
		y++;
		ry--;
	}
	
	i = 0;
	while (i < RENDER_WIDTH)
	{
		if (i % 10 == 0)
			ft_draw_raycast(game, &game->raycasts[i]);
		i++;
	}
	ft_draw_player(game);
	ft_draw_grid_horizontal(game, C_BLUE);
	ft_draw_grid_vertical(game, C_BLUE);
	ft_draw_line_in_image(game, (t_vector2){0, 0}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){0, game->width_height[1] * TILE_MAP_SIZE}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){game->width_height[0] * TILE_MAP_SIZE, 0}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
	ft_draw_line_in_image(game, (t_vector2){game->width_height[0] * TILE_MAP_SIZE, game->width_height[1] * TILE_MAP_SIZE}, (t_vector2){game->mouse_xy[0], game->mouse_xy[1]}, C_RED);
}
