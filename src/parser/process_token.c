/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:51:34 by plesukja          #+#    #+#             */
/*   Updated: 2025/01/04 00:10:08 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*null_terminate(t_token *token)
{
	t_cmd	*cmd;
	t_redir	*redir;
	t_pipe	*pipe;
	int		i;

	if (!token)
		return (NULL);
	if (token->type == COMMAND)
	{
		cmd = (t_cmd *)token;
		i = 0;
		while (cmd->av[i++])
			cmd->end_av[i] = 0;
	}
	else if (token->type == REDIR)
	{
		redir = (t_redir *)token;
		null_terminate(redir->prior_token);
		*redir->end_file = 0;
	}
	else if (token->type == PIPE)
	{
		pipe = (t_pipe *)token;
		null_terminate(pipe->left);
		null_terminate(pipe->right);
	}
	return (token);
}

t_token	*process_token(char *s)
{
	char	*end;
	t_token	*token;

	end = s + ft_strlen(s);
	token = parse_pipe(&s, end);
	if (!token)
		return (NULL);
	find_next_token(&s, end, "");
	if (s != end)
	{
		return (NULL);
	}
	null_terminate(token);
	printf("process_token: finished\n");
	return (token);
}

bool	find_next_token(char **ptr, char *end, char *charset)
{
	char	*cur;

	//printf("find_next_token\n");
	cur = *ptr;
	while ((cur < end) && ft_strchr(WHITESPACE, *cur))
		cur++;
	*ptr = cur;
	if (*cur && ft_strchr(charset, *cur))
		return (true);
	else
		return (false);
}
