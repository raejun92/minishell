# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: suko <suko@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 19:56:50 by suko              #+#    #+#              #
#    Updated: 2021/10/14 12:15:52 by suko             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
SRCS=main.c ft_lexer.c ft_tokenizer.c ft_parser.c \
ft_syntax_checker.c ft_execute.c ft_env.c ft_utils.c ft_pwd.c \
ft_handle_dollar.c ft_builtin.c ft_check_red.c ft_echo.c \
ft_exit.c ft_export.c ft_export2.c ft_unset.c ft_utils2.c \
ft_export3.c ft_cd.c ft_execve.c ft_split.c ft_signal.c \
ft_check_stat.c

#OBJS=$(SRCS:.c=.o)

FLAGS=-Wall -Wextra -Werror
LDFLAGS="-L/usr/local/opt/readline/lib"
CPPFLAGS="-I/usr/local/opt/readline/include"
INCLUDES=./

.PHONY : all clean fclean re

all: $(NAME)

$(NAME): $(SRCS)
	gcc -I. $(FLAGS) $(SRCS) -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
# gcc -I. $(FLAGS) $(SRCS) -o $(NAME) -lreadline $(CPPFLAGS) $(LDFLAGS)

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
