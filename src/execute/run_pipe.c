/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 10:43:04 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/29 23:46:18 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_pipe(t_pipe *pipe, t_shell *shell)
{
	int		pfd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pfd < 0))
		error_exit("pipe failed", shell);
	pid_left = fork();
	if (pid_left < 0)
		error_exit("fork failed", shell);
	if (pid_left == 0)
		set_new_left_pfd(pfd, pipe, shell);
	pid_right = fork();
	if (pid_right < 0)
		error_exit("fork failed", shell);
	if (pid_right == 0)
		set_new_right_pfd(pfd, pipe, shell);
	close(pfd[0]);
	close(pfd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
}

static void	set_new_left_pfd(int pfd[], t_pipe *pipe, t_shell *shell)
{
	close(pfd[0]);
	if (dup2(pfd[1], STDIN_FILENO) < 0)
		error_exit("dup2 failed", shell);
	close(pfd[1]);
	run_command(pipe->left, shell);
	clean_and_exit(shell);
}

static void	set_new_right_pfd(int pfd[], t_pipe *pipe, t_shell *shell)
{
	close(pfd[1])
	if (dup2(pfd[0], STDOUT_FILENO) < 0)
		error_exit("dup2 failed", shell);
	close(pfd[0]);
	run_command(pipe->right, shell);
	clean_and_exit(shell);
}