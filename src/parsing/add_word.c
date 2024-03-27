/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:38:30 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/22 15:44:36 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_struct_word(char *str, int pipe, t_instruct **list, t_minishell *ms)
{
	t_instruct	*temp;

	if (str[0])
	{
		if (ms->temp_str)
			add_va_env(list, str, pipe);
		else
		{
			if (str[0] == '-')
				ms->temp_str = "OPTION";
			else
				ms->temp_str = "WORD";
			temp = ft_lstnew_instruct(str, ms->temp_str, pipe);
			ft_lstadd_back_instruct(list, temp);
		}
	}
}

int	verif_exit_word(int *nb_sep, char *prompt, int i, t_minishell *ms)
{
	if (*nb_sep == 2 && prompt[i])
	{
		ms->temp_char = '\0';
		*nb_sep = 0;
		return (1);
	}
	else if (prompt[i] == '>' || prompt[i] == '<' || prompt[i] == '|')
		return (0);
	else if (*nb_sep == 0
		&& (prompt[i] == ' ' || prompt[i] == '\t' || prompt[i] == '\n'))
		return (0);
	return (1);
}

int	add_str_word(char **value, char *prompt, t_minishell *ms, int i)
{
	if (prompt[i] == '$' && ms->temp_char != '\'')
	{
		*value = handle_va_env(&prompt[i], value, ms);
		i += calc_len_va_env(&prompt[i]);
		ms->temp_str = "va_env";
	}
	else
		*value = ft_join(*value, prompt[i]);
	return (i);
}

int	add_word(t_instruct **list, char *prompt, int nb_pipe, t_minishell *ms)
{
	int			nb_sep;
	int			i;
	char		*stock_entry;

	stock_entry = ft_calloc(sizeof(char), 1);
	if (!stock_entry)
		return (malloc_error(ms), -1);
	i = 0;
	nb_sep = 0;
	ms->temp_str = NULL;
	ms->temp_char = '\0';
	while (prompt[i])
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"') && !ms->temp_char)
			ms->temp_char = prompt[i];
		if (prompt[i] != ms->temp_char)
			i = add_str_word(&stock_entry, prompt, ms, i);
		else if (prompt[i] == ms->temp_char)
			nb_sep++;
		i++;
		if (verif_exit_word(&nb_sep, prompt, i, ms) == 0)
			break ;
	}
	add_struct_word(stock_entry, nb_pipe, list, ms);
	return (i);
}
