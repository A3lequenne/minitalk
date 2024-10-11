#include "../includes/minitalk.h"

static void	send_c(int pid, unsigned char c)
{
	int		i;

	i = 8;
	while (i--)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		pause();
		usleep(200);
	}
}

static void	send_msg(int pid, char *msg)
{
	while (*msg)
	{
		send_c(pid, (unsigned char) *msg);
		msg++;
	}
	send_c(pid, '\n');
	send_c(pid, '\0');
}

static int	check_pid(int pid)
{
	int	i;

	i = 8;
	while (i-- && kill(pid, SIGUSR1) == 0)
	{
		pause();
		usleep(200);
	}
	return (i == -1);
}

static void get_msg(int sign_id)
{
	(void) sign_id;
}

int	main(int ac, char **av)
{
	unsigned int	pid;

	if (ac != 3)
	{
		ft_putstr_fd("Usage: ./client [server-pid] [message]\n", 1);
		return (1);
	}
	pid = ft_atoi(av[1]);
	signal(SIGUSR2, get_msg);
	if (!check_pid(pid))
	{
		ft_putstr_fd("Invalid PID\n", 1);
		return (1);
	}
	send_msg(pid, av[2]);
	return (0);
}