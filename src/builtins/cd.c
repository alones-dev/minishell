/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:03:14 by kdaumont          #+#    #+#             */
/*   Updated: 2024/03/23 14:54:31 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_utils(t_minishell *ms, char **cmd, int state)
{
	if (state == 0)
	{
		if (chdir(env_get_value(ms, "HOME")) == -1)
		{
			ms->code = 127;
			perror(env_get_value(ms, "HOME"));
			return (1);
		}
	}
	else
	{
		if (chdir(cmd[1]) == -1)
		{
			ms->code = 127;
			perror(cmd[1]);
			return (1);
		}
	}
	return (0);
}

void	set_pwd(t_minishell *ms, char *oldpwd)
{
	char	*pwd;

	if (oldpwd)
	{
		pwd = getcwd(NULL, 0);
		env_get(ms->env, "PWD")->value = pwd;
		env_get(ms->env, "OLDPWD")->value = oldpwd;
	}
}

void	ft_cd(t_minishell *ms, char **cmd)
{
	char	*oldpwd;

	oldpwd = env_get_value(ms, "PWD");
	if (ft_stralen(cmd) == 1)
	{
		if (cd_utils(ms, cmd, 0))
			return ;
	}
	else if (ft_stralen(cmd) == 2)
	{
		if (cd_utils(ms, cmd, 1))
			return ;
	}
	else
	{
		(printf("cd: too many arguments\n"), ms->code = 1);
		return ;
	}
	set_pwd(ms, oldpwd);
	free_all(ms, cmd);
	ms->code = 0;
}
