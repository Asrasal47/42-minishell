/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arasal <arasal@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 13:05:15 by arasal            #+#    #+#             */
/*   Updated: 2023/04/18 19:00:43 by arasal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include "../Libft/libft.h"
# include "get_next_line_bonus.h"
# include <readline/readline.h>
# include <readline/history.h>

extern void	rl_replace_line(const char *s, int i);

typedef struct s_glob
{
	pid_t				pid;
	int					exit_status;
}	t_glob;

t_glob	g_glob;

typedef struct s_env
{
	char				**env_save;
	char				**env_var;
	char				**var_val;
}	t_env;

typedef struct s_b
{
	char				*cmd;
	char				**option;
	char				*param;
}	t_b;

typedef struct s_var_exp
{
	char				*s;
	char				*temp;
	char				*temp1;
	char				*temp2;
	char				*temp3;
	int					xo;
}	t_var_exp;

typedef struct s_minishell
{
	t_env				*e;
	int					count;
	int					pipes;
	int					file[2];
	int					redirect[2];
	int					temp_fd;
	int					temp_fd2;
	int					*subsh_lvl;
	char				*line;
	char				*cmd_line;
	char				*last_line;
	char				*red;
	char				**tokens;
	t_b					*cmds;
	struct sigaction	sa;
}	t_minishell;

void		ft_clear(t_minishell *m);
void		print_s(char **str);
void		*free_s(char **str);
void		*free_r(char *str);

char		*ft_strlower(char *str);
void		signal_ft(int sign);
void		signals_handler(int sign);
char		**save_env(char **env);
void		collect_exit_status(int child_pid, t_minishell *m);
int			struct_init(t_minishell *mshell, int argc, char **env);

char		*get_next_line(int fd);

void		var_exp_init(t_var_exp *t, int x);
void		free_var_temp(t_var_exp *t, int a);

int			ft_strcmp(const char *s1, const char *s2);
int			ft_arrlen(char **s);

int			token_maker(t_minishell *m, int x);
int			ft_stradd(char *temp, char ***tokenized);
char		*ft_variable_expansion(char *s, t_minishell *m, int x);
char		**ft_tokenize(char *line);
char		*ft_quotes(char *s);

int			verify_syntax(t_minishell *m);
char		*check_output_redir(char **s, t_minishell *m, int x);
char		*check_input_redir(char **s, t_minishell *m, int x);

void		exec_builtin(t_minishell *mshell);
int			parsing_builtin(t_minishell *mshell);
void		ft_quotes_fix(char **w, char *s, int *i);
int			is_pipe(t_minishell *m);
int			is_builtin(t_minishell *mshell);
int			parse_command(t_minishell *mshell);

int			save_export(t_minishell *m);
int			change_directory(t_minishell *m);
int			print_env(char **env_save);
int			print_pwd(void);
int			print_echo(t_minishell *m);
int			ft_unset(t_minishell *m);
void		ft_exit(t_minishell *m);
int			check_ex_var(t_minishell *m, int x);
int			ft_verify_identifier(t_minishell *m);
int			check_if_builtin(t_minishell *m, char *argv);

void		exit_error(char *cmd, char *error_msg, int exit_status);
int			no_exit_error(char *cmd, char *error_msg, int exit_status);
void		ft_error_infile(char	*file);
void		ft_error_outfile(char	*file);
void		ft_error_cmd(char **cmd);

char		*set_path(char **env, char *str, char ***cmd);
void		exec_simple(char *s, t_minishell *m);

void		cmd_fix(char **cmd, int x);

int			is_redirection(char *str, char c);

void		exec_heredoc(t_minishell *m);
void		here_doc_pipe(char *argv, t_minishell *m);

void		ft_exec(char *argv, char **env, t_minishell *m);
void		broken_scmd(char *path, char **cmd, t_minishell *m);
void		ft_pipe(char *argv, t_minishell *m);
void		open_file(int i, int file[2], char **argv, int argc);
void		parsing_pipe(t_minishell *m);

#endif
