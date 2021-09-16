#include "minishell.h"

void	ft_execute(void)
{
	t_parser	*curr_parser;
	pid_t		curr_pid;
	int			prev_in;

	curr_parser = g_uni.parser_list;
	prev_in = -1;
	while (curr_parser->next != 0)
	{
		if (pipe(curr_parser->pipe) != 0)
			return (ft_error());
		curr_pid = fork();
		if (curr_pid < 0)
			return (ft_error());
		if (curr_pid == 0)
		{
			if (prev_in >= 0)
			{
				dup2(prev_in, 0);
				close(prev_in);
			}
			dup2(curr_parser->pipe[1], 1);
			// builtin check
			// 아니면 execve로 실행
			// status 처리 필요
			exit(0);
		}
		else
		{
			waitpid(curr_pid, &(g_uni.exit_status), 0);
			close(curr_parser->pipe[1]);
			prev_in = curr_parser->pipe[0];
			//exit_status 체크
		}
		curr_parser = curr_parser->next;
	}
	// 마지막 작업은 여기서
	if (prev_in >= 0)
		close(prev_in);
}
