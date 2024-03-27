/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:54:20 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/08 10:50:42 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*c;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (nmemb > 4294967296 / size)
		return (NULL);
	c = malloc(nmemb * size);
	if (!c)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		c[i] = 0;
		i++;
	}
	return ((void *)c);
}
