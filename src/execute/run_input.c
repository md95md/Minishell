/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:49:23 by plesukja          #+#    #+#             */
/*   Updated: 2024/11/30 14:59:15 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_input(t_token *token, t_shell *shell)
{
	if (!token)
		exit ();
	if (token->type == COMMAND)
		run_command((t_cmd *)token, shell);
	if (token->type == REDIR)
		run_redir((t_redir *)token, shell);
	if (token->type == PIPE)
		run_pipe((t_pipe *)token, shell);
}

void	run_command(t_cmd *cmd, t_shell *shell)
{
	char	**new_args;
	pid_t	pid;

	if (!cmd->av[0])
		return ;
	new_args = parse_arguments(cmd->av, shell);
	if (!new_args)
		error_exit();
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

parse_arguments()
{

}

run_redir()
{

}

run_pipe()
{
	
}