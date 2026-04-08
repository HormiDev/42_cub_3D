/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 12:17:03 by username          #+#    #+#             */
/*   Updated: 2026/04/09 00:50:07 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"
# include <sys/types.h>
# include <limits.h>
# include <sys/time.h>
# include <float.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
#include <sys/types.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <unistd.h>

# define C_RED 0xFFFF0000
# define C_WHITE 0xFFFFFF
# define C_GREY 0x808080
# define C_BLUE 0x0000FF
# define C_YELLOW 0xFFFF00
# define C_CYAN 0x00FFFF
# define C_BLACK 0x000000
# define C_GREEN 0x008f39
# define C_ALIEN_GREEN 0xFF00FF41
# define C_ALIEN_DARK 0x80001a0a
# define C_ALIEN_RED 0xFFFF0000
# define C_ALIEN_YELLOW 0xFFFFFF00
# define C_ALIEN_BLUE 0xFF0000FF
# define C_ALIEN_CYAN 0xFF00FFFF
# define C_ALIEN_GRID 0xFF00CC33
# define C_ALIEN_PLAYER 0xFF00FFFF
# define MAX_RAY_SIZE 10
# define MAX_PLAYERS 5

//minimap
# define MINIMAP_TILE_SIZE 8 //esto define el tamaño de cada tile en el minimapa
# define MINIMAP_OFFSET_X 10 // el margen que se deja entre el minimapa y el borde de la ventana x
# define MINIMAP_OFFSET_Y 10 // el margen que se deja entre el minimapa y el borde de la ventana y
# define MINIMAP_SCALE 0.1 // el factor de escala del minimapa, 0.1 significa que el minimapa sera 10 veces mas pequeño que la ventana

# define AUDIO_WALK "music&sounds/Andar.wav"
# define T_STEPS_WALK 0.35
# define T_STEPS_RUN 0.20

//menu animation
# define MENU_FRAME_MS 66 // 66ms = ~15 FPS, 100ms = 10 FPS, 33ms = ~30 FPS

# define TILE_MAP_SIZE 100

# define ESC 65307
# define M 109
# define m 77
# define W 119
# define A 97
# define S 115
# define D 100
# define E 101
# define Q 113
# define P 112
# define SPACE 32
# define UP 65362
# define DOWN 65364
# define L 65361
# define R 65363
# define FLOOR 0
# define CEILING 1
# define DIR_RIGHT 0
# define DIR_DOWN 1
# define DIR_LEFT 2
# define DIR_UP 3
# define LSHIFT 65505
# define RSHIFT 65506
# define G 103

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1920
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 1080
# endif

# define MENU_HEIGHT 720
# define MENU_WIDTH 1280
# define MENU_BUTTON_HEIGHT 80
# define MENU_BUTTON_WIDTH 300

# define FOV 45.0

# define MAX_FPS 60
# define GAME_DURATIONS_COUNT 5

# define MOVE_SPEED 1.0
# define ROTATION_SPEED 90.0
# define RUN_SPEED 3.0
# define MOUSE_SENSITIVITY 0.4
# define DCP 0.1 // dist player collision
# define ANGLE_STEP 0.01
# define MIN_ALIEN_SIZE 15

# define ALIEN_SPEED_ATTACK 0.0 //3.5
# define ALIEN_SPEED_PATROL 0.0 //4.0

# define MIST_COLOR 0xFF323232
# define MAX_GAMEPADS 4

typedef struct s_resolution
{
	int	width;
	int	height;
}	t_resolution;

typedef enum e_wall_direction
{
	WALL_NO = 0,
	WALL_SO = 1,
	WALL_EA = 2,
	WALL_WE = 3,
	DOOR_NO = 4,
	DOOR_SO = 5,
	DOOR_EA = 6,
	DOOR_WE = 7
}	t_wall_direction;

typedef enum e_door_state
{
	DOOR_CLOSED = 0,
	DOOR_OPEN = 1
}	t_door_state;

typedef enum e_alien_state
{
	ALIEN_PATROL = 0,
	ALIEN_CHASE = 1,
	ALIEN_IDLE = 2
}	t_alien_state;

typedef enum e_game_state
{
	GAME_PLAYING = 0,
	GAME_PLAYERS_WIN = 1,
	GAME_ALIEN_WIN = 2
}	t_game_state;

typedef struct s_texture
{
	t_img			*img;
	char			*path;
	unsigned int	texture_color;
	int				width;
	int				height;
	unsigned int	**cmx;
}	t_texture;

typedef struct s_prerender_model
{
	t_texture	**texture;
	int			n_frames;
	int			n_angles;
}	t_prerender_model;

typedef struct s_cursor
{
	int	x;
	int	y;
	int	dir;
}	t_cursor;

typedef struct s_vector2
{
	double	x;
	double	y;
}	t_vector2;

typedef struct s_vector_int
{
	int	x;
	int	y;
}	t_vector_int;

/**
* @brief Structure to hold s_raycast information.
*
* This structure is used to store the result of a raycast operation,
* including the distance to the impact point, the coordinates of the impact,
* and the type of impact (0 North, 1 South, 2 East, 3 West).
*/
typedef struct s_raycast
{
	t_vector2	origin_position;
	double		distance;
	t_vector2	impact;
	int			type;
}	t_raycast;

typedef struct s_render_objets
{
	int			object_type;
	t_vector2	*position;
	double		angle;
	double		distance;
	double		size;
}	t_render_objects;

typedef struct s_bfs
{
	t_vector_int	*queue;
	int				*parent;
	int				**visited;
	int				queue_start;
	int				queue_end;
	int				max_queue;
	int				width;
	int				height;
}	t_bfs;

typedef enum e_entity_type
{
	ENTITY_PLAYER = 0,
	ENTITY_ALIEN = 1
}	t_entity_type;

typedef struct s_player
{
	t_entity_type		type;
	int					active;
	int					alive;
	t_vector2			position;
	t_vector2			rotation;
	t_vector2			velocity;
	double				plane_y;
	double				render_distance;
	t_prerender_model	*model;
	t_alien_state		state;
	double				speed;
	double				chase_distance;
	double				size;
	int					dist[128][128];
	t_vector_int		path[1024];
	int					path_len;
	int					curr_step;
	t_vector_int		last_heatmap_pos;
	int					chase_sound_played;
}	t_player;

typedef struct s_gamepad
{
	int	fd;
	int	connected;
	int	a;
	int	b;
	int	x;
	int	y;
	int	lb;
	int	rb;
	int	rt;
	int	left_stick_x;
	int	left_stick_y;
	int	right_stick_x;
	int	right_stick_y;
	int	right_stick_click;
	int	menu;
	int	a_pressed;
	int	b_pressed;
	int	menu_pressed;
	int	rt_pressed;
}	t_gamepad;

typedef enum e_input_device
{
	INPUT_KEYBOARD = 0,
	INPUT_GAMEPAD = 1
}	t_input_device;

typedef struct s_player_actions
{
	int		front;
	int		back;
	int		left;
	int		right;
	int		rotate_left;
	int		rotate_right;
	int		run;
	int		walk;
	int		interact;
	int		flamethrower_charges;
	int		flamethrower_ready;
	long	flamethrower_last_time;
	double	flamethrower_cooldown_remaining;
}	t_player_actions;

typedef enum e_duration
{
	DURATION_1_MINUTE,
	DURATION_2_MINUTES,
	DURATION_3_MINUTES,
	DURATION_5_MINUTES,
	DURATION_10_MINUTES,
	DURATION_UNLIMITED
}	t_duration;

typedef enum e_resolutions
{
	RES_90,
	RES_135,
	RES_180,
	RES_270,
	RES_360,
	RES_540,
	RES_720,
	RES_1080,
	RES_2k,
	RES_4k
}	t_resolutions;

typedef struct s_objet_draw
{
	t_texture	*scaled;
	int			screen_x;
	int			screen_y;
	int			size;
	double		distance;
	int			angle;
}	t_objet_draw;

typedef struct s_image
{
	void	*img;
	char	*img_data;
	int		bits_pixel;
	int		image_len;
	int		end;
}	t_image;

typedef struct s_rotated_square
{
	int	x[4];
	int	y[4];
}	t_rotated_square;

typedef struct s_precalc
{
	unsigned char		***mix_colors;
	int					*scale_x_table;
	int					*scale_y_table;
	t_rotated_square	*rotated_squares;
}	t_precalc;

typedef struct s_audio_manager
{
	pid_t	pid;
	int		pipe[2];
	char	**env;
}	t_audio_manager;

typedef struct s_button
{
	t_vector_int	position;
	t_vector_int	size;
	void	(*on_click)(void *game);
	t_texture	*texture;
	t_texture	*hover_texture;
	int			is_hovered;
}	t_button;

typedef struct s_menu
{
	t_texture		*render;
	t_texture		*frames_textures[200];
	int				total_frames;
	int				current_frame;
	long			last_frame_time;
	t_texture		*logo;
	t_button		*buttons;
	int				n_buttons;
	pid_t			menu_music_pid;
	t_vector_int	mouse_position;
}	t_menu;

typedef struct s_door
{
	t_vector_int	position;
	t_door_state	state;
	double			animation_progress;
	double			auto_reopen_delay;
	double			auto_reopen_timer;
	int				texture_index;
}	t_door;

typedef struct s_config
{
	int	n_players;
	int	render_width;
	int	render_height;
	int	resolution_index;
	int	render_celling;
	int	render_mist;
	int	sound_effects;
	int	duration_index;
	int	charges;
}	t_config;

typedef struct s_game
{
	long				current_time;
	char				**map;
	int					**map_heatmap;
	long				heat_time;
	char				**map_transitable;
	char				**map_transitable_aux;
	int					width_height[2];
	int					bfs_queue_size;
	int					bfs_parent_size;
	int					bfs_visited_width;
	int					bfs_visited_height;
	t_list				*textures[7];
	t_texture			**arraytextures[7];
	int					larraytex[7];
	t_list				*doors;
	void				*mlx;
	t_raycast			*raycasts;
	void				*window;
	t_image				*img_map;
	t_texture			*render;
	t_texture			*window_img;
	t_texture			*minimap;
	t_player			*player;
	t_player_actions	actions[MAX_GAMEPADS];
	t_input_device		devices[MAX_GAMEPADS];
	int					kb_player;
	int					mouse_xy[2];
	int					mouse_captured;
	t_gamepad			gamepads[MAX_GAMEPADS];
	int					gamepad_count;
	int					waiting_for_gamepads;
	double				delta_time;
	long				last_frame_time;
	t_precalc			precalc;
	int					show_menu;
	t_menu				menu;
	t_menu				menu_settings;
	char				**env;
	t_audio_manager		*audio_manager;
	double				*fish_eye_correction;
	int					is_walking;
	// 1 si anda, 0 si está parado
	int			is_running;
	double		time_since_last_step;
	t_vector2	**prec_vector_cloud;
	//t_vector2  		**render_cloud;
	int					*mist_density_fc;
	int					mist_cloud_height;
	t_config			config;
	t_config			tmp_config;
	t_resolution		*resolutions;
	int					resolutions_size;
	int					*durations;
	int					durations_size;
	t_game_state		game_state;
	long				game_start_time;
	t_player			players[MAX_PLAYERS];
	t_player			*ordered_ojects[MAX_PLAYERS];
	t_texture			*font;
	t_texture			*timer;
	t_texture			*render_timer;
	t_prerender_model	*alien_prerender;
	t_vector_int		*bfs_queue;
	int					*bfs_parent;
	int					**bfs_visited;
	double				x_dcp;
	t_texture			*null_texture;
	t_texture			*screen_end_img;
}	t_game;

#endif
