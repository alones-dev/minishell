/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:16:41 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/18 15:48:32 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	compteur;
	char			*new_chaine;

	if (!s1 || !s2)
		return (0);
	i = 0;
	compteur = 0;
	new_chaine = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +1));
	if (!new_chaine)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		new_chaine[compteur] = s1[i];
		i++;
		compteur++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		new_chaine[compteur++] = s2[i];
		i++;
	}	
	new_chaine[compteur] = '\0';
	return (new_chaine);
}

char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*join;
	size_t	length;

	if (!s1 || !s2 || !s3)
		return (NULL);
	length = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	join = ft_calloc(length, 1);
	if (!join)
		return (NULL);
	ft_strlcat(join, s1, length);
	ft_strlcat(join, s2, length);
	ft_strlcat(join, s3, length);
	return (join);
}
