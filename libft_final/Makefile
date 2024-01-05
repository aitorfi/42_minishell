# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alvicina <alvicina@student.42urduliz.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 10:08:04 by alvicina          #+#    #+#              #
#    Updated: 2023/11/24 11:27:58 by alvicina         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c \
		ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_printf_char.c ft_printf_hexa.c \
		ft_printf_int.c ft_printf_pointer.c ft_printf_str.c ft_printf_unsg_int.c ft_printf.c \
		get_next_line_bonus.c get_next_line_utils_bonus.c \

BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c \

OBJS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I.

NAME = libft.a

$(NAME): $(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

all: $(NAME)

clean: 
		$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
				ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re
