NAME=minishell
SRCS=main.c ft_lexer.c ft_split.c ft_tokenizer.c ft_parser.c
OBJS=$(SRCS:.c=.o)

FLAGS=-Wall -Wextra -Werror
INCLUDES=./

all: $(NAME)

$(NAME): $(SRCS)
	gcc -I. $(SRCS) -o $(NAME) -lreadline
