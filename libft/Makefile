# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alienard <alienard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 18:51:33 by alienard          #+#    #+#              #
#    Updated: 2020/06/14 14:20:02 by cdai             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 		libft.a

SRCS =		./ft_calloc.c \
			./ft_realloc.c \
			./ft_free_ptr.c \
			./ft_swap.c \
			./ft_isdigit.c \
			./ft_memcmp.c \
			./ft_strchr.c \
			./ft_strlen.c \
			./ft_tolower.c \
			./ft_atoi.c \
			./ft_atof.c \
			./ft_isalnum.c \
			./ft_isnum.c \
			./ft_isprint.c \
			./ft_memcpy.c \
			./ft_strcmp.c \
			./ft_strncmp.c \
			./ft_toupper.c \
			./ft_isalpha.c \
			./ft_memccpy.c \
			./ft_memmove.c \
			./ft_strlcat.c \
			./ft_strnstr.c \
			./ft_bzero.c \
			./ft_isascii.c \
			./ft_isspace.c \
			./ft_memchr.c \
			./ft_memset.c \
			./ft_strlcpy.c \
			./ft_strrchr.c \
			./ft_strdup.c \
			./ft_calloc.c \
			./ft_itoa.c \
			./ft_substr.c \
			./ft_strjoin.c \
			./ft_split.c \
			./ft_split_charset.c \
			./ft_strtok.c \
			./ft_strtok_r.c \
			./ft_strtrim.c \
			./ft_strmapi.c \
			./ft_putchar_fd.c \
			./ft_putstr_fd.c \
			./ft_putendl_fd.c \
			./ft_putnbr_fd.c \
			./ft_lstnew_bonus.c \
			./ft_lstadd_front_bonus.c \
			./ft_lstsize_bonus.c \
			./ft_lstlast_bonus.c \
			./ft_lstadd_back_bonus.c \
			./ft_lstdelone_bonus.c \
			./ft_lstclear_bonus.c \
			./ft_lstiter_bonus.c \
			./ft_lstmap_bonus.c \
			./ft_printf.c \
			./ft_padding.c \
			./ft_preci.c \
			./ft_conv.c \
			./ft_conv_2.c \
			./ft_putnbr_base.c \
			./ft_len_hexa.c \
			./ft_dprintf.c \
			./ft_padding_dprintf.c \
			./ft_preci_dprintf.c \
			./ft_conv_dprintf.c \
			./ft_conv_2_dprintf.c \
			./ft_putnbr_base_dprintf.c \
			./ft_len_hexa_dprintf.c \
			./ft_fprintf.c \
			./ft_padding_fprintf.c \
			./ft_preci_fprintf.c \
			./ft_conv_fprintf.c \
			./ft_conv_2_fprintf.c \
			./ft_putnbr_base_fprintf.c \
			./ft_len_hexa_fprintf.c \
			./get_next_line.c \
			./ft_free_split.c \
			./ft_lstsplit.c \
			./ft_lstdel_last.c \
			./ft_strs_sort.c \
			./ft_splitadd_back.c \
			./ft_splitcpy.c \
			./ft_strsort.c \
			./ft_split_to_lst.c \
			./ft_lstdel_between.c

OBJS = 		$(SRCS:.c=.o)

CC =		gcc

RM = 		rm -f

AR = 		ar rc

HEADER = 	./

CFLAGS =	-Wall -Wextra -Werror -g

.c.o:		$(SRCS)
			$(CC) $(CFLAGS) -c $< -I $(HEADER) -o $(<:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)

clean:
			$(RM) $(OBJS) $(OBJSBONUS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

CLANG =		clang

OBJS_TEST =	$(SRCS:.c=.o)

.c.o:
			$(CLANG) $(CFLAGS) -c $< -I $(HEADER) -o $(<:.c=.o)

test:		$(OBJS_TEST)
			$(AR) $(NAME) $(OBJS)

.PHONY:		re all clean fclean
