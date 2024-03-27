/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/03/23 14:51:28 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_or_replace(t_env **env, char *content)
{
	t_env	*node;
	char	*key;
	int		pos;

	pos = ft_strchrpos(content, '=');
	if (pos == -1)
		return ;
	key = ft_substr(content, 0, pos);
	node = env_get(*env, key);
	if (!node)
		env_add_back(env, env_new(content));
	else
		node->value = ft_substr(content, pos + 1, ft_strlen(content + pos));
	free(key);
}

static void	bubble_sort(t_env **env)
{
	t_env	*temp;
	char	*temp2;
	bool	sorted;

	sorted = false;
	while (!sorted)
	{
		sorted = true;
		temp = *env;
		while (temp->next)
		{
			if (ft_strcmp(temp->key, temp->next->key) > 0)
			{
				sorted = false;
				temp2 = temp->key;
				temp->key = temp->next->key;
				temp->next->key = temp2;
				temp2 = temp->value;
				temp->value = temp->next->value;
				temp->next->value = temp2;
			}
			temp = temp->next;
		}
	}
}

static void	env_dup(t_env *src, t_env **dst)
{
	t_env	*node;

	while (src)
	{
		node = ft_calloc(1, sizeof(*node));
		node->before = NULL;
		node->next = NULL;
		node->key = ft_strdup(src->key);
		node->value = ft_strdup(src->value);
		env_add_back(dst, node);
		src = src->next;
	}
}

static int	print_env(t_env *env, t_minishell *ms, char **cmd, int state)
{
	if (state == 0)
	{
		if (cmd[1] && cmd[1][0] == '_' && cmd[1][1] == '=')
		{
			ms->code = 0;
			return (0);
		}
	}
	else
	{
		while (env)
		{
			printf("export %s=\"%s\"\n", env->key, env->value);
			env = env->next;
		}
		return (1);
	}
	return (1);
}

void	ft_export(t_minishell *ms, char **cmd)
{
	size_t	i;
	t_env	*senv;

	if (print_env(ms->env, ms, cmd, 0) == 0)
		return ;
	if (cmd[1] && (cmd[1][0] != '_' && !(ft_isalpha(cmd[1][0]))))
	{
		ms->code = 1;
		printf("minishell: export: `%s': not a valid identifier\n", cmd[1]);
		return ;
	}
	if (!cmd[1])
	{
		senv = NULL;
		env_dup(ms->env, &senv);
		(bubble_sort(&senv), print_env(senv, ms, cmd, 1), env_clear(&senv));
	}
	else
	{
		i = 0;
		while (cmd[++i])
			add_or_replace(&ms->env, cmd[i]);
	}
	free_all(ms, cmd);
	ms->code = 0;
}
