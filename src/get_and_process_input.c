/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_process_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 12:35:44 by plesukja          #+#    #+#             */
/*   Updated: 2025/01/02 14:42:06 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*init_prompt(t_shell *shell)
{
	char	*pwd;
	char	*user;
	char	*prompt;

	pwd = ft_getenv(shell->env, "PWD");
	user = ft_getenv(shell->env, "USER");
	prompt = NULL;
	if (!pwd || !user)
		return (ft_strdup("$ "));
	prompt = ft_strjoin(user, "@:~");
	prompt = ft_strjoin(prompt, pwd);
	prompt = ft_strjoin(prompt, "$ ");
	return (prompt);
}

int	get_input(char **line, t_shell *shell)
{
	char	*prompt;

	prompt = init_prompt(shell);
	run_signals(1, shell);
	*line = readline(prompt);
	free(prompt);
	if (!*line)
		return (-1);
	if (*line && **line)
		add_history(*line);
	return (0);
}

void	process_input(t_shell *shell, char *input)
{
	printf("process_input\n");
	if (!build_tree(shell, input))
		return ;
	run_signals(2, shell);
	run_input(shell->current_cmd, shell);
}

bool	build_tree(t_shell *shell, char *input)
{
	printf("build_tree\n");
	shell->current_cmd = process_token(input);
	if (!shell->current_cmd)
	{
		shell->exit_status = 2;
		free(input);
		return (false);
	}
	else if (shell->current_cmd->type == COMMAND \
		&& !((t_cmd *)(shell->current_cmd))->av[0])
	{
		free_tree(shell->current_cmd);
		free(input);
		return (false);
	}
	if (shell->current_cmd->type == PIPE)
		shell->has_pipe = 1;
	shell->default_stdin = dup(STDIN_FILENO);
	shell->default_stdout = dup(STDOUT_FILENO);
	return (true);
}
