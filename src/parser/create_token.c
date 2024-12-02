/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:28:32 by plesukja          #+#    #+#             */
/*   Updated: 2024/11/26 13:15:35 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_redir_token(t_token *token,char file_start, char file_end, int token_sign)
{
	t_redir	*redir;

	redir = malloc(sizeof(*redir));
	if (!redir)
		return (parser_error("redir malloc failed\n, token"));
	ft_memset(redir, 0, sizeof(*redir));
	redir->type = REDIR;
	redir->subcmd = token;
	redir->mode = token_sign;
	if (redir->mode == 'h')
	{
		heredoc_get_input(redir);
		if (!redir->temp_file)
		return (parser_error("heredoc failed\n"));
	}
	else
		redir->temp_file = NULL;
	redir->file = file_start;
	redir->end_file = file_end;
	if (token->type = REDIR)
		return (chain_redir_node(token, redir));
	return ((t_token *)redir);
}

t_token	*chain_redir_node(t_token *token, t_redir *redir)
{
	t_redir	*last;

	last = (t_redir *)token;
	while (last->prior_token->type == REDIR)
		last = (t_redir *)last->prior_token;
	redir->prior_token = last->prior_token;
	last->prior_token = (t_token *)redir;
	return (token);
}

t_token	*create_pipe_token(t_token *left, t_token *right)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(*pipe));
	if (!pipe)
	{
		free_tree(right); // free_tree
		return (parser_error("pipe malloc failed\n", pipe));
	}
	ft_memset(pipe, 0, sizeof(*pipe));
	pipe->type = PIPE;
	pipe->left = left;
	pipe->right = right;
	return ((t_token *)(pipe));
}