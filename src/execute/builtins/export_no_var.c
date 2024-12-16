/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _export_no_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plesukja <plesukja@42bangkok.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:17:57 by plesukja          #+#    #+#             */
/*   Updated: 2024/12/11 13:21:44 by plesukja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_sorted_env(t_env **env)
{
	t_env	*cloned_env;
	t_env	*cur;

	cloned_env = clone_env(env);
	sort_env(&cloned_env);
	cur = cloned_env;
	while (cur)
	{
		if (!cur->value)
			printf("declare -x %s\n", cur->key);
		else
			printf("declare -x %s=\"%s\"\n", cur->key, cur->value);
		cur = cur->next;
	}
	free_env (&cloned_env); //free_env
}

t_env	*clone_env(t_env **env)
{
	t_env	*cloned_env;
	t_env	*cur;
	t_env	*tail;
	t_env	*dup_node;

	if (!env || !*env)
		return (NULL);
	cloned_env = NULL;
	cur = *env;
	tail = NULL;
	while (cur)
	{
		dup_node = duplicate_node(cur);
		if (!dup_node)
		{
			free_env(&cloned_env);
			return (NULL);
		}
		add_dup_node_in_new_env(dup_node, &cloned_env, &tail);
		cur = cur->next;
	}
	return (cloned_env);
}

t_env	*duplicate_node(t_env *node)
{
	t_env	*new_node;

	if (!node)
		return (NULL);
	new_node = malloc (sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(node->key);
	new_node->value = ft_strdup(node->value);
	new_node->next = NULL;
	if (!new_node->key || (node->value && !new_node->value))
	{
		if (new_node->key)
			free (new_node->key);
		if (new_node->value)
			free (new_node->value);
		free (new_node);
		return (NULL);
	}
	return (new_node);
}

bool add_dup_node_in_new_env(t_env *dup_node, t_env **new_env, t_env **tail)
{
	if (!dup_node)
		return false;
	if (!*new_env)
		*new_env = dup_node;
	else
		(*tail)->next = dup_node;
	*tail = dup_node;
	return true;
}

void	sort_env(t_env **env)
{
	bool	sorted_env;
	t_env	**cur;
	t_env	**prev;

	if (!env || !*env)
		return ;
	while (1)
	{
		sorted_env = true;
		cur = env;
		prev = env;
		while (*cur && (*cur)->next)
		{
			compare_and_swap_node(prev, cur, &sorted_env);
			prev = &(*cur)->next;
			cur = &(*cur)->next;
		}
		if (sorted_env)
			break ;
	}
}

void	compare_and_swap_node(t_env	**cur, t_env **prev, bool *sorted_env)
{
	t_env	*tmp;

	if (ft_strcmp((*cur)->key, (*cur)->next->key) > 0)
	{
		tmp = (*cur)->next;
		(*cur)->next = tmp->next;
		tmp->next = *cur;
		if (*prev == *cur)
			*prev = tmp;
		else
			(*prev)->next = tmp;
		*cur = tmp;
		*sorted_env = false;
	}
}
