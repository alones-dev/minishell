/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sep.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:39:07 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 19:04:58 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_struc_separator(char *stock_entry, t_instruct **list, int nb_pipe)
{
	t_instruct	*temp;

	if (stock_entry)
	{
		if (stock_entry[0] == '-')
			temp = ft_lstnew_instruct(stock_entry, "OPTION", nb_pipe);
		else if (stock_entry[0] == '$' && stock_entry[1] == '?')
			temp = ft_lstnew_instruct(stock_entry, "ERREUR", nb_pipe);
		else if (stock_entry[0] == '$')
			temp = ft_lstnew_instruct(stock_entry, "VA_ENV", nb_pipe);
		else
			temp = ft_lstnew_instruct(stock_entry, "WORD", nb_pipe);
		ft_lstadd_back_instruct(list, temp);
	}
}

void	add_str_sep(char **value, char *prompt, t_minishell *ms, int nb_sep)
{
	if (prompt[ms->temp_int] == '$' && prompt[ms->temp_int + 1] == '$'
		&& (ms->temp_char == '\"' || nb_sep == 2))
	{
		*value = ft_strjoin_free(*value,
				env_get_value(ms, "SYSTEMD_EXEC_PID"));
		ms->temp_int++;
	}
	else if (prompt[ms->temp_int] == '$' && prompt[ms->temp_int + 1]
		//&& prompt[ms->temp_int + 1] != '?'
		&& (ms->temp_char == '\"' || nb_sep == 2)
		&& prompt[ms->temp_int + 1] != '\'' && prompt[ms->temp_int + 1] != '\"')
	{
		*value = handle_va_env(&prompt[ms->temp_int], value, ms);
		ms->temp_int += calc_len_va_env(&prompt[ms->temp_int]);
	}
	else
		*value = ft_join(*value, prompt[ms->temp_int]);
}

int	verif_exit_sep(int nb_sep, t_minishell *ms, char *prompt)
{
	if (nb_sep == 2 && ((ms->temp_char == '\"' && prompt[ms->temp_int] == '\'')
			|| (ms->temp_char == '\'' && prompt[ms->temp_int] == '\"')))
	{
		ms->temp_char = prompt[ms->temp_int];
		nb_sep = 0;
	}
	if (prompt[ms->temp_int] == ms->temp_char && nb_sep == 2)
		nb_sep = 0;
	return (nb_sep);
}

int	verif_break_sep(int nb_sep, t_minishell *ms, char *prompt)
{
	if (nb_sep == 2 && (prompt[ms->temp_int] == ' '
			|| prompt[ms->temp_int] == '\n'
			|| prompt[ms->temp_int] == '\t'
			|| prompt[ms->temp_int] == '|'
			|| prompt[ms->temp_int] == '<'
			|| prompt[ms->temp_int] == '>'))
		return (0);
	return (1);
}

int	add_separator(t_instruct **list, char *prompt, int nb_pipe, t_minishell *ms)
{
	int		nb_sep;
	char	*stock_entry;

	ms->temp_char = prompt[0];
	ms->temp_int = 0;
	stock_entry = ft_calloc(sizeof(char), 1);
	if (!stock_entry)
		return (malloc_error(ms), -1);
	nb_sep = 0;
	while (prompt[ms->temp_int])
	{
		if (prompt[ms->temp_int] == ms->temp_char)
			nb_sep++;
		else
			add_str_sep(&stock_entry, prompt, ms, nb_sep);
		ms->temp_int++;
		if (nb_sep == 2 && prompt[ms->temp_int] == '$')
			continue ;
		if (verif_break_sep(nb_sep, ms, prompt) == 0)
			break ;
		nb_sep = verif_exit_sep(nb_sep, ms, prompt);
	}
	add_struc_separator(stock_entry, list, nb_pipe);
	return (ms->temp_int);
}
