/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinder_bfs_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 19:43:31 by ismherna          #+#    #+#             */
/*   Updated: 2026/04/13 19:50:23 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static int	ft_bfs_reset_on_error(t_bfs *bfs, int width, int height,
		size_t max_allowed)
{
	int		j;

	if (bfs->parent && max_allowed > 0)
		ft_memset(bfs->parent, -1, sizeof(int) * max_allowed);
	if (bfs->visited)
	{
		j = -1;
		while (++j < height && bfs->visited[j])
			ft_memset(bfs->visited[j], 0, sizeof(int) * width);
	}
	return (0);
}

static void	ft_bfs_clear_visited(t_bfs *bfs, int width)
{
	int		max_rows;
	int		j;

	max_rows = bfs->max_queue / width;
	if (bfs->max_queue % width)
		max_rows++;
	j = -1;
	while (++j < max_rows && bfs->visited[j])
		ft_memset(bfs->visited[j], 0, sizeof(int) * width);
}

int	ft_bfs_init(t_bfs *bfs, t_vector_int start, int width, int height)
{
	size_t		total_cells;
	size_t		max_allowed;

	total_cells = (size_t)width * (size_t)height;
	max_allowed = (size_t)bfs->max_queue;
	if (max_allowed == 0 || total_cells > max_allowed)
		return (ft_bfs_reset_on_error(bfs, width, height, max_allowed));
	bfs->queue_start = 0;
	bfs->queue_end = 1;
	bfs->width = width;
	bfs->height = height;
	bfs->queue[0] = start;
	if (bfs->max_queue > 0)
		ft_memset(bfs->parent, -1, sizeof(int) * bfs->max_queue);
	if (bfs->visited && width > 0)
		ft_bfs_clear_visited(bfs, width);
	bfs->visited[start.y][start.x] = 1;
	return (1);
}
