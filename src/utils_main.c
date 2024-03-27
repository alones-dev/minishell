/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 11:51:31 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 18:24:22 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env **env, t_minishell *ms, char **envp)
{
	size_t	i;

	i = -1;
	while (envp[++i])
	{
		if (env_add_back(env, env_new(envp[i])) == EXIT_FAILURE)
		{
			env_clear(env);
			malloc_error(ms);
			exit(1);
		}
	}
	ms->env = *env;
	ms->code = 0;
	ms->temp_char = '\0';
	ms->temp_str = NULL;
	ms->temp_int = 0;
	ms->all_cmd = NULL;
	ms->all_pipe = NULL;
	ms->int_tab = NULL;
}

void	skip_space(char *prompt, int *i)
{
	while (prompt[*i] && (prompt[*i] == ' ' || prompt[*i] == '\t'
			|| prompt[*i] == '\n'))
		(*i)++;
}

void	check_pipe(char *prompt, int *i, int *nb_pipe, t_minishell *ms)
{
	if (prompt[*i] == '|')
		(*nb_pipe)++;
	ms->temp_int++;
}

int	check_all_val(t_instruct **instructions, int nb_pipe)
{
	t_instruct	*temp;
	t_instruct	*first;

	first = (*instructions);
	while (*instructions)
	{
		temp = (*instructions);
		handle_operator(instructions, &nb_pipe);
		handle_echo(instructions, &nb_pipe);
		(*instructions) = (*instructions)->next;
	}
	if (nb_pipe == -1)
		printf("Parse error !\n");
	return (nb_pipe);
}

void	verif_set(t_minishell *ms, t_instruct **list, t_env *env, int set)
{
	if (set == 0)
	{
		if (!ms)
			exit(2);
		set_ignore(ms);
	}
	else if (set == 1)
	{
		if (g_global == SIGQUIT)
			ms->code = 131;
		else if (g_global == SIGINT)
			ms->code = 130;
		if (!list)
		{
			env_clear(&env);
			free(ms);
			exit(2);
		}
		ms->all_cmd = list;
		set_signal_action(ms);
		*list = NULL;
	}
}
