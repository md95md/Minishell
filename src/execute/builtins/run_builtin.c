/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:14:14 by plesukja          #+#    #+#             */
/*   Updated: 2024/11/30 15:35:59 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	is_builtin_cmd(char *arg)
{
	if (!arg)
		return (false);
	if (ft_strcmp(arg, "echo") == 0 || ft_strcmp(arg, "cd") == 0
		|| ft_strcmp(arg, "pwd") == 0 || ft_strcmp(arg, "export") == 0
		|| ft_strcmp(arg, "unset") == 0 || ft_strcmp(arg, "env") == 0
		|| ft_strcmp(arg, "exit") == 0)
		return (true);
}

void	run_builtin_cmd(t_shell *shell, char **arg)
{
	if (ft_strcmp(arg, "echo") == 0)
		run_builtin_echo(shell, arg);
	else if (ft_strcmp(arg, "cd") == 0)
		run_builtin_cd(shell, arg);
	else if (ft_strcmp(arg, "pwd") == 0)
		run_builtin_pwd(shell, arg);
	else if (ft_strcmp(arg, "export") == 0)
		run_builtin_export(shell, arg);
	else if (ft_strcmp(arg, "unset") == 0)
		run_builtin_unset(shell, arg);
	else if (ft_strcmp(arg, "env") == 0)
		run_builtin_env(shell, shell->env);
	else if (ft_strcmp(arg, "exit") == 0)
		run_builtin_exit(shell, arg);
}