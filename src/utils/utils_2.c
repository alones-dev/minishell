/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 17:30:44 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/25 09:35:02 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code(t_minishell *ms)
{
	if (g_global == SIGINT)
		return (130);
	else if (g_global == SIGSEGV)
		return (0);
	else if (g_global == SIGQUIT)
		return (131);
	else
		return (ms->code);
}

void	set_all_signal_null(t_minishell *ms)
{
	if (sigaction(SIGINT, &ms->ignore, NULL) == -1)
		printf("Erreur à l'enregistrement du gestionnaire de signaux !");
	if (sigaction(SIGSEGV, &ms->ignore, NULL) == -1)
		printf("Erreur à l'enregistrement du gestionnaire de signaux !");
	if (sigaction(SIGQUIT, &ms->ignore, NULL) == -1)
		printf("Erreur à l'enregistrement du gestionnaire de signaux !");
}

void	while_echo(t_minishell *ms, size_t *i, char **cmd, size_t len)
{
	while (cmd[*i])
	{
		if (is_arg_n(cmd[*i]) && ms->temp_int == 0)
		{
			(*i)++;
			continue ;
		}
		ms->temp_int = 1;
		is_var_env(ms, cmd[*i]);
		if (*i != len - 1)
			printf(" ");
		(*i)++;
	}
}
