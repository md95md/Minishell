/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:30:06 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/30 15:34:40 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//127: Command not found.
//126: Command is found but not executable (permission denied, a directory).
//stat() checks info about a file or directory. 0: success, -1: error.
//access checks permissions for a file. 0: success, -1: failure
static void	check_path_executable(char **args, t_shell *shell)
{
	char			*path;
	struct	stat	statbuf;

	path = args[0];
	if (stat(path, &statbuf) < 0)
	{
		shell->exit_status = 127;
		execute_error(args, path, ": No such file or directory\n", shell);
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		shell->exit_status = 126;
		execute_error(args, path, ": Is a directory\n", shell);
	}
	if (access(path, X_OK) < 0)
	{
		shell->exit_status = 126;
		execute_error(args, path, ": Permission denied\n", shell);
	}
}

static char	**get_path_arr(t_env *env)
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

static char	*get_file_path(char **args, t_shell *shell)
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
			free_aray(path_arr);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free_array(path_arr);
	return (NULL);
}

static void	execute_error(char **args, char *s, char *message, t_shell *shell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (s)
		ft_putstr_fd(s, STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	free_array(args);
	clean_and_exit(shell);
}

void	execute(char **args, t_shell *shell)
{
	char	*file_path;

	if (!args || !args[0])
	{
		free_array(args);
		clean_and_exit(shell);
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
		execute_error(args, args[0], ": command not found\n", shell);
	}
	if (execve(file_path, args, shell->env) < 0)
	{
		free(file_path);
		shell->exit_status = errno;
		execute_error((args, NULL, "execute error\n", shell););
	}
}
// //path_arr 22/46