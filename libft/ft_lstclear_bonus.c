/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:01:06 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/14 15:01:09 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tampon;
	t_list	*buffer;

	if (!lst || !del)
		return ;
	buffer = *lst;
	while (buffer)
	{
		tampon = buffer->next;
		ft_lstdelone(buffer, del);
		buffer = tampon;
	}
	*lst = NULL;
}
