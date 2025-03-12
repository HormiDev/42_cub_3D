/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:09:12 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/12 18:50:38 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_3D_H
# define CUB_3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../42_Libft/libft.h"

typedef struct s_cub_3d
{
	void	*mlx;
	void	*win;
	int 	win_width;
	int 	win_height;
}	t_cub_3d;

int			ft_close_game(void *param);
t_cub_3d	*ft_init_cub3d(void);

#endif