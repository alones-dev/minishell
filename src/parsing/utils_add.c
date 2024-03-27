/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:39:26 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 18:12:01 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_len_va_env(char *prompt)
{
	int	i;

	i = 1;
	if (prompt[i] && prompt[i] == '?')
		return (i);
	while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\t'
		&& prompt[i] != '\n' && prompt[i] != '$' && prompt[i] != '\''
		&& prompt[i] != '\"')
		i++;
	i--;
	return (i);
}

char	*handle_error_write(char *new_chaine, t_minishell *ms)
{
	char	*temp_value;
	char	*temp;

	if (g_global == SIGINT)
		ms->code = 130;
	else if (g_global == SIGQUIT)
		ms->code = 131;
	if (!new_chaine)
		temp = ft_itoa(ms->code);
	else
	{
		temp_value = ft_itoa(ms->code);
		temp = ft_strjoin_free(new_chaine, temp_value);
		free(temp_value);
	}
	return (temp);
}

int	verif_boucle_error(char *prompt, int i)
{
	if (prompt[i] && prompt[i] != ' ' && prompt[i] != '\t'
		&& prompt[i] != '\n' && prompt[i] != '$'
		&& prompt[i] != '\'' && prompt[i] != '\"')
		return (1);
	return (0);
}

char	*creat_word_cmp(t_minishell *ms, char *prompt)
{
	char	*word_cmp;
	int		i;

	i = 1;
	word_cmp = ft_calloc(1, 1);
	if (!word_cmp)
		return (malloc_error(ms), NULL);
	while (verif_boucle_error(prompt, i))
	{
		word_cmp = ft_join(word_cmp, prompt[i]);
		i++;
	}
	return (word_cmp);
}

char	*handle_va_env(char *prompt, char **str, t_minishell *ms)
{
	int		i;
	char	*word_cmp;
	char	*temp;

	i = 1;
	if (prompt[i] && prompt[i] == '?')
		temp = handle_error_write(*str, ms);
	else
	{
		word_cmp = creat_word_cmp(ms, prompt);
		if (!env_get_value(ms, word_cmp))
			return (free(word_cmp), *str);
		else
		{
			if (!*str)
				temp = env_get_value(ms, word_cmp);
			else
				temp = ft_strjoin(*str, env_get_value(ms, word_cmp));
		}
		(free(word_cmp), free(*str));
		*str = NULL;
	}
	return (temp);
}
