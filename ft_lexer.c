#include "minishell.h"

int	ft_get_type(t_lexer *curr, int prev_type)
{
	if (curr->str[0] == '<' || curr->str[0] == '>')
		return (RED);
	else if (curr->str[0] == '|')
		return (PIPE);
	else if (prev_type == PIPE)
		return (CMD);
	else if ((prev_type == CMD || prev_type == OPT) && curr->str[0] == '-')
		return (OPT);
	else if (prev_type == CMD || prev_type == OPT)
		return (ARG);
	else if (prev_type == ARG)
		return (ARG);
}

int	ft_lexer(char *input)
{
	int		prev_type;
	int		red;
	t_lexer	*curr;

	ft_tokenizer(input);
	curr = g_uni.lexer_list;
	prev_type = PIPE;
	red = 0;
	while (curr->next != 0)
	{
		if (red)
		{
			curr->type = ARG;
			red = 0;
			curr = curr->next;
			continue ;
		}
		else if (curr->str[0] == '<' || curr->str[0] == '>')
			red = 1;
		curr->type = ft_get_type(curr, prev_type);
		if (!red)
			prev_type = curr->type;
		curr = curr->next;
	}
	return (0);
}
