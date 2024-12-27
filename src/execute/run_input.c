/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:49:23 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/27 16:00:35 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// non-builtin command have to be fork before executing
static void	run_non_builtin(char **new_args, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit("fork failed", shell);
	else if (pid == 0)
		execute(new_args, shell);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}

static void	run_non_piped_command(t_cmd *command, t_shell *shell)
{
	char	**new_args;

	if (!command->av[0])
		return ;
	new_args = parse_arguments(command->av, shell);
	if (!new_args)
		error_exit("parse arguments failed", shell);
	if (is_builtin_cd(new_args[0]))
		run_builtin_cd(new_args, shell);
	else
		run_non_builtin(new_args, shell);
	free_array(new_args);
}

static void	run_child_process(t_cmd *command, t_shell *shell)
{
	char	**new_args;

	if (!command->av[0])
		return ;
	new_args = parse_arguments(command->av, shell);
	if (!new_args)
		error_exit("parse arguments failed", shell);
	if (is_builtin_cd(new_args[0]))
		run_builtin_cd(new_args, shell);
	else
		execute(new_args, shell);
	free_array(new_args);
}

void	run_command(t_token *token, t_shell *shell)
{
	if (!token)
		exit(EXIT_FAILURE);
	if (token->type == COMMAND)
	{
		if (shell->has_pipe)
			run_child_process((t_cmd *)token, shell);
		else
			run_non_piped_command((t_cmd *)token, shell);
	}
	else if (token->type == REDIR)
	{
		run_redirections((t_redir *)token, shell);
	}
	else if (token->type == PIPE)
	{
		run_pipe((t_pipe *)token, shell);
	}
}


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

// void	run_command(t_cmd *cmd, t_shell *shell)
// {
// 	char	**new_args;
// 	pid_t	pid;

// 	if (!cmd->av[0])
// 		return ;
// 	new_args = parse_arguments(cmd->av, shell);
// 	if (!new_args)
// 		error_exit();
// 	if (is_builtin_cmd(new_args[0]))
// 		run_builtin_cmd(shell, new_args);
// 	else
// 	{
// 		if (shell->has_pipe)
// 			execute(new_args, shell);
// 		else
// 			fork_and_execute(new_args, shell);
// 	}
// 	free_array(new_args);
// }

parse_arguments()
{

}

run_redir()
{

}

run_pipe()
{
	
}