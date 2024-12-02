/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:30:06 by plesukja          #+#    #+#             */
/*   Updated: 2024/11/28 18:05:17 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_and_execute(char **new_args, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		error_exit();
	else if (pid == 0)
		execute(new_args, shell);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
	}
}

void	execute(char **args, t_shell *shell)
{
	char	*file_path;

	if (!args || !args[0])
	{
		free_array();
		clean_and_exit();
	}
	if (ft_strchr(args[0], '/'))
	{
		check_path_executable(args, shell);
		file_path = ft_strdup(args[0]);
	}
	else
		file_path = get_file_path(args, shell);
	if (!file_path)
	{
		shell->exit_status = 127;
		execute_error();
	}
	if (execve(file_path, args, shell->env) < 0)
	{
		free(file_path);
		shell->exit_status = errno;
		execute_error();
	}
}

//127: Command not found.
//126: Command is found but not executable (permission denied, a directory).
//stat() checks info about a file or directory. 0 : success, -1: error.
//access checks permissions for a file. 0 : success, -1: failure
void	check_path_executable(char **args, t_shell *shell)
{
	char			*path;
	struct	stat	statbuf;

	path = args[0];
	if (stat(path, &statbuf) < 0)
	{
		shell->exit_status = 127;
		execute_error();
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		shell->exit_status = 126;
		execute_error();
	}
	if (access(path, X_OK) < 0)
	{
		shell->exit_status = 126;
		execute_error();
	}
}

char	*get_file_path(char **args, t_shell *shell)
{
	char	*file_path;
	char	*tmp;
	char	**path_arr;
	int		i;

	path_arr = get_path_arr(shell->env);
	if (!path_arr)
		return (NULL);
	i = 0;
	while (path_arr[i])
	{
		tmp = ft_strjoin(path_arr[i], "/");
		file_path = ft_strjoin(tmp, args[0]);
		free (tmp);
		if (access(file_path, X_OK) == 0)
		{
			free_aray(path_arr); //***********/
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free_array(path_arr);
	return (NULL);
}

char	**get_path_arr(t_env *env)
{
	char	**path_arr;
	char	*path_value;

	path_value = ft_getenv(env, "PATH");
	if (!path_value)
		return (NULL);
	path_arr = ft_split(path_value, ':');
	if (!path_arr)
		return (NULL);
	return (path_arr);
}

path_arr 22/46