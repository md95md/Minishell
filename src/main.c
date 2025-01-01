/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:37:12 by plesukja          #+#    #+#             */
/*   Updated: 2025/01/01 20:40:25 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stddef.h>

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*input;

	(void)ac;
	(void)av;
	shell = NULL;
	input = NULL;
	init_shell(&shell, envp);
	while (1)
	{
		if (get_input(&input, shell) != -1)
		{
			process_input(shell, input);
			restore_fd(shell);//restore_fd
			run_signals(3, shell);
			free_tree(shell->current_cmd);
			shell->current_cmd = NULL;
			free(input);
		}
	}
	if (input)
		free(input);
	clean_and_exit(shell);
	return (0);
}

void	init_shell(t_shell **shell, char **envp)
{
	*shell = ft_calloc(1, sizeof(t_shell));
	if (!(*shell))
		exit(EXIT_FAILURE);
	(*shell)->env_arr = get_env_arr(envp);
	create_env_linked_list(&(*shell)->env, envp);
	(*shell)->has_pipe = 0;
	(*shell)->exit_status = 0;
	(*shell)->default_stdin = STDIN_FILENO;
	(*shell)->default_stdout = STDOUT_FILENO;
	(*shell)->in_fd = STDIN_FILENO;
	(*shell)->out_fd = STDOUT_FILENO;
}

char	**get_env_arr(char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		new_arr[i] = ft_strdup(arr[i]);
		if (!new_arr[i])
		{
			free_array(new_arr);
			return (NULL);
		}
		i++;
	}
	new_arr[i] = NULL;
	return (new_arr);
}

void	create_env_linked_list(t_env **env, char **envp)
{
	t_env	*env_node;
	t_env	*last;
	int		i;

	last = NULL;
	i = 0;
	while (envp[i])
	{
		env_node = malloc(sizeof(t_env));
		if (!env_node)
		{
			free_env(env);
			return ;
		}
		env_node->key = ft_strndup(envp[i], ft_strchr(envp[i], '=') - envp[i]);
		env_node->value = ft_strdup(ft_strchr(envp[i], '=') + 1);
		env_node->next = NULL;
		if (!(*env))
			*env = env_node;
		else
			last->next = env_node;
		last = env_node;
		i++;
	}
}

void	process_input(t_shell *shell, char *input)
{
	if (!build_tree(shell, input))
		return ;
	run_signals(2, shell);
	run_input(shell->current_cmd, shell);
}

int		get_input(char **line, t_shell *shell)
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

char	*init_prompt(t_shell *shell)
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

bool	build_tree(t_shell *shell, char *input)
{
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
