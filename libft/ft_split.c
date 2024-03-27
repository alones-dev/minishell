/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:58:16 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/09 12:06:23 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static int	t_array(char const *str, char c)
{
	unsigned int	nb;
	int				i;

	nb = 0;
	i = 0;
	if (str[0] != c && str[0] != '\0')
		nb++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] && str[i + 1] != c)
			nb++;
		i++;
	}
	return (nb);
}

static int	t_mot(unsigned int index_d, const char *str, char set)
{
	int	t_chaine;

	t_chaine = 0;
	while (str[index_d] != set && str[index_d])
	{
		t_chaine++;
		index_d++;
	}
	return (t_chaine);
}

static char	**insert(char **tab, const char *str, char c)
{
	int	i;
	int	p_chaine;
	int	n_array;

	n_array = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			p_chaine = 0;
			while (str[i] != c && str[i])
			{
				tab[n_array][p_chaine] = str[i];
				i++;
				p_chaine++;
			}
			i--;
			tab[n_array][p_chaine] = '\0';
			n_array++;
		}
		i++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		n_array;

	if (!s)
		return (0);
	n_array = 0;
	i = 0;
	tab = malloc(sizeof(char *) * (t_array(s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			tab[n_array] = malloc(sizeof(char) * t_mot(i, s, c) + 1);
			if (!tab[n_array])
				return (free_tab(tab), NULL);
			i = i + t_mot(i, s, c) - 1;
			n_array++;
		}
		i++;
	}
	tab[t_array(s, c)] = 0;
	return (insert(tab, s, c));
}
