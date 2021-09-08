#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

// 렉서 타입 지정
#define CMD 0

typedef struct	s_lexer
{
	char	*str;
	int		type;
	struct s_lexer	*next;
}t_lexer;

typedef struct	s_uni
{
	t_lexer		*lexer_list;
	// 환경변수 리스트
	// tokenizer 리스트 ?
	// lexer 리스트
	// parser 리스트 ?
}t_uni;

t_uni g_uni;

/* tokenizer.c */
int	ft_lexer(char *input);

/* ft_split.c */
char	**ft_split(char const *s);