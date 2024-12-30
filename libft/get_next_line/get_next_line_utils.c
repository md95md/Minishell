/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:50:56 by plesukja          #+#    #+#             */
/*   Updated: 2024/03/28 11:59:21 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t size, size_t count)
{
	char	*tmp;
	size_t	i;

	if ((count > 0 && __SIZE_MAX__ / count < size) || size <= 0 || count <= 0)
		return (NULL);
	tmp = malloc(size * count);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < size * count)
	{
		tmp[i] = '\0';
		i++;
	}
	return (tmp);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	int		i;
	int		result_len;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	result_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	result = malloc (sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != c)
		s++;
	if (*s == c)
		return ((char *)s);
	else
		return (NULL);
}
