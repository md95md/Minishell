/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:49:23 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/28 20:39:04 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// // non-builtin command have to be fork before executing
// static void	run_non_builtin(char **new_args, t_shell *shell)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid < 0)
// 		error_exit("fork failed", shell);
// 	else if (pid == 0)
// 		execute(new_args, shell);
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			shell->exit_status = WEXITSTATUS(status);
// 	}
// }

// static void	run_non_piped_command(t_cmd *command, t_shell *shell)
// {
// 	char	**new_args;

// 	if (!command->av[0])
// 		return ;
// 	new_args = parse_arguments(command->av, shell);
// 	if (!new_args)
// 		error_exit("parse arguments failed", shell);
// 	if (is_builtin_cd(new_args[0]))
// 		run_builtin_cd(new_args, shell);
// 	else
// 		run_non_builtin(new_args, shell);
// 	free_array(new_args);
// }

// static void	run_child_process(t_cmd *command, t_shell *shell)
// {
// 	char	**new_args;

// 	if (!command->av[0])
// 		return ;
// 	new_args = parse_arguments(command->av, shell);
// 	if (!new_args)
// 		error_exit("parse arguments failed", shell);
// 	if (is_builtin_cd(new_args[0]))
// 		run_builtin_cd(new_args, shell);
// 	else
// 		execute(new_args, shell);
// 	free_array(new_args);
// }

// void	run_command(t_token *token, t_shell *shell)
// {
// 	if (!token)
// 		exit(EXIT_FAILURE);
// 	if (token->type == COMMAND)
// 	{
// 		if (shell->has_pipe)
// 			run_child_process((t_cmd *)token, shell);
// 		else
// 			run_non_piped_command((t_cmd *)token, shell);
// 	}
// 	else if (token->type == REDIR)
// 	{
// 		run_redirections((t_redir *)token, shell);
// 	}
// 	else if (token->type == PIPE)
// 	{
// 		run_pipe((t_pipe *)token, shell);
// 	}
// }

void	run_input(t_token *token, t_shell *shell)
{
	if (!token)
		exit(EXIT_FAILURE);
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

char	**parse_arguments(char **args, t_shell *shell)
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

run_redir()
{

}

run_pipe()
{
	
}