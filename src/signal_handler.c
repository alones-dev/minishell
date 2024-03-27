/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:12:31 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 18:28:32 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global = SIGINT;
	}
	else if (signal == SIGSEGV)
	{
		g_global = SIGSEGV;
		exit(EXIT_FAILURE);
	}
}

void	handler_in_cmd(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_global = SIGINT;
	}
	else if (signal == SIGSEGV)
	{
		g_global = 0;
		return ;
	}
	else if (signal == SIGQUIT)
	{
		g_global = SIGQUIT;
		ft_putstr_fd("Quit core dump!\n", 2);
	}
}

void	handler_here_doc(int signal)
{
	if (signal == SIGSEGV)
	{
		g_global = SIGSEGV;
		return ;
	}
}

void	set_ignore(t_minishell *ms)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	sigemptyset(&ignore.sa_mask);
	ignore.sa_flags = 0;
	ms->ignore = ignore;
}

void	set_signal_action(t_minishell *ms)
{
	struct sigaction	init;
	struct sigaction	sb;

	sb.sa_handler = handler_in_cmd;
	sigemptyset(&sb.sa_mask);
	sb.sa_flags = 0;
	init.sa_handler = signal_handler;
	sigemptyset(&init.sa_mask);
	init.sa_flags = 0;
	ms->signal = sb;
	if (sigaction(SIGINT, &init, NULL) == -1)
		printf("Erreur à l'enregistrement du gestionnaire de signaux !");
	if (sigaction(SIGSEGV, &init, NULL) == -1)
		printf("Erreur à l'enregistrement du gestionnaire de signaux !");
	if (sigaction(SIGQUIT, &ms->ignore, NULL) == -1)
		printf("Erreur à l'enregistrement du gestionnaire de signaux !");
	g_global = 0;
}
