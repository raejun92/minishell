#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define CMD 0
# define ARG 1
# define OPT 2
# define PIPE 3
# define RED 4
# define DOLLAR 5

# define NONE 0
# define SINGLE 1
# define DOUBLE 2

typedef struct s_lexer
{
	char				*str;
	int					type;
	int					quote;
	int					connect;
	struct s_lexer		*next;
}t_lexer;

// echo -n "This is an example" | cat -e > file1 | cat < file1 > file2
/*
			pipe(1)
	echo~           pipe(2)
	             red        red
				cat          red
				            cat
*/
// > "abc"
// >(red) -> "abc"(arg)
// echo(cmd) -> -n(opt) -> "This is "(arg)
// "|"(pipe)
// -> cat(cmd) -> <(red) stdin out
typedef struct s_parser
{
	t_lexer *start;
	t_lexer *end;
	int				pipe[2];
	int				fd_in;
	int				fd_out;
	struct s_parser	*next;
}t_parser;

typedef struct s_env
{
	char			*key;
	char			*val;
	struct s_env	*next;
}t_env;

typedef struct s_uni
{
	t_lexer		*lexer_list;
	t_parser	*parser_list;
	int			exit_status;
	t_env		*env_list;
	// 환경변수 리스트
	// tokenizer 리스트 ?
	// lexer 리스트
	// parser 리스트 ?
}t_uni;

t_uni	g_uni;

/* main.c */
void	ft_error(void);

/* ft_syntax_checker.c */
int		ft_syntax_checker(char *input);

/* ft_tokenizer.c */
int		ft_tokenizer(char *input);

/* ft_lexer.c */
int		ft_lexer(char *input);
t_lexer	*new_lexer(int type);

/* ft_parser.c */
void	ft_parser(void);
void	view_parser_list();

/* ft_execute */
void	ft_execute(void);

/* ft_split.c */
char	**ft_split(char const *s);

/* ft_utils.c */
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strcmp(char *s1, char *s2);

/* ft_env.c */
void	save_env_variable(char **envp);
void	print_envp(void);

/* ft_pwd.c */
void	print_pwd(void);

#endif
