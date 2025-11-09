/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play_audio.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:18:06 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/11/10 00:17:50 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_3d_bonus.h"

/**
 * @brief Detiene la reproducción de audio matando el proceso.
 *
 * Esta función envía una señal SIGTERM al proceso con el PID especificado
 * para detener la reproducción de audio, y luego espera a que el proceso
 * termine para evitar procesos zombie.
 * 
 * @param pid PID del proceso que reproduce el audio.
 * @return 0 si la señal se envió correctamente, -1 en caso de error.
*/
int ft_stop_audio(pid_t pid)
{
	int	status;

	if (pid <= 0)
		return (-1);
	if (kill(pid, SIGTERM) == -1)
		return (-1);
	waitpid(pid, &status, 0);
	return (0);
}

/**
 * @brief Reproduce un archivo de audio utilizando el comando 'aplay'.
 *
 * Esta función crea un proceso hijo que ejecuta el comando 'aplay' para 
 * reproducir el archivo de audio especificado. El proceso padre continúa
 * su ejecución normal y devuelve el PID del proceso hijo.
 * 
 * @param filename Ruta al archivo de audio a reproducir.
 * @return PID del proceso hijo que reproduce el audio, o -1 en caso de error
 * al crear el proceso.
 */
pid_t ft_play_audio(const char *filename, char **env)
{
	pid_t		pid;
	char		*argv[4];

	argv[0] = "aplay";
	argv[1] = "-q";
	argv[2] = (char *)filename;
	argv[3] = NULL;
	if (!filename)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/aplay", argv, env);
		exit(1);
	}
	return (pid);
}
