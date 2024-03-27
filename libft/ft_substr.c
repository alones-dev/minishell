/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:01:44 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/07 18:18:26 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*new_chaine;

	if (!s)
		return (0);
	if (ft_strlen(s) < start)
		len = 0;
	if (len >= ft_strlen(s))
		len = ft_strlen(&s[start]);
	new_chaine = malloc(sizeof(char) * (len + 1));
	if (!new_chaine)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_chaine[i] = s[start + i];
		i++;
	}
	new_chaine[i] = '\0';
	return (new_chaine);
}
