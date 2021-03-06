/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:36 by alienard          #+#    #+#             */
/*   Updated: 2020/10/28 15:28:09 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include "libft.h"
# include "libftprintf.h"
# include "libftdprintf.h"
# include "libftfprintf.h"
# include "list.h"

# ifndef SPACE
#  define SPACE " \t\r\n\v\f"
# endif

# ifndef TOKENS
#  define TOKENS "-\"\'|;><\\$"
# endif

# ifndef META
#  define META "-\"\'\\$./><"
# endif

# ifndef QUOTE
#  define QUOTE "\"\'"
# endif

# ifndef REDIR
#  define REDIR "><"
# endif

# ifndef END_CMD
#  define END_CMD "><|;"
# endif

# ifndef CTRL_OP
#  define CTRL_OP "|| & && ; ;; ( ) | \n"
# endif

# ifndef META_CHAR
#  define META_CHAR "|&;()<> 	"
# endif

# ifndef PROMPT
#  define PROMPT "minishell$ "
# endif

# ifndef QPROMPT
#  define QPROMPT "> "
# endif

# ifndef ON
#  define ON 1
# endif

# ifndef OFF
#  define OFF 0
# endif

# ifdef BUFFER_SIZE
#  if BUFFER_SIZE < 0
#   undef BUFFER_SIZE
#   define BUFFER_SIZE 0
#  endif
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 200
# endif

typedef struct	s_quote
{
	int	nbquote;
	int	quote;
	int	i;
	int	j;
}				t_quote;

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

typedef struct	s_parse
{
	t_dlist			*current;
	t_list			*input;
	int				quote;
	int				comment;
	int				bkslh;
	int				error;
	char			*prompt;
}				t_parse;

typedef struct	s_cmd
{
	t_list			**env;
	int				ac;
	t_list			*argv;
	char			**av;
	char			*cmd;
	int				pos;
	int				after;
	int				before;

	int				quote;
	int				nbquote;

	int				pipedfd[2];
	bool			opt;
	int				bkslh;

	char			*file_redir;
	int				redir;
	int				nb_redir;
	t_list			**fd_in;
	t_list			**fd_out;
	int				fdout;
	int				fdin;
	int				ret_dup;
	struct s_cmd	*pipe_prev;
	struct s_cmd	*pipe_next;
}				t_cmd;

typedef struct	s_sh
{
	int		fd;
	char	*file;
	int		nbline;
	char	*line;
	int		ret_cmd;
	char	*ret_str;
	int		ret_sh;
	int		(**blt_fct)(t_cmd *, struct s_sh *);
	t_ref	*cmds;
	t_list	**env;
	t_list	*begin_input;
	bool	sig;
}				t_sh;

typedef struct	s_buff
{
	char			buffer[BUFFER_SIZE];
	char			*tmp;
}				t_buff;

typedef struct	s_gnl
{
	int				currfd;
	int				ret;
	char			buffer[BUFFER_SIZE];
	char			*tmp;
	char			*rest;
	struct s_gnl	*next;
}				t_gnl;

extern t_sh		g_sh;
extern t_gnl	g_gnl;

int				get_next_line_multi(int fd, char **line);
int				ft_check_ln(char **line, t_gnl *current, char *buffer);
int				ft_ifnl(char **line, t_gnl *current, size_t i, char *tmp);
char			*ft_strdup_buff(char *buffer, int ret);
size_t			ft_strlen_gnl(const char *str);
char			*ft_strdup_free_gnl(char *s1);
char			*ft_strjoin_free_gnl(char *s1, char *s2);
int				ft_error(char **line);

char			**ft_split_line(char **inputs);
char			**ft_split_quote(char *str, char c);
char			*ft_split_handle_quote(char *str, char c, int start, int *i);
char			*ft_split_quote_concat(char *result, char *str,
					int start, int i);
char			**ft_split_arg(char *str);

/*
**	fcts using gnl in stdin / .sh in arg
*/

void			ft_prompt(t_sh *sh);
void			ft_infile(t_sh *sh);

int				ft_is_escaped(char *str, int pos);
int				ft_isinquotes(char *line, int pos);
int				ft_isindquotes(char *line, int pos);
int				ft_isinsquotes(char *line, int pos);
char			*ft_strdup_clean(const char *s1);
void			ft_clean_envvar(t_cmd *cmd);
char			*ft_is_in_env(char *str, t_sh *sh);

void			ft_check_line(char **line, int *quote, int *bkslh);
char			*ft_input_join(t_list *inputs);
int				ft_line_to_lst(char *inputs, t_sh *sh);
void			ft_init_cmd(t_sh *sh, char *line, int *i);
void			ft_init_args(t_sh *sh, char *line, int *i);

void			ft_handle_end(t_sh *sh, char *line, int *i);
void			ft_parse_escape(int *j, char *line, t_cmd *cmd);
void			ft_parse_pipe(t_sh *sh, char *line, int *i);
int				ft_check_args(char *inputs, t_sh *sh);
int				ft_strisspace(char *str);
char			*ft_strtrim_space(char *str);
int				ft_iterate_in_line(char *line, int *j, char *set);
int				ft_iterate_in_line_redir(char *line, int *j, char *set);
int				ft_iterate_in_line_space(char *line, int *i);
int				ft_iterate_in_line_space_esc(char *line, int *j);

/*
**	parse redir
*/

int				ft_parse_redir(t_sh *sh, char *line, int *i);
int				ft_parse_redir_in(t_sh *sh, char *line, int *i);
int				ft_parse_redir_out(t_sh *sh, char *line, int *i);
int				ft_parse_append(t_sh *sh, char *line, int *i);
int				ft_parse_redir_nb(t_sh *sh, char *line, int *i);

/*
**	exec redir
*/

void			ft_exec_redir(t_sh *sh, t_cmd *cmd);
int				ft_exec_redir_out(t_sh *sh, t_cmd *cmd);
int				ft_exec_append(t_sh *sh, t_cmd *cmd);
int				ft_exec_redir_in(t_sh *sh, t_cmd *cmd);

int				ft_parse_cmds(t_cmd *cmd, t_sh *sh);
char			*ft_lststrjoin(t_list *lst, char *inter);
char			*ft_parse_path(char **path);
char			*ft_lststrjoin(t_list *lst, char *inter);
int				ft_isolate_exec(char *path, char **buff);

/*
**	Buitltin functions
*/

int				ft_blt_process(t_sh *sh, t_cmd *cmd,
					int (*fn)(t_cmd *cmd, t_sh *sh));
int				ft_echo(t_cmd *cmd, t_sh *sh);
int				ft_pwd(t_cmd *cmd, t_sh *sh);
int				ft_change_dir(t_cmd *cmd, t_sh *sh);
int				ft_env(t_cmd *cmd, t_sh *sh);
int				ft_export(t_cmd *cmd, t_sh *sh);
int				ft_unset(t_cmd *cmd, t_sh *sh);
int				ft_exit(t_cmd *cmd, t_sh *sh);

/*
**	execve functions
*/

int				ft_search_n_execute(char **args, char **env, t_sh *sh);
char			*ft_get_abspath_filename(char *exec, char **env, t_sh *sh);
char			*ft_findexec(char *path, char *exec);
char			*ft_get_onlypaths(char **env);
int				ft_process(t_cmd *cmd, t_sh *sh);
int				ft_process_child(t_cmd *cmd, t_sh *sh);

t_list			*ft_start_minishell(char **env);

t_list			*ft_split_to_lst_env(char **env);
void			ft_free_env_lst(void *env_lst);
void			ft_sort_env_lst(t_list *env_lst);
t_env			*ft_separate_key_value(char *env_str, bool *add);
char			**ft_lst_env_to_split(t_list *lst_env);
char			**ft_lst_env_to_split_launch(t_list *lst_env);
char			**ft_lst_env_to_split_export(t_list *lst_env);
t_list			*ft_search_env(t_list *env, char *arg);
char			*ft_parse_env_var(char *line, t_sh *sh);
t_env			*ft_new_env_var(char *key, char *value);
t_list			*ft_update_env(t_list *env, t_env *data, bool add);
char			*ft_getcwd(void);

/*
**	replacing $ by env var before exec
*/

void			ft_check_env_var(t_cmd *cmd, t_sh *sh);
char			*ft_is_in_env(char *str, t_sh *sh);
void			ft_replace_env_var(char *av, char *key, t_cmd *cmd, int	i);
char			*ft_strdup_env_var(int len, char *av, char *key);

/*
**	create & exec pipes
*/

int				ft_create_pipe(t_sh *sh);
int				ft_add_pipe(t_dlist *cur, t_dlist *next, t_sh *sh);
int				ft_init_pipe(t_sh *sh, t_cmd *cmd);
int				ft_exec_pipe_child(t_sh *sh, t_cmd *cmd);
int				ft_exec_pipe_parent(t_sh *sh, t_cmd *cmd);

/*
**	signal
*/

void			ft_signal(int is_on);
void			ft_minishell_sigoff(void);

/*
**	free functions
*/

void			ft_free_minishell(t_sh *sh, int ret);
void			ft_free_gnl(t_sh *sh);
void			ft_lstclear_env(t_list **env);
void			ft_lstclear_cmds(t_ref *cmds);
void			ft_free_cmd(t_dlist *node);
void			ft_free_sub_cmd(t_cmd *cmd);
int				ft_search_piped_exit_cmd(t_sh *sh);
int				ft_is_double_minus(char *str);

void			ft_reset_sh(t_sh *sh);
void			ft_reset_cmd(t_dlist *node);

/*
**	error msgs functions
*/

int				ft_strerror(t_cmd *cmd, t_sh *sh, char *str);
void			ft_exporterror(t_cmd *cmd, t_sh *sh, char *str, int i);
void			ft_redirerror(t_sh *sh, char *tmp, char *str);
void			ft_redir_indir_error(t_sh *sh, char *tmp, DIR **dir);

/*
**	debug functions
*/

void   			 ft_print_cmds(t_sh *sh);
void   			 ft_print_sh(t_sh *sh);
void   			 ft_print_all(t_sh *sh);

#endif
