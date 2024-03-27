/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 13:39:07 by kdaumont          #+#    #+#             */
/*   Updated: 2024/03/23 14:49:55 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	malloc_error(t_minishell *ms)
{
	ms->code = 2;
	return (ft_putstr_fd("minishell: malloc error.\n", STDERR_FILENO),
		EXIT_FAILURE);
}

void	print_list(t_instruct **lst)
{
	while ((*lst))
	{
		printf("%s\t%s\t%s\t%d\n", (*lst)->instruct, (*lst)->type, (*lst)->role,
			(*lst)->index);
		(*lst) = (*lst)->next;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	free_el(char **str, t_env **env, t_instruct **lst, t_pipe **pi)
{
	if (*str)
		free_tab(str);
	if (lst)
		free_element_struct(lst);
	if (env)
		env_clear(env);
	if (pi)
		free_pipe_struct(pi);
}

void	free_all(t_minishell *ms, char **cmd)
{
	free_tab(cmd);
	if (ms->all_pipe != NULL)
	{
		free_pipe_struct(ms->all_pipe);
		free(ms->all_pipe);
		free_element_struct(ms->all_cmd);
		env_clear(&ms->env);
	}
}
