/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:15:52 by aattali           #+#    #+#             */
/*   Updated: 2024/03/23 14:51:37 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(t_minishell *ms, char **cmd)
{
	int		size;
	char	*buffer;

	size = 0;
	buffer = NULL;
	while (!buffer)
	{
		size += 100;
		buffer = malloc(sizeof(char) * size);
		if (!buffer)
			return (NULL);
		if (!getcwd(buffer, size))
		{
			if (errno == ERANGE)
				(free(buffer), buffer = NULL);
			else
				return (free(buffer), perror("pwd"), NULL);
		}
	}
	if (buffer)
		printf("%s\n", buffer);
	free(buffer);
	free_all(ms, cmd);
	ms->code = 0;
	return (buffer);
}
