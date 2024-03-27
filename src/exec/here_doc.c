/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:07:54 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 18:34:23 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_doc(char *stop, char *all_in)
{
	int	fd;

	fd = open("objs/FiChIeR_CaChE", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		perror("objs/FiChIeR_CaChE");
	write(fd, all_in, ft_strlen(all_in));
	close(fd);
	free(all_in);
	free(stop);
}

void	here_doc(char *stop)
{
	char	*str_in;
	char	*all_in;

	stop = ft_strjoin(stop, "\n");
	all_in = ft_calloc(sizeof(char), 1);
	write(0, "> ", 2);
	str_in = get_next_line(0);
	while (str_in != NULL)
	{
		all_in = ft_strjoin_free(all_in, str_in);
		free(str_in);
		write(0, "> ", 2);
		str_in = get_next_line(0);
		if (str_in == NULL || ft_strncmp(stop, str_in) == 0)
			break ;
	}
	if (!str_in)
		printf("\n");
	free(str_in);
	handle_doc(stop, all_in);
}

int	check_here_doc(t_instruct *command)
{
	int	nb_here_doc;

	nb_here_doc = 0;
	while (command)
	{
		if (ft_strncmp(command->instruct, "<<") == 0)
			nb_here_doc++;
		command = command->next;
	}
	return (nb_here_doc);
}

void	set_signal_here_doc(t_instruct *list, t_minishell *ms)
{
	if (!check_here_doc(list))
	{
		if (sigaction(SIGQUIT, &ms->signal, NULL) == -1)
			printf("Erreur à l'enregistrement du gestionnaire de signaux !");
	}
	else
	{
		if (sigaction(SIGQUIT, &ms->ignore, NULL) == -1)
			printf("Erreur à l'enregistrement du gestionnaire de signaux !");
	}
}
