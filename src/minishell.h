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

# include "../libft/libft/libft.h"
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
void	print_sorted_env(t_env **env);
void	add_or_update_env_var(t_env **env, char *var);
bool	is_valid_key(char *var);
void print_error(const char *format, ...);
char	**env_to_arr(t_env *env, char **old_envp);
int ft_strcmp(const char *s1, const char *s2);
void	unset_env_arr(t_env **env, char *var);
void	handle_cd_error(t_shell *shell, char *msg, char *old_pwd);
bool	has_too_many_arguments(char **args);
void	update_path_var(t_env *env, char *old_pwd, char *new_pwd);
int change_directory(t_shell *shell, char **args, char *old_pwd);
void update_path_var(t_env *env, char *old_pwd, char *new_pwd);
void add_or_update_env_var(t_env **env, char *var);
void handle_cd_error(t_shell *shell, char *msg, char *old_pwd);
void	free_array(char **array);
void	sort_env(t_env **env);
void	free_env(t_env **env);
bool	add_dup_node_in_new_env(t_env *dup_node, t_env **new_env, t_env **tail);
void	compare_and_swap_node(t_env	**cur, t_env **prev, bool *sorted_env);
t_env	*clone_env(t_env **env);
t_env	*duplicate_node(t_env *node);
bool	add_dup_node_in_new_env(t_env *dup_node, t_env **new_env, t_env **tail);
void	compare_and_swap_node(t_env	**cur, t_env **prev, bool *sorted_env);
bool	find_existed_node_and_update(t_env **env, char *inp_key, char *inp_value);
void	append_new_node_in_env(t_env **env, char *inp_key, char *inp_value);
int	split_var_into_input_key_value(char *var, char **inp_key, char **inp_value);
void	run_builtin_unset(t_shell *shell, char **args);