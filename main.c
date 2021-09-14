#include "minishell.h"

void	ft_error(void)
{
	exit(0);
}

int	ft_init_uni(void)
{
	g_uni.lexer_list = malloc(sizeof(t_lexer));
	g_uni.lexer_list->next = 0;
	return (0);
}

int	ft_reset_uni(void)
{
	t_lexer	*curr_lexer;
	t_lexer	*temp_lexer;

	curr_lexer = g_uni.lexer_list;
	while (curr_lexer->next != 0)
	{
		temp_lexer = curr_lexer;
		free(curr_lexer->str);
		curr_lexer = temp_lexer->next;
	}
	g_uni.lexer_list = curr_lexer;
}

int	main(int argc, char **argv, char **envp)
{
	// 변수 초기화
	char	*input;

	ft_init_uni();
	// 환경변수 저장
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
		// syntax error check
		ft_lexer(input);
		ft_parser();
		view_parser_list();
		// 실행(fork)
		// 환경변수 변환
		// 절대경로/상대경로
		// 파이프 마지막이 아니거나, 빌트인 명령어 -x > fork
		// 파이프 마지막인데 빌트인 -> ?
		// 파이프로 인풋 아웃풋 연결?

		// 시그널 처리 -> 컨트롤 + 버튼 처리
		ft_reset_uni();
		free(input);
	}
	// 정리
	return (0);
}
