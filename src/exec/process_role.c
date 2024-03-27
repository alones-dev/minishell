/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_role.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 13:14:27 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 18:29:04 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_read_file(t_instruct *cmd, int *fd,	int num)
{
	fd[num] = open(cmd->instruct, O_RDONLY, 0777);
	if (fd[num] == -1)
	{
		perror(cmd->instruct);
		return ;
	}
	if (dup2(fd[num], 0) == -1)
		strerror(errno);
	close(fd[num]);
}

void	process_here_doc(t_instruct *cmd, int *fd)
{
	char		*tmp;
	t_instruct	*temp;

	temp = cmd;
	tmp = NULL;
	here_doc(cmd->instruct);
	*fd = open("objs/FiChIeR_CaChE", O_RDONLY, 0777);
	if (*fd == -1)
		perror(cmd->instruct);
	temp = temp->prev;
	while (temp)
	{
		if (ft_strncmp(temp->type, "WORD") == 0)
		{
			tmp = temp->instruct;
			break ;
		}
		temp = temp->prev;
	}
	if (tmp && ft_strncmp(tmp, "echo") != 0 && check_here_doc(cmd) == 0)
		if (dup2(*fd, 0) == -1)
			strerror(errno);
	close(*fd);
}

void	process_write_file(t_instruct *cmd, int *fd, int num)
{
	fd[num] = open(cmd->instruct, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd[num] == -1)
		strerror(errno);
	if (dup2(fd[num], 1) == -1)
		strerror(errno);
	close(fd[num]);
}

void	process_add_write_file(t_instruct *cmd, int *fd, int num)
{
	fd[num] = open(cmd->instruct, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd[num] == -1)
		strerror(errno);
	if (dup2(fd[num], 1) == -1)
		strerror(errno);
	close(fd[num]);
}
