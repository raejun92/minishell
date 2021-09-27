NAME=minishell
SRCS=main.c ft_lexer.c ft_tokenizer.c ft_parser.c \
ft_syntax_checker.c ft_execute.c ft_env.c ft_utils.c ft_pwd.c \
ft_handle_dollar.c ft_builtin.c ft_check_red.c ft_echo.c \
ft_exit.c ft_export.c ft_export2.c ft_unset.c ft_utils2.c \
ft_export3.c ft_cd.c

OBJS=$(SRCS:.c=.o)

FLAGS=-Wall -Wextra -Werror
INCLUDES=./

all: $(NAME)

$(NAME): $(SRCS)
	gcc -I. $(FLAGS) $(SRCS) -o $(NAME) -lreadline
