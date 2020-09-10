# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alienard <alienard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 18:51:33 by alienard          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2020/09/02 11:27:36 by alienard         ###   ########.fr        #
=======
#    Updated: 2020/09/01 23:14:12 by cdai             ###   ########.fr        #
>>>>>>> origin/cdai3
#                                                                              #
# **************************************************************************** #

NAME = 			libft.a

BILIST_DIR		= bilist
CONVERT_DIR		= convert
DPRINTF_DIR		= dprintf
FPRINTF_DIR		= fprintf
GNL_DIR			= gnl
IS_DIR			= is
LIST_DIR		= list
MEM_DIR			= mem
PRINT_DIR		= print
PRINTF_DIR		= printf
STR_DIR			= str

INCLUDES_DIR	= ./headers

_BILIST 		= ft_dlst_addafter.c \
					ft_dlst_addback.c \
					ft_dlst_addbefore.c \
					ft_dlst_addfront.c \
					ft_dlst_del.c \
					ft_dlst_delone.c \
					ft_dlst_goto_end.c \
					ft_dlst_new_node.c \
					ft_dlst_reverse.c \
					ft_init_dlst.c \
					ft_len_dlst.c \
					ft_print_dlst.c
_CONVERT		= ft_atof.c \
					ft_atoi.c \
					ft_atoi_long.c \
					ft_is_in_min_max_atoi_long.c \
					ft_itoa.c \
					ft_itoa_count.c \
					ft_tolower.c \
					ft_toupper.c
_DPRINTF		= ft_conv_2_dprintf.c \
					ft_conv_dprintf.c \
					ft_dprintf.c \
					ft_len_hexa_dprintf.c \
					ft_padding_dprintf.c \
					ft_preci_dprintf.c \
					ft_putnbr_base_dprintf.c
_FPRINTF		= ft_conv_2_fprintf.c \
					ft_conv_fprintf.c \
					ft_fprintf.c \
					ft_len_hexa_fprintf.c \
					ft_padding_fprintf.c \
					ft_preci_fprintf.c \
					ft_putnbr_base_fprintf.c
_GNL			= get_next_line.c \
					get_next_line_utils.c
_IS				= ft_isalnum.c \
					ft_isalpha.c \
					ft_isascii.c \
					ft_isdigit.c \
					ft_isnum.c \
					ft_isprint.c \
					ft_isspace.c \
					ft_ischarset.c \
					ft_str_isdigit.c
_LIST			= ft_lstadd_back_bonus.c \
					ft_lstclear_bonus.c \
					ft_lstdel_last.c \
					ft_lstiter_bonus.c \
					ft_lstmap_bonus.c \
					ft_lstsize_bonus.c \
					ft_split_to_lst.c \
					ft_lstadd_front_bonus.c \
					ft_lstdel_between.c \
					ft_lstdelone_bonus.c \
					ft_lstlast_bonus.c \
					ft_lstnew_bonus.c \
					ft_lstsplit.c \
					ft_lstadd_before.c \
					ft_lst_to_split.c \
					ft_lstdelif_false.c \
					ft_print_lst.c
_MEM			= ft_bzero.c \
					ft_calloc.c \
					ft_free_ptr.c \
					ft_free_double_array.c \
					ft_free_split.c \
					ft_memccpy.c \
					ft_memchr.c \
					ft_memcmp.c \
					ft_memcpy.c \
					ft_memmove.c \
					ft_memset.c \
					ft_realloc.c \
					ft_swap.c
_PRINT			= ft_putchar_fd.c \
					ft_putendl_fd.c \
					ft_putnbr_fd.c \
					ft_putstr_fd.c \
					ft_print_double_array.c
_PRINTF			= ft_conv.c \
					ft_conv_2.c \
					ft_len_hexa.c \
					ft_padding.c \
					ft_preci.c \
					ft_printf.c \
					ft_putnbr_base.c
_STR			= ft_split.c \
					ft_splitadd_back.c \
					ft_strchr.c \
					ft_strdup.c \
					ft_dstrdup.c \
					ft_strlcat.c \
					ft_strlen.c \
					ft_strncmp.c \
					ft_strrchr.c \
					ft_strsort.c \
					ft_strtok_r.c \
					ft_substr.c \
					ft_split_charset.c \
					ft_splitcpy.c \
					ft_strcmp.c \
					ft_strjoin.c \
					ft_dstrjoin_free.c \
					ft_strlcpy.c \
					ft_strmapi.c \
					ft_strnstr.c \
					ft_strs_sort.c \
					ft_strtok.c \
					ft_strtrim.c

BILIST 			= $(addprefix $(BILIST_DIR)/, $(_BILIST))
CONVERT			= $(addprefix $(CONVERT_DIR)/, $(_CONVERT))
DPRINTF			= $(addprefix $(DPRINTF_DIR)/, $(_DPRINTF))
FPRINTF			= $(addprefix $(FPRINTF_DIR)/, $(_FPRINTF))
GNL				= $(addprefix $(GNL_DIR)/, $(_GNL))
IS				= $(addprefix $(IS_DIR)/, $(_IS))
LIST			= $(addprefix $(LIST_DIR)/, $(_LIST))
MEM				= $(addprefix $(MEM_DIR)/, $(_MEM))
PRINT			= $(addprefix $(PRINT_DIR)/, $(_PRINT))
PRINTF			= $(addprefix $(PRINTF_DIR)/, $(_PRINTF))
STR				= $(addprefix $(STR_DIR)/, $(_STR))

SRCS 			= $(BILIST) $(CONVERT) $(DPRINTF) $(FPRINTF) $(GNL) $(IS) $(LIST) $(MEM) $(PRINT) $(PRINTF) $(STR)
OBJS			= $(SRCS:.c=.o)
OBJS_TEST 		= $(SRCS:.c=.o)

CFLAGS			= -Wall -Wextra -Werror -g
CC				= gcc
CLANG			= clang

RM				= rm -f
AR				= ar rc
HEADER			= ./

# .c.o:		$(SRCS)
			# $(CC) $(CFLAGS) -c $< -I $(INCLUDES_DIR) -o $(<:.c=.o)

.c.o:			$(SRCS)
				$(CLANG) $(CFLAGS) -c $< -I $(INCLUDES_DIR) -o $(<:.c=.o)

all:			$(NAME)

$(NAME):		$(OBJS) headers/libft.h
				$(AR) $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) $(OBJSBONUS)

fclean:			clean
				$(RM) $(NAME)

norme:
				norminette $(SRCS) headers/libft.h

re:				fclean all

test:			$(OBJS_TEST)
				$(AR) $(NAME) $(OBJS)

.PHONY:			re all clean fclean
