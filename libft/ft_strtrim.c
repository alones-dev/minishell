/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:38:28 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/02 13:21:34 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	t_chaine(const char *c)
{
	int	x;

	x = 0;
	while (c[x])
		x++;
	return (x);
}

static int	search_set(int c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static char	*recopie(char *chaine, const char *str, int d, int f)
{
	int	i;

	i = 0;
	while (d < f)
	{
		chaine[i] = str[d];
		d++;
		i++;
	}
	chaine[i] = '\0';
	return (chaine);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		debut;
	int		fin;
	char	*new_chaine;

	if (!s1 || !set)
		return (0);
	debut = 0;
	fin = t_chaine(s1);
	while (search_set(s1[debut], set))
		debut++;
	while (search_set(s1[fin - 1], set))
		fin--;
	if (fin - debut < 0)
	{
		fin = 0;
		debut = 0;
	}
	new_chaine = malloc(sizeof(char) * (fin - debut + 1));
	if (!new_chaine)
		return (NULL);
	new_chaine = recopie(new_chaine, s1, debut, fin);
	return (new_chaine);
}
