/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaleeva <agaleeva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:55:04 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/02 17:43:56 by agaleeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clean_and_exit(t_shell *shell)
{
    t_env   *tmp;

    while (shell->env)
    {
        tmp = shell->env;
        shell->env = shell->env->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
    }
    free_arr(shell->env_arr);
    free(shell);
    exit(0);
}

void free_tree(t_token *token)
{
    if (!token)
        return ;
    if (token->type == PIPE)
    {
        free_tree(((t_pipe *)token)->left);
        free_tree(((t_pipe *)token)->right);
    }
    else if (token->type == REDIR)
        free_tree(((t_redir *)token)->subcmd);
    else
    {
        free_arr(((t_cmd *)token)->av);
        free(token);
    }
}