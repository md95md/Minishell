/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redir_token_heredoc.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:55:04 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/30 16:46:27 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*generate_temp_filename(void)
{
	static int	tmp_file_id;
	char		*tmp_file_id_char;
	char		*tmp_filename;
	char		*prefix;

	tmp_file_id = 0;
	prefix = "heredoc_tmp_";
	tmp_file_id_char = ft_itoa(tmp_file_id);
	if (!tmp_file_id_char)
		return (NULL);
	tmp_filename = ft_strjoin(prefix, tmp_file_id_char);
	free(tmp_file_id_char);
	if (!tmp_filename)
		return (NULL);
	tmp_file_id++;
	return (tmp_filename);
}

void	heredoc_get_input(t_redir *redir)
{
	char	*delimiter;
	char	*heredoc_line;
	int		heredoc_fd;

	delimiter = redir->file;
	*redir->end_file = 0;
	redir->temp_file = generate_temp_filename();
	if (!redir->temp_file)
		return ;
	heredoc_fd = open(redir->temp_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (heredoc_fd < 0)
	{
		free(redir->temp_file);
		return ;
	}
	while (true)
	{
		heredoc_line = readline("< ");
		if (!heredoc_line || !ft_strcmp(heredoc_line, delimiter))
		{
			free(heredoc_line);
			break ;
		}
		ft_putstr_fd(heredoc_line, heredoc_fd);
		ft_putchar_fd('\n', heredoc_fd);
		free(heredoc_line);
	}
	close(heredoc_fd);
}
