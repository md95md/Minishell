/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 00:47:21 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/31 13:35:34 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 2
# endif

void	*ft_gnl_calloc(size_t size, size_t count);
int		ft_gnl_strlen(char *s);
char	*ft_gnl_strjoin(const char *s1, const char *s2);
char	*ft_gnl_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif
