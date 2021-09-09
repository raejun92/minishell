#include "minishell.h"

int	ft_init_uni(void)
{
	g_uni.lexer_list = malloc(sizeof(t_lexer));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	// 변수 초기화
	char	*input;

	ft_init_uni();
	// 입력받은 명령어 실행
	while (1)
	{
		// 입력 받기 -> readline
		input = readline("minishell$ ");
		if (input)
			printf("%s\n", input);
		else
			break ; // EOF 일때 탈출
		add_history(input); // 출력한 문자열을 저장하여 방향키 up, down으로 확인 가능
		// 인풋 에러 체크
		// 토크나이저, 렉서, 파서
		//ft_lexer(input);

		// 실행(fork)

		free(input);
	}
	return	(0);
}
