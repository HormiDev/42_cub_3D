/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:39:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/09 00:11:10 by ide-dieg         ###   ########.fr       */
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
	char	**env;
}	t_audio_manager;

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

pid_t ft_play_audio(const char *filename, char **env)
{
	pid_t		pid;
	char		*argv[4];
	char		audio[1024];

	if (!filename)
		return (-1);
	ft_strlcpy_p(audio, filename, sizeof(audio));
	argv[0] = "aplay";
	argv[1] = "-q";
	argv[2] = audio;
	argv[3] = NULL;
	pid = hd_fork();
	if (pid == 0)
	{
		hd_alloc_clear();
		//ft_printf("[Audio] recibido: %s\n", audio);
		execve("/usr/bin/aplay", argv, env);
		exit(1);
	}
	return (pid);
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
	if (audio_manager->pid == 0)//proceso hijo
		audio_manager_run(audio_manager);
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

int	main(int argc, char **argv, char **env)
{
	t_audio_manager	*audio_manager;

	(void)argc;
	(void)argv;
	audio_manager = init_audio_manager(env);
	if (!audio_manager)
		return (1);
	audio_manager_send(audio_manager, "music&sounds/menu.wav");
	sleep(2);
	audio_manager_send(audio_manager, "stop");
	sleep(2);
	for(int i = 0; i < 2; i++)
	{
		sleep(1);
		audio_manager_send(audio_manager, "music&sounds/Andar.wav");
	}
	sleep(1);
	audio_manager_send(audio_manager, "music&sounds/menu.wav");
	sleep(2);
	audio_manager_stop(audio_manager);
	hd_alloc_clear();
	return (0);
}
