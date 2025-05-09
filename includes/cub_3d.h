/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:09:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/09 02:30:52 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"
# include <limits.h>
#include <stdbool.h>
#include <stdio.h>

# define ESC 		65307
# define W 			119
# define A 			97
# define S 			115
# define D 			100
# define SPACE 		32
# define UP 		65362
# define DOWN 		65364
# define L 			65361
# define R 			65363
# define FLOOR  	0
# define CEILING 	1

#define DIR_RIGHT 0
#define DIR_DOWN  1
#define DIR_LEFT  2
#define DIR_UP    3

typedef struct s_cursor
{
	int x; 
	int y;
	int dir; 
} t_cursor; 

enum e_texture
{
	NORTH, 
	SOUTH, 
	WEST,
	EAST
};
/*
typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	alpha;
}	t_color;
*/
typedef struct s_game 
{
	char	**map; 
	int		width_height[2];
	int     floor_color[3];
    int     ceiling_color[3];
	char	*textures[4]; 
}	t_game;



int			ft_check_args(int argc, char **argv);
t_game		*ft_loading_game(char *path_map);
void		ft_close_game(int exit_code);
void 		ft_parse_colors(t_game *game, t_file *map_file);
void		ft_parse_textures(t_game *game, t_file *map_file); 
void		ft_debug_game(t_game *game);
int			ft_get_map_start_index(t_file *map_file);
void		ft_wall_algorithm(char **map);

#endif