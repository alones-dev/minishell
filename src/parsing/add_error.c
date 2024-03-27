/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:38:46 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 19:02:26 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_va_env(t_instruct **list, char *str, int nb_pipe)
{
	t_instruct	*temp_struct;
	int			i;
	char		*temp_str;

	temp_str = ft_calloc(sizeof(char), 1);
	if (!temp_str)
		return ;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
			temp_str = ft_join(temp_str, str[i]);
		else
		{
			temp_struct = ft_lstnew_instruct(temp_str, "VA_ENV", nb_pipe);
			ft_lstadd_back_instruct(list, temp_struct);
			temp_str = NULL;
		}
		i++;
	}
	free(str);
	temp_struct = ft_lstnew_instruct(temp_str, "VA_ENV", nb_pipe);
	ft_lstadd_back_instruct(list, temp_struct);
}

void	add_struct_env(char *str, int pipe, t_instruct **list)
{
	t_instruct	*temp;

	if (str && str[0] != '\0')
	{
		if (!check_space(str))
		{
			temp = ft_lstnew_instruct(str, "VA_ENV", pipe);
			ft_lstadd_back_instruct(list, temp);
		}
		else
			add_va_env(list, str, pipe);
	}
}

int	add_str_env(char **stock_entry, char *prompt, t_minishell *ms, int i)
{
	if (prompt[i] == '$' && prompt[i + 1] == '$')
	{
		*stock_entry = ft_strjoin_free(*stock_entry,
				env_get_value(ms, "SYSTEMD_EXEC_PID"));
		i++;
	}
	else if (i == 0 && prompt[i] == '$' && prompt[i + 1] == '?'
		&& prompt[i + 2] == '\0')
	{
		free(*stock_entry);
		*stock_entry = ft_strdup("$?");
		i++;
	}
	else if (prompt[i] == '$' && prompt[i + 1] != ' '
		&& prompt[i + 1] != '\t' && prompt[i + 1] != '\n' && prompt[i + 1])
	{
		*stock_entry = handle_va_env(&prompt[i], stock_entry, ms);
		i += calc_len_va_env(&prompt[i]);
	}
	else
		*stock_entry = ft_join(*stock_entry, prompt[i]);
	return (i);
}

int	add_env_error(t_instruct **list, char *prompt, int nb_pipe, t_minishell *ms)
{
	int			nb_sep;
	int			i;
	char		*stock_entry;

	nb_sep = 0;
	i = 0;
	ms->temp_char = '\0';
	stock_entry = ft_calloc(sizeof(char), 1);
	if (!stock_entry)
		return (malloc_error(ms), -1);
	while (prompt[i] && prompt[i] != ' '
		&& prompt[i] != '\t' && prompt[i] != '\n')
	{
		if ((prompt[i] == '\'' || prompt[i] == '\"') && !ms->temp_char)
			ms->temp_char = prompt[i];
		if (prompt[i] == ms->temp_char)
			nb_sep++;
		if (prompt[i] != ms->temp_char)
			i = add_str_env(&stock_entry, prompt, ms, i);
		if (nb_sep != 0 && nb_sep % 2 == 0 && prompt[i + 1])
			ms->temp_char = '\0';
		i++;
	}
	add_struct_env(stock_entry, nb_pipe, list);
	return (i);
}
