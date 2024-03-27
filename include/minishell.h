/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdaumont <kdaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:35:17 by cornguye          #+#    #+#             */
/*   Updated: 2024/03/25 09:35:48 by kdaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "get_next_line.h"
# include "libft.h"
# include <bits/sigaction.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

extern int				g_global;

// type operator/word/separator
typedef struct s_instruct
{
	char				*instruct;
	char				*type;
	int					index;
	char				*role;
	struct s_instruct	*next;
	struct s_instruct	*prev;
}						t_instruct;

typedef struct s_pipe
{
	int					pipe[2];
	int					index;
	t_instruct			*all_cmd;
	struct s_pipe		*next;
	struct s_pipe		*prev;
}						t_pipe;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*before;
	struct s_env		*next;
}						t_env;

typedef struct s_minishell
{
	char				*temp_str;
	char				temp_char;
	int					temp_int;
	int					*int_tab;
	t_instruct			**all_cmd;
	t_pipe				**all_pipe;
	int					code;
	t_env				*env;
	struct sigaction	signal;
	struct sigaction	ignore;
}						t_minishell;

// main
void					handle_echo(t_instruct **instructions, int *nb_pipe);
void					handle_operator(t_instruct **instructions,
							int *nb_pipe);

// utils_main
void					init_env(t_env **env, t_minishell *ms, char **envp);
void					skip_space(char *prompt, int *i);
void					check_pipe(char *prompt, int *i, int *nb_pipe,
							t_minishell *ms);
int						check_all_val(t_instruct **instructions, int nb_pipe);
void					verif_set(t_minishell *ms, t_instruct **list,
							t_env *env, int set);

// utils.c
void					free_tab(char **tab);
int						size_instruct(char **str);
char					*ft_strjoin_letter(const char *s1, char const s2);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_join(char *s1, char s2);
char					*ft_strjoin_free(char *s1, char *s2);

// utils_2.c
int						exit_code(t_minishell *ms);
void					set_all_signal_null(t_minishell *ms);
void					while_echo(t_minishell *ms, size_t *i, char **cmd,
							size_t len);

// utils_struct.c
t_instruct				*ft_lstlast_instruct(t_instruct *lst);
t_instruct				*ft_lstnew_instruct(char *txt, char *type, int nb_pipe);
void					ft_lstadd_back_instruct(t_instruct **lst,
							t_instruct *new);
void					print_list(t_instruct **lst);
void					free_element_struct(t_instruct **list);
void					free_element_struct_end(t_instruct **list);

// create_struct_pipe.c
t_pipe					*ft_lstlast_pipe(t_pipe *lst);
t_pipe					*ft_lstnew_pipe(int index);
void					ft_lstadd_back_pipe(t_pipe **lst, t_pipe *new);
void					free_pipe_struct(t_pipe **lst);
int						set_pipe(int nb_pipe, t_pipe **fd_pipe);

// pipex_one_cmd.c
void					pipex_one(t_minishell *ms, t_instruct *instruct,
							int nb_operator);
void					exec_cmd(t_instruct *instruct, t_minishell *ms,
							int nb_operator);

// pipex_utils_1.c
void					exec_cmd_n(t_instruct *instruct, t_pipe **pipe,
							int index, t_minishell *ms);
void					close_pipe(t_pipe *pipe);
int						wait_childs(int pid);
void					pipex_n(t_minishell *ms, t_instruct *instruc,
							int nb_pipe);

// pipex_utils_2.c
int						is_builtins(t_instruct *instruct);
void					pipex_one(t_minishell *ms, t_instruct *instruct,
							int nb_operator);
void					process_role_n(t_instruct **instruct, int *fd,
							int *compteur_operator);
void					process_word_n(t_instruct *instruct, char **the_cmd,
							int *i, int index);

// pipex_n_cmd.c
void					execution_n(t_minishell *ms, char *the_cmd, char **cmd,
							t_pipe **pipe);
void					create_cmd_n(char **cmd, t_instruct *instruct,
							int index);
int						nb_ope(t_instruct *lst, int index);
void					close_connection(t_pipe *pipe, int index);
void					redirect_connection(t_pipe *pipe, int index);

// utils_errors.c
int						malloc_error(t_minishell *ms);
void					free_el(char **str, t_env **env, t_instruct **lst,
							t_pipe **pi);
void					free_all(t_minishell *ms, char **cmd);

// env_list.c
t_env					*env_new(char *content);
t_env					*env_last(t_env *list);
t_env					*env_get(t_env *list, char *key);
int						env_add_back(t_env **list, t_env *node);
void					env_clear(t_env **list);

// env_path.c
char					*env_get_value(t_minishell *ms, char *key);
char					**env_collapse(t_env *list);
size_t					env_size(t_env *list);
char					*find_the_one_path(t_minishell *ms, char *commande);

// builtins
void					ft_cd(t_minishell *ms, char **cmd);
void					ft_echo(t_minishell *ms, char **cmd, t_instruct *s_cmd);
void					ft_env(t_minishell *ms, char **env);
void					ft_exit(t_minishell *ms, char **cmd, t_instruct *s_cmd);
void					ft_export(t_minishell *ms, char **cmd);
char					*ft_pwd(t_minishell *ms, char **cmd);
void					ft_unset(t_minishell *ms, char **cmd);

// here_doc.c
void					here_doc(char *stop);
int						check_here_doc(t_instruct *command);
void					set_signal_here_doc(t_instruct *list, t_minishell *ms);

// process_role
void					process_read_file(t_instruct *cmd, int *fd, int num);
void					process_here_doc(t_instruct *cmd, int *fd);
void					process_write_file(t_instruct *cmd, int *fd, int num);
void					process_add_write_file(t_instruct *cmd, int *fd,
							int num);

// signal_handler
void					set_signal_action(t_minishell *ms);
void					set_ignore(t_minishell *ms);

// utils_add
char					*handle_va_env(char *prompt, char **str,
							t_minishell *ms);
char					*creat_word_cmp(t_minishell *ms, char *prompt);
int						verif_boucle_error(char *prompt, int i);
char					*handle_error_write(char *new_chaine, t_minishell *ms);
int						calc_len_va_env(char *prompt);

// utils_add_2
int						check_space(char *str);
int						check_dolar(char *str);
int						handle_builtins(char *name, char **cmd, t_minishell *ms,
							t_instruct *s_cmd);

// add_operator
int						add_operator(t_instruct **list, char *prompt,
							int nb_pipe, t_minishell *ms);

// add_word
int						add_word(t_instruct **instructions, char *prompt,
							int nb_pipe, t_minishell *ms);

// add_sep
int						add_separator(t_instruct **instructions, char *prompt,
							int nb_pipe, t_minishell *ms);

// add_error
int						add_env_error(t_instruct **instructions, char *prompt,
							int nb_pipe, t_minishell *ms);
void					add_va_env(t_instruct **list, char *str, int nb_pipe);

#endif
