#ifndef UTILS_BONUS_H
# define UTILS_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"
# include <sys/types.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>

# define C_RED			0xFFFF0000
# define C_WHITE		0xFFFFFF
# define C_GREY			0x808080
# define C_BLUE 		0x0000FF
# define C_YELLOW       0xFFFF00
# define C_BLACK		0x000000
# define C_GREEN		0x008f39
# define C_ALIEN_GREEN	0xFF00FF41
# define C_ALIEN_DARK	0x80001a0a
# define C_ALIEN_GRID	0xFF00CC33
# define C_ALIEN_PLAYER	0xFF00FFFF
# define MAX_RAY_SIZE	10

//minimap 
# define MINIMAP_TILE_SIZE 8 //esto define el tamaño de cada tile en el minimapa
# define MINIMAP_OFFSET_X 10 //  el margen que se deja entre el minimapa y el borde de la ventana x
# define MINIMAP_OFFSET_Y 10 //  el margen que se deja entre el minimapa y el borde de la ventana y
# define MINIMAP_SCALE 0.1 //  el factor de escala del minimapa, 0.1 significa que el minimapa sera 10 veces mas pequeño que la ventana

# define AUDIO_WALK "music&sounds/Andar.wav"
# define T_STEPS_WALK 0.35
# define T_STEPS_RUN  0.20 

//menu animation
# define MENU_FRAME_MS 66  // 66ms = ~15 FPS, 100ms = 10 FPS, 33ms = ~30 FPS

# define TILE_MAP_SIZE  100

# define ESC 			65307
# define M				109
# define m				77
# define W 				119
# define A 				97
# define S 				115
# define D 				100
# define E 				101
# define Q 				113
# define P 				112
# define SPACE 			32
# define UP 			65362
# define DOWN 			65364
# define L 				65361
# define R 				65363
# define FLOOR  		0
# define CEILING 		1
# define DIR_RIGHT 		0
# define DIR_DOWN  		1
# define DIR_LEFT  		2
# define DIR_UP    		3
# define LSHIFT			65505
# define RSHIFT			65506
# define G				103

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1920
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 1080
# endif

# ifndef RENDER_WIDTH
#  define RENDER_WIDTH 1920
# endif

# ifndef RENDER_HEIGHT
#  define RENDER_HEIGHT 1080
# endif

# define MENU_HEIGHT 720
# define MENU_WIDTH 1280
# define MENU_BUTTON_HEIGHT 80
# define MENU_BUTTON_WIDTH 300

# define FOV 45.0

# define MAX_FPS 60

# define MOVE_SPEED		1.0
# define ROTATION_SPEED	45.0
# define RUN_SPEED		3.0
# define MOUSE_SENSITIVITY 0.4
# define DCP 0.1 // dist player collision

# define MIST_COLOR 0x323232

typedef struct s_resolution
{
	int width;
	int height;
} t_resolution;

typedef enum e_wall_direction
{
	WALL_NO = 0,
	WALL_SO = 1,
	WALL_EA = 2,
	WALL_WE = 3
} t_wall_direction;

typedef enum e_door_state
{
	DOOR_CLOSED = 0,
	DOOR_OPENING = 1,
	DOOR_OPEN = 2,
	DOOR_CLOSING = 3
} t_door_state;

typedef enum e_alien_state
{
	ALIEN_PATROL = 0,
	ALIEN_CHASE = 1,
	ALIEN_IDLE = 2
} t_alien_state;

typedef struct s_texture // cambiar nombre a t image
{
	t_img			*img;
	char			*path;
	unsigned int	texture_color;
	int				width;
	int				height;
	unsigned int	**colors_matrix;
} t_texture;

typedef struct s_cursor
{
	int x; 
	int y;
	int dir; 
} t_cursor;


typedef struct s_vector2
{
	double x;
	double y;
} t_vector2;

typedef struct s_vector_int
{
	int x;
	int y;
} t_vector_int;


/**
* @brief Structure to hold s_raycast information.
* 
* This structure is used to store the result of a raycast operation,
* including the distance to the impact point, the coordinates of the impact,
* and the type of impact (0 North, 1 South, 2 East, 3 West).
*/
typedef struct s_raycast
{
	double		distance;
	t_vector2	impact;
	int			type;
} t_raycast;



typedef struct s_player
{
	t_vector2	position;
	double		reverse_y_position;
	t_vector2	rotation;
	t_vector2	velocity;
	double plane_y;
	
} t_player;

typedef struct s_gamepad {
	int	fd;
	int	connected;
	int	a;
	int	b;
	int	x;
	int	y;
	int	lb;
	int	rb;
	int	left_stick_x;
	int	left_stick_y;
	int	right_stick_x;
	int	right_stick_y;
	int right_stick_click;
	int a_pressed;
    int b_pressed;
} t_gamepad;

typedef enum e_input_device
{
	INPUT_KEYBOARD = 0,
	INPUT_GAMEPAD = 1
}	t_input_device;

typedef struct s_keyboard_input {
	int	kb_front;
	int	kb_back;
	int	kb_left;
	int	kb_right;
	int	kb_rotate_left;
	int	kb_rotate_right;
	int	kb_run;
} t_keyboard_input;

typedef struct s_gamepad_input {
	int	gp_front;
	int	gp_back;
	int	gp_left;
	int	gp_right;
	int	gp_rotate_left;
	int	gp_rotate_right;
	int	gp_run;
} t_gamepad_input;

typedef struct s_mouse_input {
	int	mouse_x;
	int	mouse_y;
	int	mouse_clicked;
} t_mouse_input;

typedef struct s_raw_input {
	t_keyboard_input	kb;
	t_gamepad_input		gp;
	t_mouse_input		mouse;
} t_raw_input;

typedef struct s_player_actions {
	int	front;
	int	back;
	int	left;
	int	right;
	int	rotate_left;
	int	rotate_right;
	int	run;
} t_player_actions;

typedef struct s_input {
	t_raw_input			raw;
	t_player_actions	actions;
	t_input_device		active_device;
} t_input;


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

typedef struct s_alien
{
	t_vector2		position;
	t_alien_state	state;
	t_vector2		patrol_points[4];
	int				current_patrol;
	int				patrol_count;
	double			speed;
	double			chase_distance;
	double			patrol_distance;
	double			size;
	t_texture		*texture;
} t_alien;

typedef struct s_image // eliminar
{
	void	*img;
	char	*img_data;
	int		bits_pixel;
	int		image_len;
	int		end; 
} t_image;

typedef struct s_rotated_square
{
	int			x[4];
	int			y[4];
} t_rotated_square;

typedef struct s_precalc
{
	unsigned char	***mix_colors;
	int 			*scale_x_table;
	int 			*scale_y_table;
	t_rotated_square *rotated_squares;
} t_precalc;

typedef struct s_button
{
	t_vector_int	position;
	t_vector_int	size;
	void			(*on_click)(void *game);
	t_texture		*texture;
	t_texture		*hover_texture;
} t_button;

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
} t_menu;

typedef struct s_door
{
	t_vector_int	position;
	t_door_state	state;
	double			animation_progress;
	double			trigger_distance;
	int				texture_index;
} t_door;

typedef struct s_config
{
	int	n_players;
	int	render_width;
	int	render_height;
	int	render_celling;
	int	render_floor;
	int render_mist;
	int	sound_effects;
} t_config;

typedef struct s_game 
{
	char			**map;
	int				width_height[2];
	t_list			*textures[6]; // Array of textures for North, South, East, West, Ceiling, floor
	t_texture 		**arraytextures[6];
	int				length_textures_array[6];
	t_list			*doors;
	t_texture		**door_textures;
	t_alien			*aliens;
	int				door_texture_count;
	void			*mlx;
	t_raycast		*raycasts; 
	void			*window;
	t_image			*img_map;
	t_texture		*render;
	t_texture		*window_img;
	t_texture		*minimap;
	t_player 		*player;
	t_input			input;
	t_gamepad		gamepad;
	int				mouse_xy[2];
	double			delta_time;
	long			last_frame_time;
	int				mouse_captured;
	t_precalc		precalc;
	int				show_menu;
	t_menu			menu;
	char			**env;
	double			*fish_eye_correction;
	pid_t			steps_audio_pid;
    int				is_walking; // 1 si anda, 0 si está parado
    int				is_running;
	double			time_since_last_step;
	t_vector2		**prec_vector_cloud;
	//t_vector2  	**render_cloud;
	int				*mist_density_fc;
	int				mist_cloud_height;
	t_config		config;
	t_resolution	*resolutions;
	int				resolutions_size;
	int				resolution_index;
	t_player		*players;
}	t_game;

#endif