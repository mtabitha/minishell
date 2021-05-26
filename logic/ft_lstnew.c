#include "../minishell.h"

t_env	*ft_lstnew(void *content)
{
	t_env	*r;

	r = malloc(sizeof(t_env));
	if (!r)
		return (NULL);
	r->str = ft_strdup(content);
	r->next = NULL;
	return (r);
}
