/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:09:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 03:15:09 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"

typedef struct map_s
{
	char 	**matrix; 
	int		width;
	int		height;

	int 	color_floor[3];
	int 	color_sky[3];
	
	char 	*line;
	char 	*map_line;
	
}	t_map;



int			ft_check_args(int argc, char **argv);
int			ft_close_game(void *param);
int			ft_map_parse(t_map *map, int fd); 
t_map	*ft_init_cub3d(t_map *map);

#endif