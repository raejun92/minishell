#include "minishell.h"

static int	is_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	is_in_range(char *str)
{
	int			flag;
	int			i;
	long long	num;
	long long	temp;

	flag = 1;
	i = 0;
	num = 0;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		temp = (num * 10 + (flag) * (str[i] - '0'));
		i++;
		if (flag == -1 && temp > num)
			return (0);
		else if (flag == 1 && temp < num)
			return (0);
		else
			num = temp;
	}
	return (1);
}

static long long	stoll(char *str)
{
	int			flag;
	int			i;
	long long	num;

	flag = 1;
	i = 0;
	num = 0;
	if (str[i] == '-')
	{
		flag = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		num = (num * 10 + (flag) * (str[i] - '0'));
		i++;
	}
	return (num);
}

int	ft_exit(t_parser *curr_parser, int type)
{
	t_lexer		*curr_lexer;
	long long	status;

	status = g_uni.exit_status;
	curr_lexer = curr_parser->start;
	while (curr_lexer != 0)
	{
		if (curr_lexer->type != CMD)
		{
			if (!is_digit(curr_lexer->str) || !is_in_range(curr_lexer->str))
			{
				if (type == 1)
					ft_print_error(1, "exit", curr_lexer->str, \
		"numeric argument required");
				else
					ft_print_error(g_uni.err_pipe[1], "exit", curr_lexer->str, \
		"numeric argument required");
				exit(2);
				return (2);
			}
			status = stoll(curr_lexer->str);
			break ;
		}
		curr_lexer = curr_lexer->next;
	}
	if (curr_lexer == 0 || curr_lexer->next == 0)
		exit((unsigned char)status);
	ft_print_error(g_uni.err_pipe[1], "exit", 0, \
	"too many arguments");
	return (1);
}
