/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:44:16 by kdaumont          #+#    #+#             */
/*   Updated: 2024/03/24 18:34:12 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtins(t_instruct *instruct)
{
	if (ft_strcmp(instruct->instruct, "exit") == 0)
		return (1);
	else if (ft_strcmp(instruct->instruct, "cd") == 0)
		return (1);
	else if (ft_strcmp(instruct->instruct, "pwd") == 0)
		return (1);
	else if (ft_strcmp(instruct->instruct, "export") == 0)
		return (1);
	else if (ft_strcmp(instruct->instruct, "unset") == 0)
		return (1);
	else if (ft_strcmp(instruct->instruct, "env") == 0)
		return (1);
	return (0);
}

void	pipex_one(t_minishell *ms, t_instruct *instruct, int nb_operator)
{
	pid_t	id;

	if (sigaction(SIGINT, &ms->signal, NULL) == -1)
		printf("error\n");
	set_signal_here_doc(instruct, ms);
	while (instruct->index == -1)
		instruct = instruct->next;
	if (is_builtins(instruct))
		exec_cmd(instruct, ms, nb_operator);
	else
	{
		id = fork();
		if (id == -1)
		{
			strerror(errno);
			return ;
		}
		if (id == 0)
			exec_cmd(instruct, ms, nb_operator);
		ms->code = wait_childs(id);
	}
}

void	process_role_n(t_instruct **instruct, int *fd, int *compteur_operator)
{
	if (ft_strncmp((*instruct)->role, "FILE_READ") == 0)
		process_read_file(*instruct, fd, *compteur_operator);
	else if (ft_strncmp((*instruct)->role, "STOP_HEREDOC") == 0)
		process_here_doc(*instruct, &fd[*compteur_operator]);
	else if (ft_strncmp((*instruct)->role, "FILE_DEL_WRITE") == 0)
		process_write_file(*instruct, fd, *compteur_operator);
	else if (ft_strncmp((*instruct)->role, "FILE_ADD_WRITE") == 0)
		process_add_write_file(*instruct, fd, *compteur_operator);
	(*compteur_operator)++;
}

void	process_word_n(t_instruct *instruct, char **the_cmd, int *i, int index)
{
	if ((ft_strncmp(instruct->type, "WORD") == 0
			|| ft_strncmp(instruct->type, "OPTION") == 0
			|| ft_strncmp(instruct->type, "VA_ENV") == 0)
		&& instruct->index == index)
	{
		if (!(*the_cmd))
			*the_cmd = instruct->instruct;
		(*i)++;
	}
}

void	exec_cmd_n(t_instruct *instruct, t_pipe **pipe, int index,
		t_minishell *ms)
{
	t_instruct	*first;
	char		**cmd;
	char		*the_cmd;
	int			i;
	int			compteur_operator;

	first = instruct;
	i = 0;
	compteur_operator = 0;
	the_cmd = NULL;
	while (instruct)
	{
		if (instruct->role && instruct->index == index)
			process_role_n(&instruct, ms->int_tab, &compteur_operator);
		else
			process_word_n(instruct, &the_cmd, &i, index);
		instruct = instruct->next;
	}
	cmd = ft_calloc(sizeof(char *), i + 1);
	if (!cmd)
		return ;
	instruct = first;
	create_cmd_n(cmd, instruct, index);
	execution_n(ms, the_cmd, cmd, pipe);
}
