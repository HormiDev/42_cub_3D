/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_manager_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismherna <ismherna@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 19:39:51 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/04/10 02:21:07 by ismherna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_3d_bonus.h"

pid_t	ft_play_audio(const char *filename, char **env)
{
	pid_t	pid;
	char	*argv[4];
	char	audio[1024];

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
		close(2);
		execve("/usr/bin/aplay", argv, env);
		exit(1);
	}
	return (pid);
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
