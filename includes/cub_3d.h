/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:09:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/08 01:49:09 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"

# define ESC 	65307
# define W 		119
# define A 		97
# define S 		115
# define D 		100
# define SPACE 	32
# define UP 	65362
# define DOWN 	65364
# define L 		65361
# define R 		65363

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


#endif