#include "../../includes/cub_3d_bonus.h"

/**
 * @brief Inicializa los datos del alien en su posición inicial.
 *
 * Coloca al alien en el centro del tile (x+0.5, y+0.5) y establece
 * sus parámetros por defecto: estado IDLE, velocidad, distancias de
 * persecución y patrullaje, y tamaño.
 *
 * @param alien Puntero al alien a inicializar.
 * @param x Posición X inicial en el mapa.
 * @param y Posición Y inicial en el mapa.
 */
static void	ft_init_alien_data(t_alien *alien, double x, double y)
{
	alien->position.x = x;
	alien->position.y = y;
	alien->state = ALIEN_IDLE;
	alien->speed = 1.2;
	alien->chase_distance = 4.0;
	alien->patrol_distance = 6.0;
	alien->current_patrol = 0;
	alien->patrol_count = 0;
	alien->size = 2.0;
}

/**
 * @brief Carga la textura del alien desde disco.
 *
 * Valida el archivo XPM y carga la textura del alien usando ft_loading_texture.
 * Si la carga falla, termina el juego con código de error.
 *
 * @param game Puntero a la estructura del juego.
 * @param alien Puntero al alien que recibirá la textura.
 */
static void	ft_load_alien_texture(t_game *game, t_alien *alien)
{
	check_arguments_xpm("textures/alien.xpm");
	alien->texture = ft_loading_texture(game->mlx, "textures/alien.xpm");
	if (!alien->texture)
	{
		ft_dprintf(2, RED "Error: Failed to load alien texture\n" RESET);
		ft_close_game(1);
	}
}

/**
 * @brief Crea un alien en la posición especificada del mapa.
 *
 * Reserva memoria para el alien, lo inicializa con sus datos por defecto,
 * carga su textura y reemplaza la marca 'A' del mapa por un espacio vacío '0'.
 *
 * @param game Puntero a la estructura del juego.
 * @param x Coordenada X en el mapa donde spawneará el alien.
 * @param y Coordenada Y en el mapa donde spawneará el alien.
 */
static void	ft_spawn_alien(t_game *game, int x, int y)
{
	game->aliens = ft_alloc_lst(sizeof(t_alien), 4);
	ft_init_alien_data((t_alien *)game->aliens, x + 0.5, y + 0.5);
	ft_load_alien_texture(game, (t_alien *)game->aliens);
	game->map[y][x] = '0';
}

/**
 * @brief Busca y configura aliens en el mapa.
 *
 * Recorre todo el mapa buscando la marca 'A' que indica la posición de un alien.
 * Al encontrarla, llama a ft_spawn_alien para crear el alien y termina la búsqueda.
 *
 * @param game Puntero a la estructura del juego.
 */
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
				ft_spawn_alien(game, j, i);
				return ;
			}
			j++;
		}
		i++;
	}
}

/**
 * @brief Actualiza el estado del alien según su distancia al jugador.
 *
 * Calcula la distancia entre el alien y el jugador. Si está dentro del rango
 * de persecución, cambia su estado a CHASE; de lo contrario, lo deja en IDLE.
 *
 * @param game Puntero a la estructura del juego.
 */
void	ft_update_aliens(t_game *game)
{
	t_alien	*alien;
	double	distance;

	if (!game->aliens)
		return ;
	alien = (t_alien *)game->aliens;
	distance = ft_vector_distance(game->player->position, alien->position);
	if (distance <= alien->chase_distance)
		alien->state = ALIEN_CHASE;
	else
		alien->state = ALIEN_IDLE;
}

/**
 * @brief Calcula los ejes de cámara (forward y right) a partir de la rotación.
 *
 * Convierte el yaw del jugador (en grados) a dos vectores ortonormales
 * en espacio mundo:
 *  - view_dir: dirección hacia donde mira la cámara (forward)
 *  - view_right: eje "derecha" de la cámara (perpendicular a view_dir)
 *
 * ¿Para qué?: la proyección de sprites necesita una base de cámara estable
 * para transformar un vector mundo (dx,dy) a espacio cámara (x lateral,
 * z delante) sin usar atan2, y coherente con el convenio del raycast
 * (X=cos, Y=sin).
 *
 * @param game Puntero al juego (contiene la rotación del jugador).
 * @param view_dir Vector de salida con la dirección de vista (forward).
 * @param view_right Vector de salida con el eje derecha de cámara.
 */
static void	ft_get_camera_axes(t_game *game, t_vector2 *view_dir,
	t_vector2 *view_right)
{
	double	rotation;

	rotation = ft_normalize_angle(game->player->rotation.x);
	view_dir->x = ft_format_cos(rotation);
	view_dir->y = ft_format_sin(rotation);
	view_right->x = view_dir->y;
	view_right->y = -view_dir->x;
}


/**
 * @brief Convierte una coordenada horizontal normalizada a columna de pantalla.
 *
 * Recibe una X proyectada en Coordenadas Normalizadas de Dispositivo (NDC):
 *  - projected_x = -1 equivale al borde izquierdo
 *  - projected_x =  0 equivale al centro de pantalla
 *  - projected_x = +1 equivale al borde derecho
 *
 * ¿Para qué?: el render de sprites necesita una columna en píxeles para
 * colocar el billboard (screen_x) y para que el enmascarado por profundidad
 * indexe el rayo correcto.
 *
 * @param projected_x Coordenada NDC en el rango [-1, 1].
 * @param width Ancho de render en píxeles.
 * @return Columna de pantalla clamped a [0, width-1].
 */
static int	ft_projected_x_to_screen_col(double projected_x, int width)
{
	int	screen_col;

	screen_col = (int)(((projected_x + 1.0) * 0.5) * (double)width);
	if (screen_col < 0)
		return (0);
	if (screen_col >= width)
		return (width - 1);
	return (screen_col);
}


/**
 * @brief Proyecta un vector mundo (dx,dy) a una columna de pantalla.
 *
 * Proyecta el vector desde el jugador hasta el sprite a espacio cámara:
 *  - camera_z es la profundidad "hacia delante" (debe ser > 0 para ser visible)
 *  - camera_x es el desplazamiento lateral
 *
 * Usando tan(FOV/2) comprueba si el sprite está dentro del FOV horizontal.
 * Si lo está, convierte camera_x/(camera_z*tan(FOV/2)) a una columna
 * en el rango [0, render_width-1].
 *
 * ¿Para qué?: frente a escanear todas las columnas del raycast, esto es O(1),
 * estable con el movimiento, evita atan2 y mantiene el mismo convenio que
 * el motor de raycast.
 *
 * @param game Puntero al juego (para rotación y render_width).
 * @param dx pos.x - player.x.
 * @param dy pos.y - player.y.
 * @return Columna de pantalla o -1 si está detrás del jugador o fuera del FOV.
 */
static int	ft_project_sprite_column(t_game *game, double dx, double dy)
{
	t_vector2	view_dir;
	t_vector2	view_right;
	double		camera_x;
	double		camera_z;
	double		tan_half_fov;
	double		cos_half_fov;

	ft_get_camera_axes(game, &view_dir, &view_right);
	camera_x = dx * view_right.x + dy * view_right.y;
	camera_z = dx * view_dir.x + dy * view_dir.y;
	if (camera_z <= 0.001)
		return (-1);
	cos_half_fov = ft_cos(FOV / 2.0);
	if (cos_half_fov < 0.000001)
		return (-1);
	tan_half_fov = ft_sin(FOV / 2.0) / cos_half_fov;
	if (tan_half_fov <= 0.000001)
		return (-1);
	if (camera_x > camera_z * tan_half_fov
		|| camera_x < -camera_z * tan_half_fov)
		return (-1);
	return (ft_projected_x_to_screen_col(camera_x / (camera_z * tan_half_fov),
			game->config.render_width));
}

/**
 * @brief Oculta columnas del sprite que están detrás de paredes.
 *
 * Compara la distancia del alien con la distancia de cada rayo (pared) en el
 * raycast. Si el alien está más lejos que la pared en esa columna, marca
 * los píxeles correspondientes como transparentes para simular oclusión.
 *
 * @param game Puntero a la estructura del juego.
 * @param scaled Textura escalada del sprite a enmascarar.
 * @param screen_x Posición X inicial del sprite en pantalla.
 * @param alien_distance Distancia del alien al jugador.
 */
static void	ft_mask_alien_by_depth(t_game *game, t_texture *scaled,
	int screen_x, double alien_distance)
{
	int	x;
	int	ray_index;
	int	y;

	x = 0;
	while (x < scaled->width)
	{
		ray_index = game->config.render_width - (screen_x + x) - 1;
		if (screen_x + x < 0 || screen_x + x >= game->config.render_width
			|| ray_index < 0 || ray_index >= game->config.render_width
			|| (alien_distance - 0.3)
			>= game->raycasts[ray_index].distance)
		{
			y = 0;
			while (y < scaled->height)
			{
				scaled->colors_matrix[y][x] = 0x00FFFFFF;
				y++;
			}
		}
		x++;
	}
}

/**
 * @brief Calcula el tamaño del sprite en pantalla según la distancia.
 *
 * Aplica proyección en perspectiva para escalar el sprite inversamente
 * proporcional a la distancia. Limita el resultado entre un tamaño mínimo
 * (MIN_ALIEN_SIZE) y el alto de la pantalla.
 *
 * @param game Puntero a la estructura del juego.
 * @param base_size Tamaño base del sprite en el mundo.
 * @param distance Distancia del sprite al jugador.
 * @return Tamaño del sprite en píxeles.
 */
static int	ft_compute_sprite_size(t_game *game, double base_size,
	double distance)
{
	int	size;

	size = (int)((base_size * game->config.render_height) / distance);
	if (size < MIN_ALIEN_SIZE)
		size = MIN_ALIEN_SIZE;
	if (size > game->config.render_height)
		size = game->config.render_height;
	return (size);
}

/**
 * @brief Obtiene los datos de una entidad según su tipo.
 *
 * Recupera la posición, tamaño base y textura de un sprite (alien o jugador).
 * Valida que la entidad exista y sea renderizable antes de devolver sus datos.
 *
 * @param game Puntero a la estructura del juego.
 * @param kind Tipo de sprite (SPRITE_ALIEN o SPRITE_PLAYER1-4).
 * @param pos Puntero de salida para la posición de la entidad.
 * @param base_size Puntero de salida para el tamaño base.
 * @param tex Puntero de salida para la textura de la entidad.
 * @return 1 si la entidad es válida y tiene textura, 0 en caso contrario.
 */
static int	ft_get_entity_data(t_game *game, t_sprite_kind kind,
	t_vector2 *pos, double *base_size, t_texture **tex)
{
	if (kind == SPRITE_ALIEN)
	{
		if (!game->aliens)
			return (0);
		*pos = game->aliens->position;
		*base_size = game->aliens->size;
		*tex = game->aliens->texture;
		return (*tex != NULL);
	}
	if (kind >= SPRITE_PLAYER1 && kind <= SPRITE_PLAYER4)
	{
		if ((int)(kind - SPRITE_PLAYER1) >= game->config.n_players)
			return (0);
		*pos = game->players[kind - SPRITE_PLAYER1].position;
		*base_size = 2.0;
		if (game->aliens)
			*tex = game->aliens->texture;
		else
			*tex = NULL;
		return (*tex != NULL);
	}
	return (0);
}

/**
 * @brief Renderiza un sprite (alien o jugador) usando técnica billboard.
 *
 * Calcula la posición y tamaño del sprite en pantalla según su distancia
 * al jugador. Escala la textura, aplica enmascaramiento por profundidad
 * para ocultar partes detrás de paredes, y dibuja el sprite con transparencia.
 *
 * @param game Puntero a la estructura del juego.
 * @param kind Tipo de sprite a renderizar (alien o jugador).
 */
void	ft_render_objects(t_game *game, t_sprite_kind kind)
{
	t_alien_draw	draw;
	t_vector2		pos;
	t_texture		*tex;
	double			distance;
	int				screen_col;
	t_vector2		diff;
	double			base_size;

	if (!ft_get_entity_data(game, kind, &pos, &base_size, &tex))
		return ;
	distance = ft_vector_distance(game->player->position, pos);
	if (distance < 0.3 || distance > (MAX_RAY_SIZE - 0.5))
		return ;
	diff.x = pos.x - game->player->position.x;
	diff.y = pos.y - game->player->position.y;
	(void)distance;
	screen_col = ft_project_sprite_column(game, diff.x, diff.y);
	if (screen_col < 0)
		return ;
	draw.size = ft_compute_sprite_size(game, base_size, distance);
	draw.scaled = ft_new_texture(game->mlx, draw.size, draw.size);
	if (!draw.scaled)
		return ;
	/*
	 * screen_col está en coordenadas de pantalla (izq->der).
	 * IMPORTANTE: el mask ya hace la conversión a índice de rayo:
	 *   ray_index = render_width - (screen_x + x) - 1
	 */
	draw.screen_x = screen_col - draw.size / 2;
	/* Clamp suave para evitar que se quede "pegado" al borde por screen_x extremos */
	if (draw.screen_x < -draw.size)
		draw.screen_x = -draw.size;
	if (draw.screen_x > game->config.render_width)
		draw.screen_x = game->config.render_width;
	draw.screen_y = game->config.render_height / 2 - draw.size / 2
		+ draw.size / 8;
	ft_scale_t_image(tex, draw.scaled);
	ft_mask_alien_by_depth(game, draw.scaled, draw.screen_x, distance);
	ft_draw_transparent_image(game->render, draw.scaled,
		draw.screen_x, draw.screen_y);
}

/**
 * @brief Renderiza todos los sprites visibles en la escena.
 *
 * En modo multijugador, renderiza primero todos los jugadores remotos
 * (excluyendo el jugador local). Luego renderiza el alien si existe.
 * El orden de renderizado asegura que todos los sprites se dibujan
 * con oclusión correcta.
 *
 * @param game Puntero a la estructura del juego.
 */
void	ft_render_all_sprites(t_game *game)
{
	int	idx;

	idx = 0;
	if (game->config.n_players > 1)
	{
		while (idx < game->config.n_players && idx < 4)
		{
			ft_render_objects(game, SPRITE_PLAYER1 + idx);
			idx++;
		}
	}
	ft_render_objects(game, SPRITE_ALIEN);
}
