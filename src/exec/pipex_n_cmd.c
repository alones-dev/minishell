/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_n_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:55:21 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/23 14:45:37 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution_n(t_minishell *ms, char *the_cmd, char **cmd, t_pipe **pipe)
{
	char	**env;

	free(ms->int_tab);
	if (!the_cmd)
		(free_el(cmd, &ms->env, ms->all_cmd, pipe), exit(0));
	if (!handle_builtins(the_cmd, cmd, ms, *ms->all_cmd))
	{
		if (!find_the_one_path(ms, the_cmd))
		{
			ft_putstr_fd(the_cmd, 2);
			ft_putstr_fd(": Command not found\n", 2);
			free_el(cmd, &ms->env, ms->all_cmd, pipe);
			free(pipe);
			exit(127);
		}
		env = env_collapse(ms->env);
		if (execve(find_the_one_path(ms, the_cmd), cmd, env) == -1)
		{
			perror(the_cmd);
			free_el(cmd, &ms->env, ms->all_cmd, pipe);
			exit(127);
		}
	}
	else
		exit(ms->code);
}

void	create_cmd_n(char **cmd, t_instruct *instruct, int index)
{
	int	i;

	i = 0;
	while (instruct)
	{
		if (instruct->index == index && instruct->role == NULL
			&& ft_strncmp(instruct->type, "OPERATOR") != 0)
		{
			cmd[i] = ft_strdup(instruct->instruct);
			i++;
		}
		instruct->index = -1;
		instruct = instruct->next;
	}
	cmd[i] = NULL;
}

int	nb_ope(t_instruct *lst, int index)
{
	int	nb_ope;

	nb_ope = 0;
	while (lst)
	{
		if (lst->index == index && ft_strncmp(lst->type, "OPERATOR") == 0
			&& ft_strncmp(lst->instruct, "|") != 0)
			nb_ope++;
		lst = lst->next;
	}
	return (nb_ope);
}

void	close_connection(t_pipe *pipe, int index)
{
	int	i;

	i = 0;
	while (pipe)
	{
		if (index != i || index == 0)
			close(pipe->pipe[0]);
		if (index + 1 != i)
			close(pipe->pipe[1]);
		pipe = pipe->next;
		i++;
	}
}

void	redirect_connection(t_pipe *pipe, int index)
{
	int	i;

	i = 0;
	while (pipe)
	{
		if (index == i && index != 0)
		{
			dup2(pipe->pipe[0], 0);
			close(pipe->pipe[0]);
		}
		if (index + 1 == i)
		{
			dup2(pipe->pipe[1], 1);
			close(pipe->pipe[1]);
		}
		pipe = pipe->next;
		i++;
	}
}
