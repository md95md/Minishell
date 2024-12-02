/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procure_token_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:54:15 by plesukja          #+#    #+#             */
/*   Updated: 2024/11/20 09:17:54 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_token_sign(char **ptr, char *end, char **token_start, char **token_end)
{
	int		token_sign;
	char	*cur;

	cur = *ptr;
	while ((cur < end) && ft_strchr(WHITESPACE, *cur))
		cur++;
	if (token_start)
		*token_start = cur;
	if (!(*cur))
		token_sign = 0;
	else if (*cur == '|')
	{
		token_sign = *cur;
		(*cur)++;
	}
	else if (*cur == '>' || *cur == '<')
		token_sign = get_redir_sign(&cur);
	else
		token_sign = get_quote_sign(&cur);
	if (token_end)
		*token_end = cur;
	*ptr = cur;
	return (token_sign);
}

int	get_quote_sign(char **curr)
{
	int	quote_sign;

	quote_sign = 'a';
	while (**curr && !ft_strchr(signS, **curr) \
		&& !ft_strchr(WHITESPACE, **curr))
	{
		if (**curr == '\'' || **curr == '"')
		{
			quote_sign = **curr;
			(*curr)++;
			while ((**curr && **curr != quote_sign))
				(*curr)++;
			if (!(**curr))
				return (-1);
			else
				(*curr)++;
		}
		else
			(*curr)++;
	}
	return (quote_sign);
}

int	get_redir_sign(char **cur)
{
	int	redir_sign;

	redir_sign = **cur;
	if (**cur == '<')
	{
		(*cur)++;
		if (**cur == '<')
		{
			redir_sign = 'h';
			(*cur)++;
		}
	}
	else if (**cur == '>')
	{
		(*cur)++;
		if (**cur == '>')
		{
			redir_sign = '+';
			(*cur)++;
		}
	}
	return (redir_sign);
}