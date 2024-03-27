/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:56:28 by cornguye          #+#    #+#             */
/*   Updated: 2023/11/08 18:21:44 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_taille_chaine(int n)
{
	int	i;

	if (n == -2147483648)
		return (11);
	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*cas_special(char *nbr)
{
	int		i;
	char	*chaine;

	chaine = malloc(sizeof(char) * 12);
	if (!chaine)
		return (NULL);
	i = 0;
	while (nbr[i])
	{
		chaine[i] = nbr[i];
		i++;
	}
	chaine[i] = '\0';
	return (chaine);
}

char	*ft_itoa(int n)
{
	char	*new_chaine;
	int		t_chaine;

	t_chaine = ft_taille_chaine(n);
	if (n == -2147483648)
		return (cas_special("-2147483648"));
	new_chaine = malloc(sizeof(char) * t_chaine + 1);
	if (!new_chaine)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		new_chaine[0] = '-';
	}
	if (n == 0)
		new_chaine[0] = n + '0';
	new_chaine[t_chaine] = '\0';
	while (n > 0)
	{
		new_chaine[t_chaine - 1] = (n % 10) + '0';
		n = n / 10;
		t_chaine--;
	}
	return (new_chaine);
}
