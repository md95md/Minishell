/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleeva <agaleeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:36:54 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/02 17:47:07 by agaleeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../libft/libft/libft.h"
# include <readline/readline.h> //readline
# include <readline/history.h> //add_history
# include <unistd.h>
# include <signal.h>
# include <stdbool.h> //bool
# include <sys/stat.h> //stat

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
	t_token_type		type;
	t_token			*left;
	t_token			*right;
}   t_pipe;

typedef struct s_redir
{
	t_token_type		type;
	t_token			*subcmd;
}   t_redir;

typedef struct s_cmd
{
	t_token_type		type;
	char				**av;
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

void    clean_and_exit(t_shell *shell);
char	**get_env_arr(char **arr);
void	create_env_linked_list(t_env **env, char **envp);
t_token	*process_token(char *s);
char	*ft_strndup(char *src, size_t n);
char	*init_prompt(t_shell *shell);
bool	build_tree(t_shell *shell, char *input);
void free_tree(t_token *token);
char	*ft_getenv(t_env *env, char *key);
