#include "../includes/minitalk.h"

static void	get_sign(int sign_id, siginfo_t *info, void *context)
{
	static unsigned char	c;
	static int				i;

	(void) context;
	i += 1;
	c |= sign_id == SIGUSR2;
	if (i < 8)
		c <<= 1;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
	usleep(200);
	kill(info->si_pid, SIGUSR2);
}

static void	show_pid(int pid)
{
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = get_sign;
	show_pid(getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}