/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:40:36 by kdaumont          #+#    #+#             */
/*   Updated: 2024/03/17 17:26:34 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *content)
{
	t_env	*node;
	int		pos;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	pos = ft_strchrpos(content, '=');
	if (pos == -1)
		return (NULL);
	node->key = ft_substr(content, 0, pos);
	node->value = ft_substr(content, pos + 1, ft_strlen(content + pos));
	node->next = NULL;
	node->before = NULL;
	return (node);
}

t_env	*env_last(t_env *list)
{
	if (list)
		while (list->next)
			list = list->next;
	return (list);
}

t_env	*env_get(t_env *list, char *key)
{
	while (list)
	{
		if (!strcmp(key, list->key))
			return (list);
		list = list->next;
	}
	return (NULL);
}

int	env_add_back(t_env **list, t_env *node)
{
	t_env	*last;

	if (!node)
		return (EXIT_FAILURE);
	if (!*list)
	{
		*list = node;
		return (EXIT_SUCCESS);
	}
	last = env_last(*list);
	node->next = last->next;
	node->before = last;
	last->next = node;
	return (EXIT_SUCCESS);
}

void	env_clear(t_env **list)
{
	t_env	*next;

	if (!list)
		return ;
	while (*list)
	{
		next = (*list)->next;
		free((*list)->key);
		free((*list)->value);
		free(*list);
		*list = next;
	}
	*list = NULL;
}
