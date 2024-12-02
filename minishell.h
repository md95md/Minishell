/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:36:54 by plesukja          #+#    #+#             */
/*   Updated: 2024/11/26 13:15:35 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libft.h"
# include <readline/readline.h> //readline
# include <readline/history.h> //add_history
# include <unistd.h>
# include <signal.h>
# include <stdbool.h> //bool
# include <sys/fcntl.h> //open

# define WHITESPACE " \t\r\n\v"
# define signS "><|"

typedef enum e_cmd_oprt_type
{
	COMMAND,
	REDIR,
	PIPE
}   t_token_type;

typedef struct s_cmd_oprt
{
	t_token_type	type;
}	t_token;

typedef struct s_pipe
{
	t_token_type	type;
	t_token			*left;
	t_token			*right;
}   t_pipe;

typedef struct s_redir
{
	t_token_type	type;
	t_token			*prior_token;
	int				mode;
	char			*file;
	char			*end_file;
	char			*temp_file;
}   t_redir;

typedef struct s_cmd
{
	t_token_type		type;
	char				*av[];
	char				*end_av[];
}   t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char			**env_arr;
	t_env			*env;
	t_token		*current_cmd;
	int				has_pipe;
	int				exit_status;
	int				default_stdin;
	int				default_stdout;
	int				in_fd;
	int				out_fd;
}	t_shell;