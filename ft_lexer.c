#include "minishell.h"

int	is_delimeter(char c)
{
	if (c == " " || c == "|" || c == ">" || c == "<")
		return (1);
	else
		return (0);
}
char	**ft_tokenizer(char *input)
{
	int		i;
	int		j;
	int		is_single;
	int		is_double;
	t_lexer	*curr;

	i = -1;
	is_single = 0;
	is_double = 0;
	curr = g_uni.lexer_list;
	while (input[++i] != '\0')
	{
		if (input[i] == "'" && !is_single && !is_double)
			is_single = 1;
		else if (input[i] == "'" && is_single && !is_double)
			is_single = 0;
		else if (input[i] == '"' && !is_single && !is_double)
			is_double = 1;
		else if (input[i] == '"' && !is_single && is_double)
			is_double = 0;
		else
		{

		}
	}
	return ;
}

int	ft_lexer(char *input)
{
	int		i;
	int		prev_type;
/*
	// 첫번째 무조건 cmd x redirect도 올 수 있음

	// cmd -> none(arg), red, pipe, dollar, opt
	//
	// redirect -> cmd, none, dollar
	// if redirect -> pipe, red : syntax error
	// if redirect (>, >>, <)-> dollar : dollar 명 파일
	// if redirect (<<) -> dollar : 해석 x,
	// pipe -> cmd, red
	// none -> cmd, red, none

	// dollar sign 처리가 먼저 필요! 왜냐하면 A="o" 일 때, ech$A 제대로 실행됨
	// 환경변수로 A=" 되어있는 경우, 이는 스트링 취급 echo $A 하면 " 인쇄
*/
/*
		1. prev == x(pipe)
			1.1 red
			1.2 else -> cmd; token에서 red, pipe이 나오기 전까지
		2. prev == cmd, opt?
			2.1 - -> opt
			2.2 | -> pipe
			2.3 >, >>, <, << -> red
			2.4 else arg("" '' 이면 무조건 arg)
		3. prev == red
			3.1 first arg -> file name
			3.2 others -> normal ...?
		4. prev == arg
			4.1 red
			4.2 pipe
			4.3 else arg
*/

	i = -1;
	prev_type = PIPE;
	// 나눌 때 ' '만이 기준이 되면 안됨. ex) echo "abc"| 에서 파이프 인식!
	// cmd가 입력되지 않았을 때는 붙어있으면 다 cmd로 인식
	// ft split 그대로 사용하면 안됨! 따옴표 내부 스페이스는 유지되어야 함
	tokens = ft_split(input);
	// quote 처리 필요
	while (tokens[++i] != 0)
	{
		// 따옴표 쌍 마무리 안되면 에러 -> 이건 앞에서 체크?
		//

	}
	return (0);
}
