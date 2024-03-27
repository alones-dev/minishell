/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/03/23 14:49:48 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *ms, char **cmd)
{
	t_env	*senv;

	if (ft_stralen(cmd) > 1)
	{
		if (access(cmd[1], F_OK) == 0)
		{
			printf("env: %s: Permission denied\n", cmd[1]);
			ms->code = 126;
		}
		else
		{
			printf("env: %s: No such file or directory\n", cmd[1]);
			ms->code = 127;
		}
		return ;
	}
	senv = ms->env;
	while (senv)
	{
		if (senv->value)
			printf("%s=%s\n", senv->key, senv->value);
		senv = senv->next;
	}
	ms->code = 0;
	free_all(ms, cmd);
}
