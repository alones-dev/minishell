/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:46:32 by kdaumont          #+#    #+#             */
/*   Updated: 2024/03/24 18:34:05 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_pipe *pipe)
{
	while (pipe)
	{
		close(pipe->pipe[0]);
		close(pipe->pipe[1]);
		pipe = pipe->next;
	}
}

int	wait_childs(int pid)
{
	int	wstatus;
	int	code;

	code = 0;
	while (1)
	{
		pid = waitpid(-1, &wstatus, 0);
		if (pid == -1)
			break ;
		if (WIFEXITED(wstatus))
			code = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGINT)
				code = 130;
			else if (WTERMSIG(wstatus) == SIGSEGV)
				code = 0;
			else if (WTERMSIG(wstatus) == SIGSEGV)
				code = 131;
		}
	}
	return (code);
}

void	fork_utils(pid_t id, t_instruct *instruc, t_pipe **fd_pipe,
		t_minishell *ms)
{
	if (id == -1)
		strerror(errno);
	if (id == 0)
	{
		close_connection(*fd_pipe, ms->temp_int);
		redirect_connection(*fd_pipe, ms->temp_int);
		ms->int_tab = malloc(sizeof(int) * (nb_ope(instruc, ms->temp_int) + 1));
		if (!ms->int_tab)
		{
			ms->code = 2;
			return ;
		}
		exec_cmd_n(instruc, fd_pipe, ms->temp_int, ms);
	}
}

void	pipex_n(t_minishell *ms, t_instruct *instruc, int nb_pipe)
{
	pid_t	id;
	t_pipe	**fd_pipe;
	t_pipe	*first;

	ms->temp_int = 0;
	ms->all_pipe = NULL;
	fd_pipe = malloc(sizeof(t_pipe));
	*fd_pipe = NULL;
	if (set_pipe(nb_pipe, fd_pipe) == 0)
		return ;
	first = *fd_pipe;
	ms->all_pipe = fd_pipe;
	if (sigaction(SIGINT, &ms->signal, NULL) == -1)
		printf("error\n");
	set_signal_here_doc(instruc, ms);
	while (ms->temp_int <= nb_pipe)
	{
		id = fork();
		fork_utils(id, instruc, fd_pipe, ms);
		ms->temp_int++;
	}
	(close_pipe(*fd_pipe), ms->code = wait_childs(id));
	*fd_pipe = first;
	(free_pipe_struct(fd_pipe), free(fd_pipe));
}
