#include "minishell.h"

void	sigint_handler(void)
{
	t_parser	*curr_parser;

	curr_parser = g_uni.parser_list;
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGKILL);
		curr_parser = curr_parser->next;
	}
	rl_replace_line("", 0);
	printf("\n");
	if (g_uni.parser_list == 0)
	{
		g_uni.exit_status = 1;
		rl_on_new_line();
	}
	rl_redisplay();
}

void	sigquit_handler(void)
{
	t_parser	*curr_parser;

	curr_parser = g_uni.parser_list;
	if (g_uni.parser_list == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGQUIT);
		curr_parser = curr_parser->next;
	}
	rl_replace_line("", 0);
	if (g_uni.parser_list == 0)
		rl_on_new_line();
	rl_redisplay();
}

void	sigtstp_handler(void)
{
	t_parser	*curr_parser;

	curr_parser = g_uni.parser_list;
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGTERM);
		curr_parser = curr_parser->next;
	}
	rl_replace_line("", 0);
	printf("\n");
	if (g_uni.parser_list == 0)
		rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
		sigint_handler();
	else if (signum == SIGQUIT)
		sigquit_handler();
	else if (signum == SIGTSTP)
		sigtstp_handler();
}
