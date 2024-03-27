/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:53:46 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/06 16:28:03 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	t_chaine(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	x;

	if (big == 0 && n == 0)
		return (0);
	i = 0;
	if (!little[0])
		return ((char *)&big[0]);
	while (big[i] && i < n)
	{
		x = 0;
		while (little[x] && little[x] == big[i + x] && i + x < n)
			x++;
		if (x == t_chaine(little))
		{
			return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}
