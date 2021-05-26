#include "../minishell.h"

void	memory_allocated(char *memory)
{
	if (!memory)
	{
		ft_putstr_fd("Not allocated memory\n", 2);
		exit (1);
	}
}
