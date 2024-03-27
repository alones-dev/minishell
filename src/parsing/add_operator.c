/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:43:15 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/22 11:43:43 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_operator(t_instruct **list, char *prompt, int nb_pipe, t_minishell *ms)
{
	t_instruct	*temp;
	int			i;
	char		*stock_entry;

	stock_entry = ft_calloc(sizeof(char), 1);
	if (!stock_entry)
		return (malloc_error(ms), -1);
	i = 0;
	while (prompt[i] && (prompt[i] == '|'
			|| prompt[i] == '<' || prompt[i] == '>'))
	{
		stock_entry = ft_join(stock_entry, prompt[i]);
		i++;
		if (prompt[i] && prompt[i - 1] != prompt[i])
			break ;
	}
	temp = ft_lstnew_instruct(stock_entry, "OPERATOR", nb_pipe);
	ft_lstadd_back_instruct(list, temp);
	return (i);
}
