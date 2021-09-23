#include "minishell.h"

static int	is_only_contain(char *str, char c, int start)
{
	int	i;

	i = start - 1;
	while (str[++i] != '\0')
	{
		if (str[i] != c)
			return (0);
	}
	return (1);
}
int	ft_echo(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;
	int		flag;
	int		fd;

	flag = 0;
	curr_lexer = curr_parser->start;
	while (curr_lexer != 0)
	{
		if (curr_lexer->type == OPT && is_only_contain(curr_lexer->str, 'n', 1))
			flag += 2;
		else if (curr_lexer->type != CMD)
		{
			if (flag == 1 || flag == 3)
				printf(" ");
			else
				flag += 1;
			printf("%s", curr_lexer->str);
		}
		curr_lexer = curr_lexer->next;
	}
	if (flag < 2)
		printf("\n");
	return (0);
}
