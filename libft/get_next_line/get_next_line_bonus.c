/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 17:24:26 by plesukja          #+#    #+#             */
/*   Updated: 2024/04/08 16:14:26 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_find_new_line(int fd, char *file_read);
char	*ft_extract_line(char *file_read);
char	*ft_get_remain(char *file_read);

char	*get_next_line(int fd)
{
	static char	*file_read[1000];
	char		*extract_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1000)
		return (NULL);
	file_read[fd] = ft_find_new_line(fd, file_read[fd]);
	if (!file_read[fd])
		return (NULL);
	extract_line = ft_extract_line(file_read[fd]);
	file_read[fd] = ft_get_remain(file_read[fd]);
	return (extract_line);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	return (tmp);
}

char	*ft_find_new_line(int fd, char *file_read)
{
	int		num_read;
	char	*buffer;

	if (!file_read)
		file_read = ft_calloc(sizeof(char), 1);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (free(buffer), free(file_read), (NULL));
	num_read = 1;
	while (num_read > 0)
	{
		num_read = read(fd, buffer, BUFFER_SIZE);
		if (num_read == 0)
			break ;
		if (num_read == -1)
			return (free(buffer), free(file_read), (NULL));
		buffer[num_read] = '\0';
		file_read = ft_strjoin_free(file_read, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), file_read);
}

char	*ft_extract_line(char *file_read)
{
	char	*result;
	int		index;

	index = 0;
	if (!file_read[index])
		return (NULL);
	while (file_read[index] && file_read[index] != '\n')
		index++;
	result = ft_calloc(sizeof(char), index + 2);
	if (!result)
		return (NULL);
	index = 0;
	while (file_read[index] && file_read[index] != '\n')
	{
		result[index] = file_read[index];
		index++;
	}
	if (file_read[index] && file_read[index] == '\n')
	{
		result[index] = file_read[index];
		index++;
	}
	return (result);
}

char	*ft_get_remain(char *file_read)
{
	int		index;
	int		result_index;
	char	*result;

	index = 0;
	while (file_read[index] && file_read[index] != '\n')
		index++;
	if (!file_read[index])
		return (free(file_read), (NULL));
	result = ft_calloc(sizeof(char), ft_strlen(file_read) - index + 1);
	if (!result)
		return (free(file_read), (NULL));
	index++;
	result_index = 0;
	while (file_read[index])
	{
		result[result_index] = file_read[index];
		result_index++;
		index++;
	}
	free(file_read);
	return (result);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	fd1 = open("test_bonus1.text", O_RDONLY);
	if (fd1 == -1)
	{
        perror("Error opening file");
        return 1;
    }
	printf("%s", get_next_line(fd1));
	fd2 = open("test_bonus2.text", O_RDONLY);
	if (fd2 == -1)
	{
        perror("Error opening file");
        return 1;
    }
	printf("%s", get_next_line(fd2));
	fd3 = open("test_bonus3.text", O_RDONLY);
	if (fd3 == -1)
	{
        perror("Error opening file");
        return 1;
    }
	printf("%s", get_next_line(fd3));
	printf("%s", get_next_line(fd2));
	printf("%s//", get_next_line(fd3));
	printf("%s", get_next_line(fd3));
}
*/