/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:18:36 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/08 16:34:24 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	t_chaine(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new_chaine;

	if (!s || !f)
		return (0);
	i = 0;
	new_chaine = malloc(sizeof(char) * t_chaine(s) + 1);
	if (!new_chaine)
		return (NULL);
	while (s[i])
	{
		new_chaine[i] = f(i, s[i]);
		i++;
	}
	new_chaine[i] = '\0';
	return (new_chaine);
}
