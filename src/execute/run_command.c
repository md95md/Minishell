/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 10:46:41 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/29 23:51:06 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_command(t_cmd *cmd, t_shell *shell)
{
	char	**new_args;
	pid_t	pid;

	if (!cmd->av[0])
		return ;
	new_args = parse_arguments(cmd->av, shell);
	if (!new_args)
		error_exit("parse arguments failed", shell);
	if (is_builtin_cmd(new_args[0]))
		run_builtin_cmd(shell, new_args);
	else
	{
		if (shell->has_pipe)
			execute(new_args, shell);
		else
			fork_and_execute(new_args, shell);
	}
	free_array(new_args);
}

static char	**parse_arguments(char **args, t_shell *shell)
{
	char	**new_args;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_args = ft_calloc(array_len(args) + 1, sizeof(char *))
	while (args[i])
	{
		tmp = unquote_and_expand_var(args[i], shell);
		if (tmp[0])
			new_args[j++] = tmp;
		else
			free(tmp);
		i++;
	}
	return (new_args);
}
