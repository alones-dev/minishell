/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/03/23 14:44:47 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	utils_exit_re(t_minishell *ms, char **cmd, char *str)
{
	ms->code = ft_atoi(cmd[1]);
	str = ft_itoa(ms->code);
	if (!str)
		return ;
	if (ft_strncmp(cmd[1], str) != 0)
	{
		printf("minishell: exit: numeric argument required\n");
		ms->code = 2;
	}
	free(str);
}

int	utils_exit(t_minishell *ms, char **cmd, char *str)
{
	ms->code = ft_atoi(cmd[1]);
	str = ft_itoa(ms->code);
	if (!str)
		return (0);
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	if (ft_strncmp(cmd[1], str) == 0)
	{
		ms->code = 1;
		return (free(str), 0);
	}
	(free(str), ms->code = 2);
	return (1);
}

void	ft_exit(t_minishell *ms, char **cmd, t_instruct *s_cmd)
{
	int		len;
	int		t;
	char	*str;

	str = NULL;
	ft_putstr_fd("exit\n", 2);
	if (g_global == SIGINT)
		ms->code = 130;
	len = ft_stralen(cmd);
	if (len > 2)
	{
		if (!utils_exit(ms, cmd, str))
		{
			free_tab(cmd);
			return ;
		}
	}
	else if (len == 2)
		utils_exit_re(ms, cmd, str);
	t = ms->code;
	free_el(cmd, &ms->env, &s_cmd, NULL);
	free(ms->all_cmd);
	free(ms);
	exit(t);
}
