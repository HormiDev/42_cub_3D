/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:39:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/17 20:10:36 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../42_Libft/libft.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_audio_manager
{
	pid_t	pid;
	int		pipe[2];
}	t_audio_manager;

void	free_gnl(void *ptr)
{
	get_next_line(-1);
	free(ptr);
}

static void	audio_manager_run(void)
{
	char	*line;

	hd_alloc(malloc(1), free_gnl);
	line = get_next_line(0);
	while (line)
	{
		ft_printf("[CHILD] recibido: %s", line);
		line = get_next_line(0);
		hd_free(line);
	}
	hd_alloc_clear();
	exit(0);
}

t_audio_manager	*start_audio_manager(void)
{
	t_audio_manager	*audio_manager;

	audio_manager = hd_calloc(1, sizeof(t_audio_manager));
	if (!audio_manager)
		return (0);
	audio_manager->pipe[0] = -1;
	audio_manager->pipe[1] = -1;
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
	if (audio_manager->pid == 0)//proceso hijo
	{
		close(audio_manager->pipe[1]);
		if (dup2(audio_manager->pipe[0], 0) < 0)
			exit(1);
		close(audio_manager->pipe[0]);
		audio_manager_run();
	}
	close(audio_manager->pipe[0]);
	audio_manager->pipe[0] = -1;
	return (audio_manager);
}

int	audio_manager_send(t_audio_manager *audio_manager, const char *msg)
{
	if (!audio_manager || !msg || audio_manager->pipe[1] < 0)
		return (-1);
	return (ft_dprintf(audio_manager->pipe[1], "%s\n", msg));
}

void	audio_manager_stop(t_audio_manager *audio_manager)
{
	if (!audio_manager)
		return ;
	if (audio_manager->pipe[1] >= 0)
		close(audio_manager->pipe[1]);
	waitpid(audio_manager->pid, 0, 0);
}

int	main(int argc, char **argv)
{
	t_audio_manager	*audio_manager;

	(void)argc;
	(void)argv;
	audio_manager = start_audio_manager();
	if (!audio_manager)
		return (1);
	audio_manager_send(audio_manager, "hola desde el padre");
	sleep(1);
	audio_manager_send(audio_manager, "segunda linea");
	audio_manager_send(audio_manager, "tercera linea");
	audio_manager_stop(audio_manager);
	return (0);
}