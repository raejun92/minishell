all:
	gcc -I. main.c ft_split.c ft_lexer.c -lreadline
	./a.out
