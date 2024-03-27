/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:21:21 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/06 15:24:37 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		p;
	const char	*new_chaine;
	int			i;
	int			compteur;

	p = c;
	i = 0;
	compteur = 0;
	while (s[i])
	{
		if (s[i] == p)
		{
			new_chaine = &s[i];
			compteur++;
		}
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	else if (compteur == 0)
		return (0);
	return ((char *)new_chaine);
}
