/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_and_expand_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:41:27 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/29 00:59:36 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*unquote_and_expand_var(char *s, t_shell *shell)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	while (*s)
	{
		if (*s == '\'')
			single_quote_handler(&s, &result);
		else if	(*s == '"')
			double_quote_handler(&s, &result);
		else if	(*s == '$')
			dollar_sign_handler(&s, &result, shell);
		else
			character_handler(&s, &result);
	}
	return (result);
}

void	single_quote_handler(char **s, char **result)
{
	int		i;
	char 	*temp;

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

void	double_quote_handler(char **s, char **result)
{
	int		i;
	char 	*temp;

	i = 0;
	*s += 1;
	if (is_empty(s))
		return ;
	while ((*s)[i] && (*s)[i] != '"')
	{
		if ((*s)[i] == '$')
			double_quote_dollar_handler(&s, &result, shell);
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
	char 	*temp;

	temp = var_expansion(s, shell);
	*result = ft_strjoin_free(*result, temp);
}

void	dollar_sign_handler(char **s, char **result, t_shell *shell)
{
	char	*temp;

	if (*s[1] == '\'')
		single_quote_handler(s, result);
	else if (*s[1] == '"')
		double_quote_handler(s, result);
	else
	{
		temp = var_expansion(s, shell);
		*result = ft_strjoin_free(*result, temp);
	}
}

void	character_handler(result, s)
{
	int		i;
	char 	*temp;

	i = 0;
	*s += 1;
	if (is_empty(s))
		return ;
	while ((*s)[i] && (*s)[i] != '\'' && (*s)[i] != '"' && (*s)[i] != '$')
		i++
	temp = ft_substr(&(*s)[0], 0, i);
	*result = ft_strjoin_free(*result, temp);
	*s += i;
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	if  (!join)
		return (NULL);
	free(s1);
	free(s2);
	return (join);
}

char	*var_expansion(char **s,t_shell *shell)
{
	char	*var_value;
	char	*var_name;
	int		var_name_len;

	*s += 1;
	// if (ft_strchr("\'\"$ \0", (*s)[0]))
	// return (ft_strdup("$"));
	if ((*s)[0] == '?')
	{
		*s += 1;
		return (ft_itoa(shell->status));
	}
	var_name_len = 0;
	while (!ft_strchr('\'"$ \0', (*s)[var_name_len]) && (*s)[var_name_len])
		var_name_len++;
	var_name = ft_substr(*s, 0, var_name_len);
	var_value = ft_getenv(shell->env, var_name);
	free (var_name);
	if (!var_value)
		return (ft_strdup(""));
	*s += var_name_len;
	return (var_value);
}

//expand_variable 7/16