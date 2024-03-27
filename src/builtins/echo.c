/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 09:28:17 by kdaumont          #+#    #+#             */
/*   Updated: 2024/03/25 09:34:52 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_arg_n(char *str)
{
	int	i;

	if (str[0] != '-')
		return (0);
	i = 0;
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

void	print_echo(char *str, int state)
{
	int	i;

	i = 0;
	if (state == 0)
	{
		while (str[i])
		{
			if (str[i] == 92)
			{
				i++;
				printf("%c", str[i]);
			}
			else
				printf("%c", str[i]);
			i++;
		}
	}
	else
	{
		while (str[i] && str[i] == 39)
			i++;
		while (str[i] && str[i] != 39)
			write(1, &str[i++], 1);
	}
}

void	print_env_var(t_minishell *ms, char *str, int state)
{
	int		i;
	int		j;
	char	*var;

	i = 0;
	j = ft_strlen(str) - 1;
	if (state == 0)
	{
		var = ft_substr(str, 1, ft_strlen(str) - 1);
		if (env_get_value(ms, var))
			printf("%s", env_get_value(ms, var));
	}
	else
	{
		while (str[i] && str[i] == 34)
			i++;
		while (str[j] && str[j] == 34)
			j--;
		var = ft_substr(str, i + 1, j - i);
		if (ft_strcmp(var, "?") == 0)
			printf("%d", ms->code);
		if (env_get_value(ms, var))
			printf("%s", env_get_value(ms, var));
	}
}

void	is_var_env(t_minishell *ms, char *str)
{
	if (ft_strcmp(str, "$?") == 0)
	{
		if (g_global == SIGINT)
		{
			ms->code = 130;
			return (g_global = 0, (void)printf("%d", 130));
		}
		else if (g_global == SIGSEGV)
			return (g_global = 0, (void)printf("%d", 0));
		else if (g_global == SIGQUIT)
		{
			ms->code = 131;
			return (g_global = 0, (void)printf("%d", 131));
		}
		else
			return (g_global = 0, (void)printf("%d", ms->code));
	}
	return (print_echo(str, 0));
}

void	ft_echo(t_minishell *ms, char **cmd, t_instruct *s_cmd)
{
	size_t	len;
	size_t	i;

	ms->temp_int = 0;
	len = ft_stralen(cmd);
	if (len > 1 && (!is_arg_n(cmd[1])))
		i = 1;
	else
		i = 2;
	if (len == 1)
		(printf("\n"), free_el(cmd, &ms->env, &s_cmd, ms->all_pipe), exit(0));
	if (len == 2 && is_arg_n(cmd[1]))
		(free_el(cmd, &ms->env, &s_cmd, ms->all_pipe), exit(0));
	while_echo(ms, &i, cmd, len);
	if (!is_arg_n(cmd[1]))
		printf("\n");
	ms->code = 0;
	free_el(cmd, &ms->env, &s_cmd, ms->all_pipe);
	free(ms->all_pipe);
	exit(EXIT_SUCCESS);
}
