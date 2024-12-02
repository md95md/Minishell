/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 16:46:03 by plesukja          #+#    #+#             */
/*   Updated: 2024/11/10 12:07:37 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// run_signals(1) For restoring prompt behavior // before the command is executed
// run_signals(2) For normal signal handling // while executing command
// run_signals(3) For exit handling
void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
}

void	restore_prompt(void)
{
	shell->exit_status = 130;
	g_signal = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c(void)
{
	shell->exit_status = 130;
	g_signal = 130;
	write(STDOUT_FILENO, "\n", 1);
}

void	back_slash(void)
{
	shell->exit_status = 131;
	g_signal = 131;
	write(STDERR_FILENO, "QUIT\n", 6);
}
