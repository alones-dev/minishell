/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_one_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:05:51 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 18:31:09 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_minishell *ms, char *the_cmd, char **cmd, t_instruct *s_cmd)
{
	char	**env;

	if (!the_cmd)
	{
		(env_clear(&ms->env), free_element_struct(&s_cmd), free_tab(cmd));
		exit(0);
	}
	if (!handle_builtins(the_cmd, cmd, ms, s_cmd))
	{
		if (!find_the_one_path(ms, the_cmd))
		{
			env_clear(&ms->env);
			free_tab(cmd);
			ft_putstr_fd(the_cmd, 2);
			ft_putstr_fd(": Command not found\n", 2);
			free_element_struct(&s_cmd);
			exit(127);
		}
		env = env_collapse(ms->env);
		if (execve(find_the_one_path(ms, the_cmd), cmd, env) == -1)
		{
			(perror(the_cmd), free_tab(cmd), free(the_cmd), free_tab(env));
			exit(127);
		}
	}
}

void	create_cmd(char **cmd, t_instruct *instruct)
{
	int	i;

	i = 0;
	while (instruct)
	{
		if (instruct->index > -1 && instruct->role == NULL
			&& ft_strncmp(instruct->type, "OPERATOR") != 0)
		{
			cmd[i] = ft_strdup(instruct->instruct);
			i++;
		}
		instruct->index = -1;
		instruct = instruct->next;
	}
	cmd[i] = NULL;
}

void	process_role(t_instruct **instruct, int *fd, int *compteur_operator)
{
	if (ft_strncmp((*instruct)->role, "FILE_READ") == 0)
		process_read_file(*instruct, fd, *compteur_operator);
	else if (ft_strncmp((*instruct)->role, "STOP_HEREDOC") == 0)
		process_here_doc(*instruct, &fd[*compteur_operator]);
	else if (ft_strncmp((*instruct)->role, "FILE_DEL_WRITE") == 0)
		process_write_file(*instruct, fd, *compteur_operator);
	else if (ft_strncmp((*instruct)->role, "FILE_ADD_WRITE") == 0)
		process_add_write_file(*instruct, fd, *compteur_operator);
	(*compteur_operator)++;
}

void	process_word(t_instruct *instruct, t_minishell *ms, int *i)
{
	if (ft_strncmp(instruct->type, "WORD") == 0 || ft_strncmp(instruct->type,
			"OPTION") == 0 || ft_strncmp(instruct->type, "ERREUR") == 0
		|| ft_strncmp(instruct->type, "VA_ENV") == 0)
	{
		if (instruct->index > -1)
		{
			if (!(ms->temp_str))
				ms->temp_str = instruct->instruct;
			(*i)++;
		}
	}
}

void	exec_cmd(t_instruct *instruct, t_minishell *ms, int NB_OPERATOR)
{
	t_instruct	*first;
	char		**cmd;
	int			i;
	int			compteur_operator;
	int			fd[NB_OPERATOR];

	ms->temp_str = NULL;
	first = instruct;
	i = 0;
	compteur_operator = 0;
	while (instruct)
	{
		if (instruct->role)
			process_role(&instruct, fd, &compteur_operator);
		else
			process_word(instruct, ms, &i);
		instruct = instruct->next;
	}
	cmd = ft_calloc(sizeof(char *), i + 1);
	if (!cmd)
		return ;
	instruct = first;
	create_cmd(cmd, instruct);
	execution(ms, ms->temp_str, cmd, instruct);
}
