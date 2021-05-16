#include "../minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void				ft_putnbr_fd(int n, int fd)
{
	unsigned int	nmb;

	if (n < 0)
	{
		nmb = n * -1;
		ft_putchar_fd('-', fd);
	}
	else
		nmb = n;
	if (nmb / 10 != 0)
		ft_putnbr_fd(nmb / 10, fd);
	ft_putchar_fd(nmb % 10 + '0', fd);
}