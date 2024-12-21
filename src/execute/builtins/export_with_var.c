/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:26:22 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/12 15:34:38 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_or_update_env_var(t_env **env, char *var)
{
	// t_env	*cur;
	// t_env	*new;
	char	*inp_key;
	char	*inp_value;

	if (!env || !var)
		return ;
	if (split_var_into_input_key_value(var, &inp_key, &inp_value) < 0)
		return ;
	if (find_existed_node_and_update(env, inp_key, inp_value))
		return ;
	else
		append_new_node_in_env(env, inp_key, inp_value);
}

//success returns 0
//error returns -1
int	split_var_into_input_key_value(char *var, char **inp_key, char **inp_value)
{
	char	*equal_ptr;

	equal_ptr = ft_strchr(var, '=');
	if (equal_ptr)
	{
		//*inp_key = ft_substr(var, 0, equal_ptr - var);
		*inp_key = ft_strndup(var, equal_ptr - var);
		*inp_value = ft_strdup(equal_ptr + 1);
	}
	else
	{
		*inp_value = ft_strdup(var);
		*inp_value = NULL;
	}
	if (!*inp_key || (!*inp_value && equal_ptr))
	{
		free (*inp_key);
		free (*inp_value);
		*inp_key = NULL;
		*inp_value = NULL;
		return (-1);
	}
	return (0);
}

bool	find_existed_node_and_update(t_env **env, char *inp_key, char *inp_value)
{
	t_env	*cur;
	
	cur = *env;
	while (cur)
	{
		if (ft_strcmp(cur->key, inp_key) == 0)
		{
			free(cur->value);
			cur->value = inp_value;
			free(inp_key);
			return (true);
		}
		cur = cur->next;
	}
	free(inp_key);
	free(inp_value);
	return (false);
}

void	append_new_node_in_env(t_env **env, char *inp_key, char *inp_value)
{
	t_env	*new;
	t_env	*cur;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free (inp_key);
		free (inp_value);
		return ;
	}
	new->key = inp_key;
	new->value = inp_value;
	new->next = NULL;
	if (!*env)
		*env = new;
	else
	{
		cur = *env;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

bool	is_valid_key(char *var)
{
	int	i;

	i = 0;
	if ( !ft_isalpha(var[i]) || var[i] != '_')
		return (false);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}