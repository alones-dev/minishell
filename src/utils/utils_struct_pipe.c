/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:21:15 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/22 10:30:26 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe	*ft_lstlast_pipe(t_pipe *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_pipe	*ft_lstnew_pipe(int index)
{
	t_pipe	*new_valeur;

	new_valeur = malloc(sizeof(t_pipe));
	if (!new_valeur)
		return (NULL);
	new_valeur->index = index;
	new_valeur->next = NULL;
	return (new_valeur);
}

void	ft_lstadd_back_pipe(t_pipe **lst, t_pipe *new)
{
	t_pipe	*new_valeur;

	if (!lst || !new)
		return ;
	new_valeur = ft_lstlast_pipe(*lst);
	if (!new_valeur)
	{
		new->prev = NULL;
		*lst = new;
	}
	else
	{
		new->prev = new_valeur;
		new_valeur->next = new;
	}
}

void	free_pipe_struct(t_pipe **list)
{
	t_pipe	*next;

	if (!*list)
		return ;
	while ((*list)->prev)
		(*list) = (*list)->prev;
	while (*list)
	{
		next = (*list)->next;
		free(*list);
		*list = next;
	}
	free(*list);
	*list = NULL;
}

int	set_pipe(int nb_pipe, t_pipe **fd_pipe)
{
	int		i;
	t_pipe	*temp;
	t_pipe	*temp2;

	i = 0;
	while (i <= nb_pipe)
	{
		temp = ft_lstnew_pipe(i);
		ft_lstadd_back_pipe(fd_pipe, temp);
		i++;
	}
	temp2 = *fd_pipe;
	while (temp2)
	{
		if (pipe(temp2->pipe))
			strerror(errno);
		temp2 = temp2->next;
	}
	return (1);
}
