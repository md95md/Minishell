/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_and_expand_var2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 01:03:37 by plesukja          #+#    #+#             */
/*   Updated: 2025/01/23 00:42:56 by plesukja         ###   ########.fr       */
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

// void	double_quote_handler(char **s, char **result, t_shell *shell)
// {
// 	*s += 1;
// 	if (is_empty(s))
// 		return ;
// 	while (**s != 0 && **s != '"')
// 	{
// 		if (**s == '\'')
// 			single_quote_handler(s, result);
// 		else if (**s == '$')
// 			dollar_sign_handler(s, result, shell);
// 		else
// 			character_handler(s, result);
// 	}
// }

// ***********My original*************
// void	double_quote_handler(char **s, char **result, t_shell *shell)
// {
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	*s += 1;
// 	if (is_empty(s))
// 		return ;
// 	while ((*s)[i] && (*s)[i] != '"')
// 	{
// 		if ((*s)[i] == '$')
// 			double_quote_dollar_handler(s, result, shell);
// 		else
// 		{
// 			while ((*s)[i] && (*s)[i] != '$' && (*s)[i] != '"')
// 				i++;
// 			temp = ft_substr(&(*s)[0], 0, i);
// 			*result = ft_strjoin_free(*result, temp);
// 			*s += i;
// 		}
// 	}
// 	*s += 1;
// }

// ***********Original*************
void	double_quote_handler(char **s, char **result, t_shell *shell)
{
	int	i;
	char	*temp;

	*s += 1;
	if (is_empty(s))
		return ;
	while (**s && **s != '\"')
	{
		if (**s == '$')
			double_quote_dollar_handler(s, result, shell);
		if (**s && **s != '$')
		{
			i = 0;
			while ((*s)[i] && (*s)[i] != '$' && (*s)[i] != '\"')
				i++;
			temp = ft_substr(& *(s)[0], 0, i);
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
	// if (!temp || temp[0] == '\0') // Handle empty variable expansion
    // {
    //     free(temp);
    //     return;
    // }
	*result = ft_strjoin_free(*result, temp);
}

// void	dollar_sign_handler(char **s, char **result, t_shell *shell)
// {
// 	char	*temp;

// 	*s += 1;
// 	if (**s == '\'')
// 		single_quote_handler(s, result);
// 	if (**s == '"')
// 		double_quote_handler(s, result, shell);
// 	else
// 	{
// 		temp = var_expansion(s, shell);
// 		*result = ft_strjoin_free(*result, temp);
// 	}
// 	//printf("dollar_sign_handler: **s = %i\n", **s);
// }

void	dollar_sign_handler(char **s, char **result, t_shell *shell)
{
	char	*temp;

	if ((*s)[1] == '\'')
	{
		*s += 1;
		single_quote_handler(s, result);
	}
	else if ((*s)[1] == '"')
	{
		*s += 1;
		double_quote_handler(s, result, shell);
	}
	else
	{
		temp = var_expansion(s, shell);
		// if (!temp || temp[0] == '\0') // Handle empty variable expansion
        // {
        //     free(temp);
        //     return;
        // }
		*result = ft_strjoin_free(*result, temp);
	}
}

void	character_handler(char **s, char **result)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\'' && (*s)[i] != '"' && (*s)[i] != '$')
		i++;
	temp = ft_substr(&(*s)[0], 0, i);
	*result = ft_strjoin_free(*result, temp);
	*s += i;
}
