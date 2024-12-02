
#include "minishell.h"

char	*ft_getenv(t_env *env, char *key)
{
	t_env	*curr;

	if (!env || !key)
		return (NULL);
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			return (curr->value);
		}
		curr = curr->next;
	}
	return (NULL);
}