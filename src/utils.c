/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:22:34 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/30 14:27:15 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_error(const char *format, ...)
// {
//     va_list args;
//     va_start(args, format);
//     vfprintf(stderr, format, args);
//     va_end(args);
// }

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}