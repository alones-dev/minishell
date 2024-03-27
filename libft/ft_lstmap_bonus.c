/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:34:57 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/20 17:18:31 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_struct;
	t_list	*content;

	if (!lst || !f || !del)
		return (NULL);
	new_struct = NULL;
	while (lst)
	{
		content = ft_lstnew(f(lst->content));
		if (!content)
		{
			ft_lstclear(&new_struct, del);
			return (0);
		}
		ft_lstadd_back(&new_struct, content);
		lst = lst->next;
	}
	return (new_struct);
}
