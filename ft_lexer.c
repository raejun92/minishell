#include "minishell.h"

int	ft_lexer(char *input)
{
	char **tokens;
	int i = 0;
	int type = -1;
	// 첫번째 무조건 cmd
	// cmd -> none(arg), red, pipe, dollar, opt
	// redirect -> cmd, none
	// pipe -> cmd
	// none -> cmd, red, none

	tokens = ft_split(input);
	// quote 처리 필요
	while (tokens[i] != 0)
	{
		// 따옴표 쌍 마무리 안되면 에러
		i++;
		
	}
	return (0);
}