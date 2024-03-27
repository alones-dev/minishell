/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:17:21 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/13 15:17:23 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*new_valeur;

	if (!lst || !new)
		return ;
	new_valeur = ft_lstlast(*lst);
	if (!new_valeur)
		*lst = new;
	else
		new_valeur->next = new;
}
