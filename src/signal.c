/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:46:03 by plesukja          #+#    #+#             */
/*   Updated: 2025/01/22 23:26:53 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

// static void	set_exit_status(t_shell *shell, int status)
// {
// 	shell->exit_status = status;
// 	g_signal = status;
// }

// void	restore_prompt(t_shell *shell)
// {
// 	set_exit_status(shell, 130);
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// static void	ctrl_c(t_shell *shell)
// {
// 	set_exit_status(shell, 130);
// 	write(STDOUT_FILENO, "\n", 1);
// }

// static void	back_slash(t_shell *shell)
// {
// 	set_exit_status(shell, 131);
// 	write(STDERR_FILENO, "QUIT\n", 6);
// }

void	restore_prompt(int signum)
{
    if (signum == SIGINT)
	{
    	g_signal = 130; // Set the global exit status
    	write(STDOUT_FILENO, "\n", 1);
    	rl_replace_line("", 0);
    	rl_on_new_line();
    	rl_redisplay();
	}
}

static void	ctrl_c(int signum)
{
    (void)signum;
    g_signal = 130;
    write(STDOUT_FILENO, "\n", 1);
}

static void	back_slash(int signum)
{
    (void)signum;
    g_signal = 131;
    write(STDERR_FILENO, "Quit: 3\n", 8);
}

// run_signals(1) For restoring prompt behavior // before the command is executed
// run_signals(2) For normal signal handling // while executing command
// run_signals(3) For exit handling
// SIGINT ^C
// SIGQUIT ^\
// EOF ^D
// void	run_signals(int sig, t_shell *shell)
// {
// 	(void)shell;

// 	if (sig == 1)
// 	{
// 		signal(SIGINT, (void (*)(int))restore_prompt);
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	if (sig == 2)
// 	{
// 		signal(SIGINT, (void (*)(int))ctrl_c);
// 		signal(SIGQUIT, (void (*)(int))back_slash);
// 	}
// 	// if (sig == 3)
// 	// {
// 	// 	printf("exit\n");
// 	// 	exit(shell->exit_status);
// 	// }
// }

void	run_signals(int sig, t_shell *shell)
{
	(void)shell;

	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
}
