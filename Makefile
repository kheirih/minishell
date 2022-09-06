# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkheiri <hkheiri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/02 05:34:06 by hkheiri           #+#    #+#              #
#    Updated: 2022/06/02 05:34:06 by hkheiri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell 
FLAGS=  -Wall -Wextra -Werror -I /Users/$(USER)/.brew/opt/readline/include -fsanitize=address
CC= gcc
INCLUDE= INC/
SRC =	SRC/checks.c SRC/env_parse.c SRC/env_utils.c SRC/exec.c SRC/execute_builtin.c SRC/filel.c \
		SRC/handle_heredoc.c SRC/main.c SRC/open_filel.c SRC/parser.c SRC/parser_utils.c SRC/tok_utils.c \
		SRC/tokenizer.c builtin/ft_cd.c builtin/ft_echo.c builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd_env.c \
		builtin/ft_unset.c

OBJ= 	checks.o env_parse.o env_utils.o exec.o execute_builtin.o filel.o \
		handle_heredoc.o main.o open_filel.o parser.o parser_utils.o tok_utils.o \
		tokenizer.o ft_cd.o ft_echo.o ft_exit.o ft_export.o ft_pwd_env.o \
		ft_unset.o

all: $(NAME)

$(NAME): $(SRC)
	make -C libft/ all
	$(CC) -c $(FLAGS) -I $(INCLUDE) $(SRC) 
	$(CC) $(FLAGS) -L /users/$(USER)/.brew/opt/readline/lib -lreadline -I $(INCLUDE) $(OBJ) libft/libft.a -o $(NAME)

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all
	make -C libft/ re
