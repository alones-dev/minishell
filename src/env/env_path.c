/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:43:00 by kdaumont          #+#    #+#             */
/*   Updated: 2024/03/18 10:07:00 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	env_size(t_env *list)
{
	size_t	i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**env_collapse(t_env *list)
{
	char	**env;
	size_t	i;

	env = ft_calloc(env_size(list) + 1, sizeof(*env));
	if (!env)
		return (NULL);
	i = 0;
	while (list)
	{
		env[i] = ft_strjoin3(list->key, "=", list->value);
		list = list->next;
		i++;
	}
	return (env);
}

char	*env_get_value(t_minishell *ms, char *key)
{
	t_env	*tmp;

	tmp = ms->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*find_the_one_path(t_minishell *ms, char *commande)
{
	int		i;
	char	**all_ways;
	char	*add_slash;
	char	*add_cmd;

	if (!commande)
		return (NULL);
	if (access(commande, X_OK) == 0)
		return (commande);
	i = 0;
	if (env_get_value(ms, "PATH") == NULL)
		return (NULL);
	all_ways = ft_split(env_get_value(ms, "PATH"), ':');
	while (all_ways[i])
	{
		add_slash = ft_strjoin(all_ways[i], "/");
		add_cmd = ft_strjoin(add_slash, commande);
		free(add_slash);
		if (access(add_cmd, F_OK | X_OK) == 0)
			return (add_cmd);
		free(add_cmd);
		i++;
	}
	free_tab(all_ways);
	return (NULL);
}
