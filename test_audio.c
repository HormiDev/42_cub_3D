#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>

pid_t ft_play_audio(const char *filename)
{
pid_tpid;
char*argv[4];
intdev_null;

argv[0] = "aplay";
argv[1] = "-q";
argv[2] = (char *)filename;
argv[3] = NULL;
if (!filename)
return (-1);
pid = fork();
if (pid == -1)
return (-1);
else if (pid == 0)
{
dev_null = open("/dev/null", O_WRONLY);
if (dev_null != -1)
{
dup2(dev_null, STDERR_FILENO);
close(dev_null);
}
execve("/usr/bin/aplay", argv, NULL);
exit(1);
}
return (pid);
}

int ft_stop_audio(pid_t pid)
{
if (pid <= 0)
return (-1);
return (kill(pid, SIGKILL));
}

int main()
{
pid_t pid;

printf("Iniciando reproducción...\n");
pid = ft_play_audio("music&sounds/menu.wav");
printf("PID del audio: %d\n", pid);

if (pid > 0)
{
printf("Audio reproduciéndose por 3 segundos...\n");
sleep(3);
printf("Deteniendo audio...\n");
ft_stop_audio(pid);
printf("Audio detenido.\n");
}
else
{
printf("Error al iniciar el audio\n");
}

return 0;
}
