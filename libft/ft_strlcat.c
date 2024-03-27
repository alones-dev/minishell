/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:46:48 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/07 17:24:36 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	t_dest;
	size_t	t_src;

	t_dest = 0;
	t_src = 0;
	i = 0;
	while (src[t_src])
		t_src++;
	while (t_dest < size && dest[t_dest])
		t_dest++;
	if (!size)
		return (t_src);
	while ((i + t_dest + 1) < size && src[i])
	{
		dest[t_dest + i] = src[i];
		i++;
	}
	if (t_dest < size)
		dest[t_dest + i] = '\0';
	while (src[i])
		i++;
	return (i + t_dest);
}
