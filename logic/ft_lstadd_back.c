#include "../minishell.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env *ptr;

	ptr = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}
