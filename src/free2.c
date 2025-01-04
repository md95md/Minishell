/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 17:48:10 by plesukja          #+#    #+#             */
/*   Updated: 2025/01/04 17:54:40 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd(t_cmd *cmd)
{
	if (cmd->av)
		free_array(cmd->av);
	free(cmd);
}

static void	free_redir(t_redir *redir)
{
	if (redir->mode == 'h' && redir->temp_file)
	{
		free(redir->temp_file);
		redir->temp_file = NULL;
	}
	free_tree(redir->prior_token);
	free(redir);
}

static void	free_pipe(t_pipe *pipe)
{
	free_tree(pipe->left);
	free_tree(pipe->right);
	free(pipe);
}

void	free_tree(t_token *token)
{
	t_redir	*redir;
	t_cmd	*cmd;

	if (!token)
		return ;
	if (token->type == COMMAND)
		free_cmd((t_cmd *)token);
	else if (token->type == REDIR)
		free_redir((t_redir *)token);
	else if (token->type == PIPE)
		free_pipe((t_pipe *)token);
}