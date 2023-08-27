/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@studend.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 20:58:09 by mlormois          #+#    #+#             */
/*   Updated: 2021/09/16 15:51:40 by mlormois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "ft_getenv.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

# define PATH_HEREDOC "/tmp/.broshell_heredoc"
# define DISPLAY_PROMPT "➜  Broshell >>> "
# define SPLIT_CHAR -32
# define ERROR_STATUS 2

# define INPUT 0
# define OUTPUT 1

# define START 0
# define INDEX 1
# define I 2

enum	e_type
{
	CMD,
	WRD,
	FD,
	LIM,
	RIN,
	DRIN,
	ROUT,
	DROUT,
	DAND,
	DOR,
	PIPE,
	SPAR,
	EPAR
};

enum	e_state
{
	NORMAL,
	SIMPLE_Q,
	DOUBLE_Q
};

/* ************************************************************************** */
/*								   STRUCT									  */
/* ************************************************************************** */

extern int				g_exit_status;
typedef struct s_op		t_op;
typedef struct s_bultin	t_bultin;
typedef struct s_token	t_token;
typedef struct s_ast	t_ast;
typedef struct s_cmd	t_cmd;
typedef struct s_lst	t_lst;

struct		s_op
{
	char	*str;
	int		ret;
};

struct		s_bultin
{
	char	*str;
	void	(*ft)(t_cmd *);
};

struct		s_token
{
	char	*str;
	int		type;
	t_token	*prev;
	t_token	*next;
};

struct		s_cmd
{
	int		ispipe;
	int		input;
	int		output;
	t_token	*red;
	t_token	*args;
};

struct		s_ast
{
	int		type;
	t_cmd	*cmd;
	t_ast	*left;
	t_ast	*right;
};

/* ************************************************************************** */
/*						       LST UTILS									  */
/* ************************************************************************** */

t_token		*ft_token_first(t_token *lst);
t_token		*ft_token_create(char *str, int type);
void		ft_token_pushback(t_token **lst, t_token *new_elem);
t_token		*ft_token_last(t_token *lst);
void		ft_token_delone(t_token **lst);
void		ft_token_destroy(t_token *lst);

char		**ft_lst_to_tab(t_lst *data);
char		**ft_token_to_tab(t_token *data);
void		ft_insert_lst(t_token **new_lst, t_token **lst);
void		ft_lst_split(t_token **lst, int type, char *line);

int			ft_check_parenthese(t_token *lst);
t_token		*ft_skip_parenthese(t_token **lst);

int			ft_cmd_create(t_cmd **data, t_token **lst);
void		ft_cmd_destroy(t_cmd *data);

int			ft_ast_setpipe(t_ast **data);
int			ft_ast_build(t_ast **data, t_token *lst);
t_ast		*ft_ast_create(int type, t_cmd *elem_cli);
void		ft_ast_destroy(t_ast *data);

/* ************************************************************************** */
/*								DEBUG	  									  */
/* ************************************************************************** */

void		ft_ast_display(t_ast *data);
void		ft_cmd_display(t_cmd *data);
void		ft_token_display(t_token *lst);
void		ft_strs_display(char **tab_word);

/* ************************************************************************** */
/*								 ERROR										  */
/* ************************************************************************** */

int			checker_syntax(int curr, int old, int index);
int			token_start_error_syntax(int curr_token);
int			token_middle_error_syntax(int curr_token, int old);

int			error_permission_denied(char *file_name);
int			ft_check_relative_binary(char **cmd, char *arg);
void		error_cmd_not_found(char *cmd);
int			token_epar_error_syntax(int curr, int old);
int			token_last_error_syntax(int curr_token, int state);
int			spliter_error_syntax(int state);
int			error_syntax(char *message);
int			error_unexpected_token(char *token);

void		*ft_return_clear(t_token *data);

/* ************************************************************************** */
/*								 UTILES										  */
/* ************************************************************************** */

int			do_split_quotes(char **str);
int			ft_expension_apply(t_token **new_lst, t_token **ptr_tmp);
char		*ft_add_variable(char *line, int opt);
char		*do_wildcard(char *path, char **cond, int opt);

void		ft_builtin_forked(t_cmd *data, void (*ft)(t_cmd *),
				t_ast *origin, int *n_child);
int			ft_cmd_isbuiltin(char *cmd, t_cmd *data,
				t_ast *origin, int *n_child);
int			ft_opendir(DIR **pdir, char *path);
int			ft_ismetachar(char *line, int start);

int			isfile(const char *name);
char		*ft_isvalide_cmd(char *binary);
int			ft_expension_fd(char **str, int opt);
int			ft_check_file(char *filename);
void		ft_overwrite_redirection(int input, int output);
int			ft_open_fd(char *file, int flag, int mode);
int			ft_create_fd(char *file, int mode);

void		ft_swap_env_pwd(char *arg);
int			ft_here_doc(t_cmd **data, char *limiter);
int			ft_red_loader(t_cmd **data, t_token *redirection);
int			ft_args_loader(t_token **args);

/* ************************************************************************** */
/*								BUILTIN										  */
/* ************************************************************************** */

void		ft_echo(t_cmd *data);
void		ft_cd(t_cmd *data);
void		ft_pwd(t_cmd *data);
void		ft_export(t_cmd *data);
void		ft_unset(t_cmd *data);
void		ft_env(t_cmd *data);
void		ft_exit(t_cmd *data);

/* ************************************************************************** */
/*								SIGNAL										  */
/* ************************************************************************** */

void		signal_handling_default(void);
void		signal_handling_reset(void);
void		signal_handling_register(void);

/* ************************************************************************** */
/*							MAIN FUNCTION									  */
/* ************************************************************************** */

char		*expension_wildcard(char *line);
void		shell_spliter(char *line);
void		shell_tokenizer(char **tab_word, int size_tab);
void		shell_expension(t_token *lst);
void		shell_ast(t_token *lst);
void		shell_exec(t_ast *data);

char		*ft_remove_quotes(char *line);
char		*ft_double_quotes_expension(char *line);
char		*ft_normal_expension(char *line);
char		*do_expension(char *line);

#endif
