/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:15:09 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/07 11:27:42 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*t;
	unsigned char	p;
	size_t			i;

	p = c;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		t = (unsigned char *)s;
		if (t[i] == p)
			return ((void *) &t[i]);
		i++;
	}
	return (0);
}
