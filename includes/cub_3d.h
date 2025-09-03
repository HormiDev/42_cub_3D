
#ifndef CUB_3D_H
# define CUB_3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdio.h>
#include <fcntl.h>
# include <math.h>
# include <errno.h>
 
# define C_RED			0xFFFF0000
# define C_WHITE		0xFFFFFF
# define C_GREY			0x808080
# define C_BLUE 		0x0000FF
# define C_YELLOW       0xFFFF00
# define C_BLACK		0x000000
# define C_GREEN		0x008f39
# define MAX_RAY_SIZE	100  // Aumentado para permitir distancias mayores

//minimap 
#define MINIMAP_TILE_SIZE 8 //esto define el tamaño de cada tile en el minimapa
#define MINIMAP_OFFSET_X 10 //  el margen que se deja entre el minimapa y el borde de la ventana x
#define MINIMAP_OFFSET_Y 10 //  el margen que se deja entre el minimapa y el borde de la ventana y
#define MINIMAP_SCALE 0.1 //  el factor de escala del minimapa, 0.1 significa que el minimapa sera 10 veces mas pequeño que la ventana

# define TILE_MAP_SIZE  100

# define ESC 			65307
# define W 				119
# define A 				97
# define S 				115
# define D 				100
# define E 				101
# define Q 				113
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

# define MOVE_SPEED		1.0
# define ROTATION_SPEED	45.0
# define RUN_SPEED		3.0

typedef enum e_wall_direction
{
	WALL_NO = 0,
	WALL_SO = 1,
	WALL_EA = 2,
	WALL_WE = 3
} t_wall_direction;

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

typedef struct s_precalc
{
	unsigned char	***mix_colors;
	int 			*scale_x_table;
	int 			*scale_y_table;
} t_precalc;

typedef struct s_game 
{
	char		**map;
	int			width_height[2];
	t_list		*textures[4]; // Array of textures for North, South, East, West
	t_texture 	**arraytextures[4];
	int			length_textures_array[4];
	t_texture 	*floor_tex;
	t_texture 	*ceiling_tex; 
	void		*mlx;
	t_raycast	*raycasts; 
	void		*window;
	t_image		*img_map;
	t_texture	*render;
	t_texture	*window_img;
	t_player 	player;
	t_input		input;
	t_gamepad	gamepad;
	int			mouse_xy[2];
	double		delta_time;
	long		last_frame_time;
	t_precalc	precalc;
}	t_game;

// ============================================================================
// MAIN FUNCTIONS
// ============================================================================
int				ft_check_args(int argc, char **argv);
t_game			*ft_loading_game(char *path_map);
void			ft_close_game(int exit_code);
int				ft_close_game_for_mlx(t_game *game);

// ============================================================================
// CONFIGURATION FUNCTIONS
// ============================================================================
void			ft_config_mlx(t_game *game);
void			ft_config_player(t_game *game);

// ============================================================================
// PARSING FUNCTIONS
// ============================================================================
void			ft_parse_map(t_game *game, t_file *map_file);
void 			ft_parse_colors(t_game *game, t_file *map_file);
void			ft_read_textures_in_map(t_game *game, t_file *map_file);
int				ft_path_or_color(char *str);

// Map parsing utilities
int				ft_get_map_start_index(t_file *map_file);
int				ft_start_line_map(t_file *map_file);
int				ft_end_line_map(t_file *map_file, int start_line);
int				ft_start_column_map(t_file *map_file, const int *height_start_end);
int				ft_end_column_map(t_file *map_file, const int *height_start_end);
void			ft_create_game_map(t_game *game, t_file *map_file, const int *height_start_end, const int *width_start_end);
void			ft_rotate_map_y(t_game *game);

// Map validation
void			ft_check_map(t_game *game);
int				ft_check_map_closed(t_game *game);

// XPM parsing
void			check_arguments_xpm(char *path);

// ============================================================================
// GAME LOOP & UPDATE FUNCTIONS
// ============================================================================
int				ft_update(void *param);
long			ft_get_time(void);

// ============================================================================
// MOVEMENT & INPUT FUNCTIONS
// ============================================================================
void			ft_controls(t_game *game);
void 			ft_forwad_back(t_game *game, double move_speed);
void 			ft_right_left(t_game *game, double move_speed);
int 			ft_key_press(int keycode, t_game *game);
int 			ft_key_release(int keycode, t_game *game);
int				ft_mouse_move(int x, int y, t_game *game);
void			ft_move_direction(t_game *game, double angle, double move_speed);
void			ft_move_player(t_game *game, double move_x, double move_y);


// Gamepad functions
void			ft_init_gamepad(t_game *game);
void			ft_free_gamepad(t_game *game);
void			ft_update_gamepad(t_game *game);
void			ft_gamepad_movement(t_game *game);

// ============================================================================
// RAYCAST FUNCTIONS
// ============================================================================
void			ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size);
void			ft_calculate_raycasts(t_game *game);

// ============================================================================
// RENDER FUNCTIONS
// ============================================================================
void			ft_render_3d(t_game *game);
void			ft_map2D(t_game *game);
void			draw_column(t_game *game, int x, t_raycast *ray);
void			ft_draw_player(t_game *game);
void			ft_scale_t_image_precalc(t_texture *tex_origin, t_texture *text_destiny, t_game *game);
void			ft_scale_t_image(t_texture *tex_origin, t_texture *text_destiny);

// Drawing utilities
void			ft_draw_line_in_image(t_game *game, t_vector2 start, t_vector2 end, int color);
void			ft_draw_pixel_in_img(t_img *img, int x, int y, int color);
void			ft_draw_circle(t_game *game, int cx, int cy, int color);
void			ft_draw_sq(t_game *game, int x, int y, int color);
void			ft_draw_grid_horizontal(t_game *game, int color);
void			ft_draw_grid_vertical(t_game *game, int color);

// Utility functions
double			ft_double_diff(double a, double b);
double			ft_vector_distance(t_vector2 a, t_vector2 b);

// ============================================================================
// MATH FUNCTIONS
// ============================================================================
double			ft_angle_rad(double degrees);
double			ft_cos(double angle);
double			ft_sin(double angle);
double			ft_sqrt(double value);

// ============================================================================
// COLOR FUNCTIONS
// ============================================================================
void			ft_mix_color_precalc(unsigned int *color, unsigned int  *mix_color, int percent, t_game *game);
void			ft_mix_color(unsigned int *color, unsigned int  *mix_color, int percent);
unsigned int	ft_parse_color_rgb(char *color_str);
int				ft_path_or_color(char *str);
int				ft_str_isnumber(char *str);

// ============================================================================
// DEBUG FUNCTIONS
// ============================================================================
void			ft_debug_game(t_game *game);
void			ft_print_map(char **map, int error_x, int error_y);
void			debug_print_textures(t_game *game);
long			ft_long_diff(long a, long b);

unsigned char 	***ft_precalc_mixcolor(void);
int				*ft_scale_precalc_x(void);
int				*ft_scale_precalc_y(void);


#endif