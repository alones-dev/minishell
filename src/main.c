/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cornguye <cornguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:17:18 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/24 19:10:25 by cornguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_global;

void	handle_operator(t_instruct **instructions, int *nb_pipe)
{
	if (strcmp((*instructions)->type, "OPERATOR") == 0 && (*instructions)->next)
	{
		if (strcmp((*instructions)->instruct, ">") == 0)
			(*instructions)->next->role = "FILE_DEL_WRITE";
		else if (strcmp((*instructions)->instruct, "<") == 0)
			(*instructions)->next->role = "FILE_READ";
		else if (strcmp((*instructions)->instruct, "|") == 0)
		{
			if (!(*instructions)->prev)
				*nb_pipe = -1;
			else if ((*instructions)->next->instruct
				&& strcmp((*instructions)->next->instruct, "|") == 0)
				*nb_pipe = -1;
		}
		else if (strcmp((*instructions)->instruct, "<<") == 0)
			(*instructions)->next->role = "STOP_HEREDOC";
		else if (strcmp((*instructions)->instruct, ">>") == 0)
			(*instructions)->next->role = "FILE_ADD_WRITE";
	}
	else if (strcmp((*instructions)->type, "OPERATOR") == 0
		&& !(*instructions)->next)
		*nb_pipe = -1;
}

void	handle_echo(t_instruct **instructions, int *nb_pipe)
{
	if (strcmp((*instructions)->instruct, "echo") == 0 && (*instructions)->next)
	{
		if (strcmp((*instructions)->next->instruct, "|") == 0)
		{
			(*instructions)->index = -1;
			(*instructions)->next->index = -1;
			(*nb_pipe)--;
		}
		else if (strcmp((*instructions)->next->instruct, ">") == 0)
			(*instructions)->index = -1;
	}
}

int	start_exec(t_instruct **instr, t_minishell *ms, int nb_pipe, int i)
{
	t_instruct	*first_node;

	first_node = (*instr);
	nb_pipe = check_all_val(instr, nb_pipe);
	if (nb_pipe == -1)
	{
		ms->code = 2;
		return (0);
	}
	(*instr) = first_node;
	if (first_node && i != 0)
	{
		if (nb_pipe == 0)
			pipex_one(ms, (*instr), ms->temp_int);
		else
			pipex_n(ms, (*instr), nb_pipe);
	}
	unlink("objs/FiChIeR_CaChE");
	return (0);
}

void	parsing(char *prompt, t_minishell *ms, t_instruct **instructions)
{
	int			i;
	int			nb_pipe;

	ms->all_pipe = NULL;
	ms->temp_int = 0;
	i = 0;
	nb_pipe = 0;
	skip_space(prompt, &i);
	while (prompt[i])
	{
		if (prompt[i] == '|' || prompt[i] == '<' || prompt[i] == '>')
		{
			check_pipe(prompt, &i, &nb_pipe, ms);
			i += add_operator(instructions, &prompt[i], nb_pipe, ms);
		}
		else if (prompt[i] == '\'' || prompt[i] == '\"')
			i += add_separator(instructions, &prompt[i], nb_pipe, ms);
		else if (prompt[i] == '$')
			i += add_env_error(instructions, &prompt[i], nb_pipe, ms);
		else if (prompt[i] != ' ' && prompt[i] != '\t' && prompt[i] != '\n')
			i += add_word(instructions, &prompt[i], nb_pipe, ms);
		else
			i++;
	}
	start_exec(instructions, ms, nb_pipe, i);
}

int	main(int ac, char **av, char **envp)
{
	char		*prompt;
	int			error;
	t_instruct	**instructions;
	t_env		*env;
	t_minishell	*ms;

	((void)ac, (void)av, env = NULL, instructions = NULL);
	ms = malloc(sizeof(t_minishell));
	(verif_set(ms, instructions, env, 0), init_env(&env, ms, envp));
	while (1)
	{
		instructions = malloc(sizeof(t_instruct));
		verif_set(ms, instructions, env, 1);
		prompt = readline("Minishell$ ");
		if (prompt == NULL)
		{
			error = exit_code(ms);
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		(add_history(prompt), parsing(prompt, ms, instructions));
		(free_element_struct_end(instructions), free(prompt));
	}
	(env_clear(&env), free(ms), free_element_struct_end(instructions));
	return (error);
}
