#include "minishell.h"

void	ft_error(int exit_status)
{
	exit(exit_status);
}

int	ft_init_uni(void)
{
	g_uni.lexer_list = 0;
	g_uni.parser_list = 0;
	g_uni.exit_status = 0;
	g_uni.input = 0;
	return (0);
}

int	ft_reset_uni(void)
{
	t_lexer		*curr_lexer;
	t_lexer		*temp_lexer;
	t_parser	*curr_parser;
	t_parser	*temp_parser;

	curr_lexer = g_uni.lexer_list;
	while (curr_lexer != 0)
	{
		temp_lexer = curr_lexer;
		free(curr_lexer->str);
		curr_lexer = temp_lexer->next;
		free(temp_lexer);
	}
	curr_parser = g_uni.parser_list;
	while (curr_parser != 0)
	{
		temp_parser = curr_parser;
		curr_parser = curr_parser->next;
		free(temp_parser);
	}
	g_uni.lexer_list = 0;
	g_uni.parser_list = 0;
	g_uni.input = 0;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char			*input;
	t_env			*curr_env;
	t_env			*temp_env;
	struct termios	old_term;
	struct termios	new_term;

	if (argc == 0 || argv == 0)
		return (0);
	ft_init_uni();
	ft_env(envp);
	tcgetattr(0, &old_term);
	tcgetattr(0, &new_term);
	new_term.c_lflag &= ~(ICANON | ECHOCTL);
	new_term.c_cc[VMIN] = 1;
	new_term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new_term);
	signal(SIGINT, ft_signal);
	signal(SIGTSTP, ft_signal);
	signal(SIGQUIT, ft_signal);
	input = 0;
	while (1)
	{
		new_term.c_lflag &= ~(ICANON | ECHOCTL);
		tcsetattr(0, TCSANOW, &new_term);
		input = readline("minishell$ ");
		if (!input)
		{
			printf("\x1b[1A\033[11Cexit\n");
			break ;
		}
		new_term.c_lflag |= (ICANON | ECHOCTL);
		tcsetattr(0, TCSANOW, &new_term);
		g_uni.input = input;
		add_history(input); // 출력한 문자열을 저장하여 방향키 up, down으로 확인 가능
		if (!ft_syntax_checker(input))
		{
			ft_lexer(input);
			ft_parser();
			//view_parser_list();
			if (g_uni.parser_list != 0)
				ft_execute();
			ft_reset_uni();
		}
		free(input);
	}
	curr_env = g_uni.env_list;
	while (curr_env != 0)
	{
		if (curr_env->key != 0)
			free(curr_env->key);
		if (curr_env->val != 0)
			free(curr_env->val);
		temp_env = curr_env;
		curr_env = curr_env->next;
		free(temp_env);
	}
	tcsetattr(0, TCSANOW, &old_term);
	return (g_uni.exit_status);
}
