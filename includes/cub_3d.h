/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:09:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/07/22 19:22:35 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdio.h>
#include <math.h>
 
# define C_RED			0xFFFF0000
# define C_WHITE		0xFFFFFF
# define C_GREY			0x808080
# define C_BLUE 		0x0000FF
# define C_YELLOW       0xFFFF00
# define C_BLACK		0x000000
# define C_GREEN		0x008f39
# define MAX_RAY_SIZE	20

# define TILE_MAP_SIZE  50

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

# ifndef WINDOW_WIDTH
#  define WINDOW_WIDTH 1920
# endif

# ifndef WINDOW_HEIGHT
#  define WINDOW_HEIGHT 1080
# endif

typedef enum e_wall_direction
{
	WALL_NO = 0,
	WALL_SO = 1,
	WALL_EA = 2,
	WALL_WE = 3
} t_wall_direction;

typedef struct s_texture
{
	char			*path;
	int				width;
	int				height;
	int				size_colors;
	int				**pixels; 
	unsigned int	*colors;
} t_texture;

typedef struct s_xpm_color
{
	char            *chars;
    unsigned int    value;
} t_xpm_color;

typedef struct s_cursor
{
	int x; 
	int y;
	int dir; 
} t_cursor;

/*
typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_color;
*/

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

typedef struct s_image
{
	void	*img;
	char	*img_data;
	int		bits_pixel;
	int		image_len;
	int		end; 
} t_image;

typedef struct s_input {
	int w;
	int a;
	int s;
	int d;
	int q;
	int e;
} t_input;

typedef struct s_game 
{
	char	**map; 
	int		width_height[2];
	int     floor_color[3];
    int     ceiling_color[3];
	t_list	*textures[4]; // Array of textures for North, South, East, West
	t_texture floor_tex;
	t_texture ceiling_tex; 
	void	*mlx;
	t_raycast	*raycasts; 
	void	*window;
	t_image  *img_map; 
	t_player player;
	t_input	keys;
	int		mouse_xy[2];
}	t_game;

int				ft_check_args(int argc, char **argv);
t_game			*ft_loading_game(char *path_map);
void			ft_close_game(int exit_code);
int				ft_close_game_for_mlx(void);
void 			ft_parse_colors(t_game *game, t_file *map_file);
void			ft_parse_textures(t_game *game, t_file *map_file); 
void			ft_debug_game(t_game *game);
int				ft_get_map_start_index(t_file *map_file);
int				ft_check_map_closed(t_game *game);
void			ft_config_mlx(t_game *game);
void			ft_draw_map(t_game *game);
void			ft_config_player(t_game *game);
void			ft_check_map(t_game *game);
void			ft_create_game_map(t_game *game, t_file *map_file, const int *height_start_end, const int *width_start_end);
int				ft_end_column_map(t_file *map_file, const int *height_start_end);
int				ft_start_column_map(t_file *map_file, const int *height_start_end);
void			ft_parse_map(t_game *game, t_file *map_file);
//int		 	ft_handle_key(void *parm);

//rays
void			ft_raycast(t_game *game, double angle, t_raycast *ray, double max_size);
void			ft_draw_line_in_image(t_game *game, t_vector2 vertex1, t_vector2 vertex2, int color);
int				ft_mouse_move(int x, int y, t_game *game);
double			ft_angle_rad(double degrees);
int				ft_update(void *param);
int 			ft_key_release(int keycode, t_game *game);
int 			ft_key_press(int keycode, t_game *game);
int				ft_start_line_map(t_file *map_file);
int				ft_end_line_map(t_file *map_file, int start_line);
int				ft_start_column_map(t_file *map_file, const int *height_start_end);
int				ft_end_column_map(t_file *map_file, const int *height_start_end);
void			ft_rotate_map_y(t_game *game);
void			ft_draw_player(t_game *game);
int				get_pixel_color_from_game(t_game *game, int x, int y);
void			ft_draw_pixel_in_img(t_game *game, int x, int y, int color);
void			ft_draw_circle(t_game *game, int cx, int cy, int color);
void			ft_draw_sq(t_game *game, int x, int y, int color);
void			ft_draw_grid_horizontal(t_game *game, int color);
void			ft_draw_grid_vertical(t_game *game, int color);

//textures 
int				extract_texture_from_xpm(const char *path, t_texture *tex);

//math
double			ft_cos(double angle);
double			ft_sin(double angle);

//debug 
void			ft_print_map(char **map);

// xpm
unsigned int 	parse_color_hex(const char *str);
int				parse_xpm_header(char *line, int *w, int *h, int *n_colors, int *cpp);
int				parse_xpm_colors(char **lines, int *i, int n_colors, unsigned int *colors, char *symbols);
int				parse_xpm_pixels(char **lines, int *i, int w, int h, int **pixels, char *symbols);
int				parse_xpm_file_header_and_alloc(const char **lines, int *i, t_texture *tex, char *symbols);

#endif