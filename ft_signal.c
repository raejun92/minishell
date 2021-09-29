#include "minishell.h"

void	sigint_handler(void)
{
	t_parser	*curr_parser;

	curr_parser = g_uni.parser_list;
	if (g_uni.parser_list != 0)
		printf("^C");
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGKILL);
		curr_parser = curr_parser->next;
	}
	if (g_uni.parser_list != 0)
		rl_replace_line("", 1);
	printf("\n");
	if (g_uni.parser_list == 0)
		rl_on_new_line();
	rl_redisplay();
}

void	sigtstp_hanlder(void)
{
	t_parser	*curr_parser;
	static int	count = 0;

	curr_parser = g_uni.parser_list;
	if (g_uni.parser_list == 0)
		return ;
	printf("^Z");
	printf("[%d]+  Stopped\t\t\t%s", count++, g_uni.input);
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGSTOP);
		curr_parser = curr_parser->next;
	}
	rl_replace_line("", 1);
	printf("\n");
	rl_redisplay();
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
		sigint_handler();
	else if (signum == SIGTSTP)
		sigtstp_hanlder();
}
