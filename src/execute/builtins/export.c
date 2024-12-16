/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:59:12 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/11 13:21:24 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	run_builtin_export(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	shell->exit_status = 0;
	if (!args[1])
		print_sorted_env(&shell->env);
	else
	{
		while (args[i])
		{
			if (!is_valid_key(args[i]))
			{
				print_error("export: `", args[i], "': not a valid identifier");
				shell->exit_status = 1;
			}
			else
				add_or_update_env_var(&shell->env, args[i]);
			i++;
		}
		shell->env_arr = env_to_arr(shell->env, shell->env_arr);
	}
}

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (*env)
	{
		temp = *env;
		*env = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	*env = NULL;
}