/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:06:45 by cornguye          #+#    #+#             */
/*   Updated: 2024/02/29 09:43:55 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	p;
	int		i;

	p = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == p)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}

int	ft_strchrpos(const char *s, int c)
{
	int	i;

	i = -1;
	c = c % 256;
	while (s[++i])
		if (s[i] == c)
			return (i);
	if (s[i] == c)
		return (i);
	return (-1);
}
