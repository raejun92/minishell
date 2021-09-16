#include "minishell.h"

static int	is_delimiter(char c, int *del)
{
	if (c == '|' || c == '>' || c == '<')
	{
		(*del) += 1;
		return (1);
	}
	else
	{
		if (c != ' ')
			*del = 0;
		return (0);
	}
}

static	int	ft_print_error(char *input, int idx, int type)
{
	if (type == 0)
		return (0);
	if (idx == -1)
		printf("bash: syntax error near unexpected token \'newline\'\n");
	else
	{
		if (input[idx] == '<')
		{
			if (input[idx + 1] == '<')
				printf("bash: syntax error near unexpected token \'<<\'\n");
			else
				printf("bash: syntax error near unexpected token \'<\'\n");
		}
		else if (input[idx] == '>')
		{
			if (input[idx + 1] == '>')
				printf("bash: syntax error near unexpected token \'>>\'\n");
			else
				printf("bash: syntax error near unexpected token \'>\'\n");
		}
		else
			printf("bash: syntax error near unexpected token \'%c\'\n", \
			input[idx]);
	}
	return (-1);
}

int	ft_syntax_checker(char *input)
{
	int	i;
	int	del;
	int	quote;

	i = -1;
	del = 0;
	quote = 0;
	while (input[++i] != '\0')
	{
		if (!quote && input[i] == '\'')
			quote = 1;
		else if (!quote && input[i] == '"')
			quote = 2;
		else if ((quote == 1 && input[i] == '\'') || \
		(quote == 2 && input[i] == '"'))
			quote = 0;
		if (!quote && is_delimiter(input[i], &del))
		{
			if (!(del < 2 || (del == 2 && input[i - 1] == input[i] && \
			(input[i] == '>' || input[i] == '<'))))
				return (ft_print_error(input, i, del));
		}
	}
	return (ft_print_error(input, -1, del));
}
