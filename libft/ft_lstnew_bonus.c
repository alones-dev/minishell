/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:05:04 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/10 17:45:53 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_valeur;

	new_valeur = malloc(sizeof(t_list));
	if (!new_valeur)
		return (NULL);
	new_valeur->content = content;
	new_valeur->next = NULL;
	return (new_valeur);
}
