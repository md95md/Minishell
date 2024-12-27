
#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tree(t_token *token)
{
	t_redir	*redir;

	if (!token)
		return ;
	if (token->type == COMMAND)
		free((t_cmd *)token);
	else if (token->type == REDIR)
	{
		redir = (t_redir *)token;
		if (redir->mode == 'h' && redir->temp_file)
		{
			free(redir->temp_file);
			redir->temp_file = NULL;
		}
		free_tree(redir->prior_token);
		free(redir);
	}
	else if (token->type == PIPE)
	{
		free_tree(((t_pipe *)token)->left);
		free_tree(((t_pipe *)token)->right);
		free((t_pipe *)token);
	}
}

t_token	*parser_error(char *message, t_token *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	else
		ft_putstr_fd("error\n", STDERR_FILENO);
	free_tree(token);
	token = NULL;
	return (NULL);
}

void	close_fd(t_shell *shell)
{
	if (shell->default_stdin != STDIN_FILENO)
		close(shell->default_stdin);
	if (shell->default_stdout != STDOUT_FILENO)
		close(shell->default_stdout);
	if (shell->in_fd != STDIN_FILENO)
		close(shell->in_fd);
	if (shell->out_fd != STDOUT_FILENO)
		close(shell->out_fd);
}

void	clean_and_exit(t_shell *shell)
{
	int	exit_status_temp;

	exit_status_temp = shell->exit_status;
	close_fd(shell);
	if (shell->env_arr)
		free_array(shell->env_arr);
	if (shell->env)
		free_env(&shell->env);
	if (shell->current_cmd)
	{
		free_tree(shell->current_cmd);
		shell->current_cmd = NULL;
	}
	free(shell);
	rl_clear_history();
	exit(exit_status_temp);
}

void	error_exit(char *message, t_shell *shell)
{
	if (!shell)
		exit(EXIT_FAILURE);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	perror(message);
	if (errno)
		shell->exit_status = errno;
	else
		shell->exit_status = 1;
	clean_and_exit(shell);
}
