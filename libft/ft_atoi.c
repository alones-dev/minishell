/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:40:10 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/02 13:21:00 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	unsigned int	i;
	int				signe;
	int				valeur;

	valeur = 0;
	i = 0;
	signe = 1;
	while (nptr[i] && (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
			|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v'))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe = -1;
		i++;
	}
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		valeur = valeur * 10 + (nptr[i] - '0');
		i++;
	}
	return (signe * valeur);
}
