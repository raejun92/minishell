#include "minishell.h"

void	sigint_handler(void)
{
	t_parser	*curr_parser;

	curr_parser = g_uni.parser_list;
	while (!curr_parser)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGKILL);
		curr_parser = curr_parser->next;
	}
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
		sigint_handler();
}
