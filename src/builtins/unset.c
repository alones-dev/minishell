/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/03/23 14:51:43 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_minishell *ms, char **cmd)
{
	int		i;
	t_env	*node;

	i = 0;
	while (cmd[++i])
	{
		node = env_get(ms->env, cmd[i]);
		if (!node)
			continue ;
		free(node->value);
		free(node->key);
		if (node->next != NULL)
		{
			node->before->next = node->next;
			node->next->before = node->before;
		}
		else
			node->before->next = NULL;
		free(node);
	}
	free_all(ms, cmd);
	ms->code = 0;
}
