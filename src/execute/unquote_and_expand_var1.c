/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_and_expand_var1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 20:41:27 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/30 19:12:53 by plesukja         ###   ########.fr       */
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
		else if (*s == '"')
			double_quote_handler(&s, &result, shell);
		else if (*s == '$')
			dollar_sign_handler(&s, &result, shell);
		else
			character_handler(&s, &result);
	}
	return (result);
}

char	*var_expansion(char **s, t_shell *shell)
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
		return (ft_itoa(shell->exit_status));
	}
	var_name_len = 0;
	while (!ft_strchr("'\"$ \0", (*s)[var_name_len]) && (*s)[var_name_len])
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