#include "minishell.h"

int	ft_lexer(char *input)
{
	char	**tokens;
	int		i;
	int		type;
	// 첫번째 무조건 cmd x redirect도 올 수 있음

	// cmd -> none(arg), red, pipe, dollar, opt
	//
	// redirect -> cmd, none, dollar
	// if redirect -> pipe, red : syntax error
	// if redirect (>, >>, <)-> dollar : dollar 명 파일
	// if redirect (<<) -> dollar : 해석 x,
	// pipe -> cmd, red
	// none -> cmd, red, none


	i = -1;
	// 나눌 때 ' '만이 기준이 되면 안됨. ex) echo "abc"| 에서 파이프 인식!
	// cmd가 입력되지 않았을 때는 붙어있으면 다 cmd로 인식
	tokens = ft_split(input);
	// quote 처리 필요
	while (tokens[++i] != 0)
	{
		// 따옴표 쌍 마무리 안되면 에러

	}
	return (0);
}
