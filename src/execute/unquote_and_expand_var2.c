/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_and_expand_var2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:03:37 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/30 18:49:30 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_quote_handler(char **s, char **result)
{
	int		i;
	char	*temp;

	i = 0;
	*s += 1;
	if (is_empty(s))
		return ;
	while ((*s)[i] && (*s)[i] != '\'')
		i++;
	if ((*s)[i] == '\'')
	{
		temp = ft_substr(&(*s)[0], 0, i);
		*result = ft_strjoin_free(*result, temp);
		i++;
	}
	*s += i;
}

void	double_quote_handler(char **s, char **result, t_shell *shell)
{
	int		i;
	char	*temp;

	i = 0;
	*s += 1;
	if (is_empty(s))
		return ;
	while ((*s)[i] && (*s)[i] != '"')
	{
		if ((*s)[i] == '$')
			double_quote_dollar_handler(s, result, shell);
		else
		{
			while ((*s)[i] && (*s)[i] != '$' && (*s)[i] != '"')
				i++;
			temp = ft_substr(&(*s)[0], 0, i);
			*result = ft_strjoin_free(*result, temp);
			*s += i;
		}
	}
	*s += 1;
}

void	double_quote_dollar_handler(char **s, char **result, t_shell *shell)
{
	char	*temp;

	temp = var_expansion(s, shell);
	*result = ft_strjoin_free(*result, temp);
}

void	dollar_sign_handler(char **s, char **result, t_shell *shell)
{
	char	*temp;

	if (*s[1] == '\'')
		single_quote_handler(s, result);
	else if (*s[1] == '"')
		double_quote_handler(s, result, shell);
	else
	{
		temp = var_expansion(s, shell);
		*result = ft_strjoin_free(*result, temp);
	}
}

void	character_handler(char **result, char **s)
{
	int		i;
	char	*temp;

	i = 0;
	*s += 1;
	if (is_empty(s))
		return ;
	while ((*s)[i] && (*s)[i] != '\'' && (*s)[i] != '"' && (*s)[i] != '$')
		i++;
	temp = ft_substr(&(*s)[0], 0, i);
	*result = ft_strjoin_free(*result, temp);
	*s += i;
}
