# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afidalgo <afidalgo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/06 17:48:55 by alejandro         #+#    #+#              #
#    Updated: 2024/01/08 20:27:09 by afidalgo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SETUP

NAME            = minishell
CC              = gcc
RM              = rm -rf
FLAGS           = -Wall -Wextra -Werror -Ilibft #-g3 -fsanitize=address
LREADLINE_FLAGS = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
READLINE        = -I /Users/$(USER)/.brew/opt/readline/include

#FILES AND PATH

HEADER_SRCS = minishell.h
HEADER_DIR  = includes/
HEADER      = $(addprefix $(HEADER_DIR), $(HEADER_SRCS))

MPATH_SRCS  = \
	main.c sig_handler.c cmd_preprocessor.c ast_builder.c ast_processor.c \
	builtin_env.c builtin_pwd.c utils.c ast_utils.c
MPATH_DIR   = mandatory/
MPATH       = $(addprefix $(MPATH_DIR), $(MPATH_SRCS))
OBJ_M       = $(MPATH:.c=.o)

BPATH_SRCS  = 
BPATH       = $(addprefix $(BPATH_DIR), $(BPATH_SRCS))
OBJ_B       = $(BPATH:.c=.o)

#COMMANDS
all:        lib $(NAME)

$(NAME):    $(OBJ_M)
		    @$(CC) $(FLAGS) $(OBJ_M) $(LREADLINE_FLAGS) -Llibft -lft -o $(NAME) 

%.o: %.c $(HEADER) Makefile
		    @$(CC) $(FLAGS) $(READLINE) -c $< -o $@

bonus:      lib $(OBJ_B)
			@$(CC) $(FLAGS) $(OBJ_B) $(LREADLINE_FLAGS) -Llibft -lft -o $(NAME)

clean:
	        @$(RM) $(OBJ_M)
			@$(RM) $(OBJ_B)
	        $(MAKE) -C libft clean

fclean:	    clean
		    @$(RM) $(NAME)

re:         fclean all

lib:
	        $(MAKE) -C libft

.PHONY: all execute clean fclean re lib
