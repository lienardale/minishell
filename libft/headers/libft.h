/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alienard <alienard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:12:43 by alienard          #+#    #+#             */
/*   Updated: 2020/08/30 15:44:58 by alienard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

# ifndef EXT_ALPHA
#  define EXT_ALPHA "ÄÅÇÉÑÖÜáàâäãåçéèêëíìîïñóòôöõúùûüÆçæøâêôûƒéàèùÃÕŒœÿŸﬁﬂÂÊÁËÈÍÎÏÌÓÔÒÚÛÙ"
# endif

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			ft_bzero(void *s, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *str);
size_t			ft_double_strlen(char **str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *haystack, const char *needle,
		size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
long			ft_atoi_long(const char *str);
int				ft_is_in_min_max_atoi_long(const char *str);
double			ft_atof(const char *str);
char			*ft_itoa(int n);
int				ft_itoa_count(int i);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isnum(char *c);
int				ft_str_isdigit(char *str);
int				ft_ischarset(char *set, char c);
void			*ft_calloc(size_t count, size_t size);
void			*ft_realloc(void *ptr, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_strdup_free(const char *s1);
char			**ft_dstrdup(char **s1);
char			**ft_dstrdup_free(char **s1);
void			*ft_free_ptr(void *ptr);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_dstrjoin(char **s1, char **s2);
char			**ft_dstrjoin_free(char **s1, char **s2);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strtok(char *str, const char *sep);
char			*ft_strtok_r (char *s, const char *delim, char **save_ptr);
char			**ft_split(char const *s, char c);
char			**ft_split_charset(const char *s, const char *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_swap_int(int *a, int *b);
void			ft_swap_double(double *a, double *b);
void			ft_swap_addr(void **a, void **b);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_print_double_array(char **str, char *name);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strtok(char *restrict str, const char *restrict sep);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void*),
		void (*del)(void *));
char			**ft_free_split(char **data);
void			ft_free_double_array(char **str);
t_list			*ft_lstsplit(char *str, char c);
void			ft_lstdel_last(t_list *lst);
char			**ft_strs_sort(char **strs, int strs_len);
char			**ft_splitadd_back(char **strs, char *str);
char			**ft_splitcpy(char **src);
int				get_next_line(int fd, char **line);
void			ft_strsort(char **strs);
t_list			*ft_split_to_lst(char **strs);
void			ft_lstdel_between(t_list **alst, void *content, void (*del)(void*));
void			ft_lstadd_before(t_list **alst, t_list *new, t_list *next);
char			**ft_lst_to_split(t_list *lst);
void			ft_print_lst(t_list *lst, char *str);

#endif
