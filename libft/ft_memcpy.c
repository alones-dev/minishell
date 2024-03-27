/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:47:56 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/16 11:18:26 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	d = (char *)dest;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
