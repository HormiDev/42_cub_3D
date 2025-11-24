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
# define C_ALIEN_GREEN	0x00FF41
# define C_ALIEN_DARK	0x001a0a
# define C_ALIEN_GRID	0x00CC33
# define C_ALIEN_PLAYER	0x00FFFF
# define MAX_RAY_SIZE	10

//minimap 
# define MINIMAP_TILE_SIZE 8 //esto define el tamaño de cada tile en el minimapa
# define MINIMAP_OFFSET_X 10 //  el margen que se deja entre el minimapa y el borde de la ventana x
# define MINIMAP_OFFSET_Y 10 //  el margen que se deja entre el minimapa y el borde de la ventana y
# define MINIMAP_SCALE 0.1 //  el factor de escala del minimapa, 0.1 significa que el minimapa sera 10 veces mas pequeño que la ventana

# define AUDIO_WALK "music&sounds/Andar.wav"
# define T_STEPS_WALK 0.75
# define T_STEPS_RUN  0.4 

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

# define FOV 45.0

# define MAX_FPS 60

# define MOVE_SPEED		1.0
# define ROTATION_SPEED	45.0
# define RUN_SPEED		3.0
# define MOUSE_SENSITIVITY 0.4
# define DCP 0.1 // dist player collision

# define MIST_COLOR 0x323232FF

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

typedef struct s_input {
	int front;
	int back;
	int left;
	int right;
	int rotate_left;
	int rotate_right;
	int run;
} t_input;

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
} t_gamepad;

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

typedef struct s_menu
{
	void		*frames[200];
	t_texture	*frames_textures[200];
	int			total_frames;
	int			current_frame;
	long		last_frame_time;
	t_texture	*scaled_frame;
	pid_t		menu_music_pid;
} t_menu;

typedef struct s_door
{
	t_vector_int	position;
	t_door_state	state;
	double			animation_progress;
	double			trigger_distance;
	int				texture_index;
} t_door;

typedef struct s_game 
{
	char		**map;
	int			width_height[2];
	t_list		*textures[6]; // Array of textures for North, South, East, West, Ceiling, floor
	t_texture 	**arraytextures[6];
	int			length_textures_array[6];
	t_list		*doors;
	t_texture	**door_textures;
	int			door_texture_count;
	void		*mlx;
	t_raycast	*raycasts; 
	void		*window;
	t_image		*img_map;
	t_texture	*render;
	t_texture	*window_img;
	t_texture	*minimap;
	t_player 	player;
	t_input		input;
	t_gamepad	gamepad;
	int			mouse_xy[2];
	double		delta_time;
	long		last_frame_time;
	int			mouse_captured;
	t_precalc	precalc;
	int			show_menu;
	t_menu		menu;
	char		**env;
	double		*fish_eye_correction;
	pid_t		steps_audio_pid;
    int  		is_walking; // 1 si anda, 0 si está parado
    int  		is_running;
	double		time_since_last_step;
	t_vector2   **prec_vector_cloud;
	t_vector2   **render_cloud;
}	t_game;

#endif