/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:39:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 02:25:44 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

static void	free_gnl(void *ptr)
{
	get_next_line(-1);
	free(ptr);
}

static void	exit_audio_manager(int exit_code)
{
	hd_alloc_clear();
	exit(exit_code);
}

static void	audio_manager_run(t_audio_manager *audio_manager)
{
	char	*line;

	close(audio_manager->pipe[1]);
	if (dup2(audio_manager->pipe[0], 0) < 0)
		exit_audio_manager(1);
	close(audio_manager->pipe[0]);
	hd_alloc(malloc(1), free_gnl);
	line = hd_alloc(get_next_line(0), free);
	while (line)
	{
		line[ft_strlen_p(line) - 1] = '\0';
		if (ft_strncmp_p(line, "stop", 5) == 0)
			hd_alloc_clear();
		else
			ft_play_audio(line, audio_manager->env);
		hd_free(line);
		line = hd_alloc(get_next_line(0), free);
	}
	hd_alloc_clear();
	exit(0);
}

t_audio_manager	*init_audio_manager(char **env)
{
	t_audio_manager	*audio_manager;

	audio_manager = hd_calloc(1, sizeof(t_audio_manager));
	if (!audio_manager)
		return (0);
	audio_manager->env = env;
	if (pipe(audio_manager->pipe) < 0)
	{
		hd_free(audio_manager);
		return (0);
	}
	audio_manager->pid = hd_fork();
	if (audio_manager->pid == -1)
	{
		close(audio_manager->pipe[0]);
		close(audio_manager->pipe[1]);
		hd_free(audio_manager);
		return (0);
	}
	if (audio_manager->pid == 0)
		audio_manager_run(audio_manager);
	close(audio_manager->pipe[0]);
	audio_manager->pipe[0] = -1;
	return (audio_manager);
}
