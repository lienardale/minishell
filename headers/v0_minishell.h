/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v0_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 13:06:36 by alienard          #+#    #+#             */
/*   Updated: 2020/07/29 16:03:38 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef V0_MINISHELL_H
# define V0_MINISHELL_H

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include "libft.h"
#include "libftprintf.h"
#include "libftdprintf.h"
#include "libftfprintf.h"
#include "get_next_line_bonus.h"
#include "list.h"

# ifndef SPACE
#  define SPACE " \t\r\n\v\f"
# endif

# ifndef TOKENS
#  define TOKENS "-\"\'|;><\\"
# endif

# ifndef META
#  define META "-\"\'\\$"
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

# ifndef BUILTINS
#  define BUILTINS &ft_exit, &ft_echo, &ft_pwd, &ft_env, &ft_change_dir, &ft_export, &ft_unset
# endif


/*
typedef struct	s_env
{
	int	fd;
	int	check;
}				t_env;
*/

typedef struct	s_env
{
	char *key;
	char *value;
}				t_env;

typedef struct	s_cmd
{
	t_list			**env;
	int				ac;
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
	t_list			**fd_in;
	t_list			**fd_out;
	int				fdout;
	int				fdin;
	int				ret_dup;
	// either redir or right/left but not both, still not sure which is more suitable for our needs
	t_dlist			*redir_in;
	t_dlist			*redir_out;
	struct s_cmd	*left;
	struct s_cmd	*right;
}				t_cmd;

typedef struct	s_sh
{
	int		fd;
	char	*line;
	int		ret_cmd;
	int		ret_sh;
	int		(**blt_fct)(t_cmd *, struct s_sh *);
	t_ref	*cmds;
	t_list	**env;
}				t_sh;


char		**ft_split_line(char **inputs);
char		**ft_split_quote(char *str, char c);
char		**ft_split_arg(char *str);

/* fcts using gnl in stdin / .sh in arg */

void		ft_prompt(t_sh *sh);
void		ft_infile(t_sh *sh);


int			ft_isescaped(char *c); //should not use this one
int			ft_is_escaped(char *str, int pos); //but this one instead
int			ft_isinquotes(char *line, int pos);
int			ft_isindquotes(char *line, int pos);
int			ft_isinsquotes(char *line, int pos);
char		*ft_strdup_clean(const char *s1);

void		ft_check_line(char **line, int *quote, int *bkslh);
char		*ft_input_join(t_list *inputs);
void		ft_line_to_lst(char *inputs, t_sh *sh);
void		ft_init_cmd(t_sh *sh, char *line, int *i);
void		ft_init_args(t_sh *sh, char *line, int *i);

void		ft_handle_end(t_sh *sh, char *line, int *i);
void		ft_parse_escape(int *j, char *line, t_cmd *cmd);
void		ft_parse_pipe(t_sh *sh, char *line, int *i);

/* parse redir */

void		ft_parse_redir(t_sh *sh, char *line, int *i);
void		ft_parse_redir_in(t_sh *sh, char *line, int *i);
void		ft_parse_redir_out(t_sh *sh, char *line, int *i);
void		ft_parse_append(t_sh *sh, char *line, int *i);

/* exec redir */

void	ft_exec_redir(t_sh *sh, t_cmd *cmd);
int		ft_exec_redir_out(t_sh *sh, t_cmd *cmd);
int		ft_exec_append(t_sh *sh, t_cmd *cmd);
int		ft_exec_redir_in(t_sh *sh, t_cmd *cmd);


int			ft_parse_cmds(t_cmd *cmd, t_sh *sh);

char		*ft_lststrjoin(t_list *lst, char *inter);

char		*ft_parse_path(char *path);

char		*ft_lststrjoin(t_list *lst, char *inter);

int			ft_isolate_exec(char *path, char **buff);

/* Buitltin functions */

int			ft_echo(t_cmd *cmd, t_sh *sh);
int			ft_pwd(t_cmd *cmd, t_sh *sh);
int			ft_change_dir(t_cmd *cmd, t_sh *sh);
int			ft_env(t_cmd *cmd, t_sh *sh);
int			ft_export(t_cmd *cmd, t_sh *sh);
int			ft_unset(t_cmd *cmd, t_sh *sh);
int			ft_exit(t_cmd *cmd, t_sh *sh);


/* execve functions */

void		ft_search_n_execute(char **args, char **env);
char		*ft_get_abspath_filename(char *exec, char **env);
char		*ft_findexec(char *path, char *exec);
char		*ft_get_onlypaths(char **env);
int			ft_process(t_cmd *cmd, t_sh *sh);



t_list		*ft_start_minishell(char **env);

t_list		*ft_split_to_lst_env(char **env);
void		ft_free_env_lst(void *env_lst);
void		ft_sort_env_lst(t_list *env_lst);
t_env		*ft_separate_key_value(char *env_str);

char		**ft_lst_env_to_split(t_list *lst_env);
char		**ft_lst_env_to_split_launch(t_list *lst_env);
char		**ft_lst_env_to_split_export(t_list *lst_env);
t_list		*ft_search_env(t_list *env, char *arg);
// int			ft_unset(char **args, t_list **env);
char		*ft_parse_env_var(char *line, t_sh *sh);

/* replacing $ by env var before exec */

void		ft_check_env_var(t_cmd *cmd, t_sh *sh);
char		*ft_is_in_env(char *str, t_sh *sh);
void		ft_replace_env_var(char *av, char *key, t_cmd *cmd, int	i);
char		*ft_strdup_env_var(int len, char *av, char *key);

# endif
