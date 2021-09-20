#include "minishell.h"

t_lexer	*new_lexer(int type)
{
	t_lexer	*prev;
	t_lexer	*curr;

	prev = 0;
	curr = g_uni.lexer_list;
	while (curr != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (type == 1)
	{
		curr = malloc(sizeof(t_lexer));
		if (curr == 0)
			return (0);
		if (prev != 0)
			prev->next = curr;
		else
			g_uni.lexer_list = curr;
		curr->next = 0;
	}
	else
		prev->connect = 0;
	return (curr);
}

int	ft_get_type(t_lexer *curr, int prev_type)
{
	if (curr->quote == 0 && (curr->str[0] == '<' || curr->str[0] == '>'))
		return (RED);
	else if (curr->quote == 0 && curr->str[0] == '|')
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

void	merge_lexer(void)
{
	t_lexer	*curr;
	t_lexer	*temp;

	curr = g_uni.lexer_list;
	while (curr != 0)
	{
		if (curr->connect == 1 && curr->next != 0)
		{
			temp = curr->next;
			curr->str = ft_strjoin(curr->str, temp->str);
			curr->connect = temp->connect;
			curr->next = temp->next;
			free(temp);
		}
		else
			curr = curr->next;
	}
}

void	ft_lexer(char *input)
{
	int		prev_type;
	int		red;
	t_lexer	*curr;

	ft_tokenizer(input);
	merge_lexer();
	curr = g_uni.lexer_list;
	prev_type = PIPE;
	red = 0;
	while (curr != 0)
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
}
