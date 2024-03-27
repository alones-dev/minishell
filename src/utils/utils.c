/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:26:39 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/19 14:43:30 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_instruct(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned int	result;

	if (!s1)
		return (-1);
	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i]
		&& (unsigned char)s1[i] == (unsigned char)s2[i])
		i++;
	result = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (result);
}

char	*ft_strjoin_letter(const char *s1, char const s2)
{
	unsigned int	i;
	unsigned int	compteur;
	unsigned int	len;
	char			*new_chaine;

	if (!s1)
		len = 0;
	else
		len = ft_strlen(s1);
	new_chaine = ft_calloc(sizeof(char), (len + 2));
	if (!new_chaine)
		return (NULL);
	i = 0;
	compteur = 0;
	while (i < len)
	{
		new_chaine[compteur] = s1[i];
		i++;
		compteur++;
	}
	new_chaine[compteur] = s2;
	new_chaine[compteur + 1] = '\0';
	return (new_chaine);
}

char	*ft_join(char *s1, char s2)
{
	char	*temp;

	temp = ft_strjoin_letter(s1, s2);
	free(s1);
	return (temp);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*temp;

	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}
