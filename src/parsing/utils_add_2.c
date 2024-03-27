/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_add_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:44:59 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/22 15:44:50 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtins(char *name, char **cmd, t_minishell *ms, t_instruct *s_cmd)
{
	if (ft_strcmp(name, "echo") == 0)
		return (ft_echo(ms, cmd, s_cmd), 1);
	if (ft_strcmp(name, "cd") == 0)
		return (ft_cd(ms, cmd), 1);
	if (ft_strcmp(name, "pwd") == 0)
		return ((void)ft_pwd(ms, cmd), 1);
	if (ft_strcmp(name, "export") == 0)
		return (ft_export(ms, cmd), 1);
	if (ft_strcmp(name, "unset") == 0)
		return (ft_unset(ms, cmd), 1);
	if (ft_strcmp(name, "env") == 0)
		return (ft_env(ms, cmd), 1);
	if (ft_strcmp(name, "exit") == 0)
		return (ft_exit(ms, cmd, s_cmd), 1);
	return (0);
}

int	check_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	check_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}
