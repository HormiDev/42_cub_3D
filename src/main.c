/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:54:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 03:15:09 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d.h"

void ft_set_map(t_map *map)
{
	map->matrix = NULL; 
	map->width = 0; 
	map->height = 0; 
	map->color_sky[0] = -1;
	map->color_sky[1] = -1;
	map->color_sky[2] = -1;
	map->color_floor[0] = -1; 
	map->color_floor[1] = -1; 
	map->color_floor[2] = -1; 
	map->line = NULL; 
	map->map_line = NULL; 
	
}

int main(int argc, char **argv)
{
	//t_map		map; 
	//int			fd; 

	if (!ft_check_args(argc, argv))
		return (1);
	ft_printf("Arguments are valid\n");
	/*
	fd = open(argv[1], O_RDONLY);
	ft_add_fd_to_alloc_lst_ie(fd);
	if (fd <= 0)
	{
		ft_dprintf(2, "Error\nFailed to open file\n"); 
		exit (37);
	}
	ft_set_map(&map);
	if (!ft_map_parse(&map, fd))
	{
		
		exit (38); 
	}

	ft_loading_game(&map);*/
	return (0);
}
