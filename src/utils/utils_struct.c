/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:00:28 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/22 12:19:28 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_instruct	*ft_lstlast_instruct(t_instruct *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_instruct	*ft_lstnew_instruct(char *txt, char *type, int nb_pipe)
{
	t_instruct	*new_valeur;

	new_valeur = malloc(sizeof(t_instruct));
	if (!new_valeur)
		return (NULL);
	new_valeur->instruct = txt;
	new_valeur->type = type;
	new_valeur->index = nb_pipe;
	new_valeur->role = NULL;
	new_valeur->next = NULL;
	return (new_valeur);
}

void	ft_lstadd_back_instruct(t_instruct **lst, t_instruct *new)
{
	t_instruct	*new_valeur;

	if (!lst || !new)
		return ;
	new_valeur = ft_lstlast_instruct(*lst);
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

void	free_element_struct(t_instruct **list)
{
	t_instruct	*next;

	if (!list)
		return ;
	while ((*list)->prev)
		(*list) = (*list)->prev;
	while (*list)
	{
		next = (*list)->next;
		free((*list)->instruct);
		free(*list);
		*list = next;
	}
	free(*list);
	*list = NULL;
}

void	free_element_struct_end(t_instruct **list)
{
	t_instruct	*next;

	while (*list)
	{
		next = (*list)->next;
		free((*list)->instruct);
		free(*list);
		*list = next;
	}
	free(*list);
	free(list);
}
