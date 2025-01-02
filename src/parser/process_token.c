/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:51:34 by plesukja          #+#    #+#             */
/*   Updated: 2025/01/02 18:34:43 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_token	*null_terminate(t_token *token)
{
	t_cmd	*cmd;
	t_redir	*redir;
	t_pipe	*pipe;
	int		i;

	printf ("null_terminate\n");
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
	printf ("null_terminate: finished\n");
	return (token);
}

t_token	*process_token(char *s)
{
	char	*end;
	t_token	*token;

	end = s + ft_strlen(s);
	token = parse_pipe(&s, end);
	printf ("process_token: s = %s\n", s);
	printf ("process_token: ft_strlen(s) = %d\n", ft_strlen(s));
	printf ("process_token: end = %s...\n", end);
	if (!token)
		return (NULL);
	find_next_token(&s, end, "");
	printf ("process_token: after find_next_token\n");
	if (s != end)
	{
		printf ("process_token: s != end\n");
		return (NULL);
	}
	printf ("process_token: before null_terminate\n");
	null_terminate(token);
	return (token);
	printf("process_token: finished\n");
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
