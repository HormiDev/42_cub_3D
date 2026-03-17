/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_forck_audiomanager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:04:18 by ide-dieg          #+#    #+#             */
/*   Updated: 2026/03/17 18:25:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hd_alloc.h"
#include <sys/wait.h>

/**
 * @brief Libera el PID registrado y solicita la finalización del hijo.
 *
 * Esta función se registra como destructor del PID almacenado en HD_alloc.
 * Si el PID corresponde a un proceso hijo válido, le envía SIGTERM para
 * solicitar una terminación controlada y espera a que finalice mediante
 * waitpid. Finalmente libera la memoria que contiene el PID.
 *
 * @param pid_ptr Puntero a un pid_t dinámico con el PID del proceso hijo.
 */
static void hd_kill_free_fork(void *pid_ptr)
{
	pid_t pid = *(pid_t *)pid_ptr;
	if (pid > 0)
	{
		if (kill(pid, SIGTERM) != -1)
			waitpid(pid, NULL, 0);
	}
	free(pid_ptr);
}

/**
 * @brief Atiende las señales de terminación configuradas para el hijo.
 *
 * Cuando el proceso hijo recibe una de las señales instaladas por
 * hd_fork_child_setup_cleanup, libera la memoria gestionada por HD_alloc y
 * termina el proceso con un código compatible con la convención de shell
 * `128 + señal`.
 *
 * @param sig Número de la señal recibida.
 */
static void	hd_fork_child_signal_handler(int sig)
{
	hd_alloc_clear();
	exit(128 + sig);
}

/**
 * @brief Instala los manejadores de señales del proceso hijo.
 *
 * Configura una misma rutina de tratamiento para SIGTERM, SIGINT y SIGHUP.
 * Estas señales permiten limpiar los recursos del hijo antes de finalizar.
 *
 * Nota: SIGKILL no puede capturarse ni interceptarse, por lo que no existe
 * garantía de limpieza si el proceso se termina con `kill -9`.
 */
static void	hd_fork_child_setup_cleanup(void)
{
	struct sigaction	sa;

	sa.sa_handler = hd_fork_child_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGTERM, &sa, NULL);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGHUP, &sa, NULL);
}

/**
 * @brief Crea un proceso hijo y registra su PID en HD_alloc.
 *
 * Esta función encapsula fork() y reserva memoria gestionada por HD_alloc
 * para guardar el PID resultante. En el proceso padre, ese PID queda
 * asociado a un destructor que intentará terminar al hijo con SIGTERM al
 * liberar la memoria. En el proceso hijo, se instalan manejadores para
 * señales de terminación controlada.
 * 
 * Si hay que matar este proceso se recomienda usar:
 * kill(<PID>, SIGTERM)
 * kill(<PID>, SIGINT)
 * kill(<PID>, SIGHUP)
 *
 * @return PID del hijo en el padre, 0 en el hijo y -1 si falla la reserva.
 */
pid_t hd_fork(void)
{
	pid_t *pid_ptr;
	
	pid_ptr = hd_alloc(malloc(sizeof(pid_t)), hd_kill_free_fork);
	if (!pid_ptr)
		return (-1);
	*pid_ptr = fork();
	if (*pid_ptr == 0)
		hd_fork_child_setup_cleanup();
	return (*pid_ptr);
}
