#include "minishell.h"

int	is_delimeter(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

char	*ft_fill_str(char *s1, int start, int len, int quote)
{
	char			*result;
	unsigned int	i;
	unsigned int	j;

	result = malloc(sizeof(char) * (i + 1));
	if (result == 0)
		return (0);
	i = 0;
	j = start;
	while (i < len)
	{
		if (!(quote == 1 && s1[j] == '\'' || quote == 2 && s1[j] == '"'))
		{
			result[i] = s1[j];
			i++;
		}
		j++;
	}
	result[i] = '\0';
	return (result);
}

void	add_token(char *input, int start, int end, int quote)
{
	t_lexer	*curr;
	int		i;
	int		j;
	int		len;

	if (quote == 0)
		len = end - start + 1;
	else
		len = end - start - 1;
	curr = g_uni.lexer_list;
	while (curr->next != 0)
		curr = curr->next;
	curr->str = ft_fill_str(input, start, len, quote);
	curr->quote = quote;
	if (curr->str == 0)
		return (ft_error());
	curr->next = malloc(sizeof(t_lexer));
	curr->next->next = 0;
}

void	handle_delimeter(char *input, int *start, int *end, int *quote)
{
	if (quote)
		add_token(input, *start, *end, *quote);
	else
	{
		if (*start < *end)
			add_token(input, *start, *end - 1, 0);
		*start = *end;
		if (input[*end] == '|')
			add_token(input, *start, *end, 0);
		else if (input[*end] == '<' || input[*end] == '>')
		{
			if (input[*end] == input[(*end) + 1])
				*end = (*end) + 1;
			add_token(input, *start, *end, 0);
		}
	}
	*start = (*end) + 1;
	if (quote)
		*quote = 0;
}

int	ft_tokenizer(char *input)
{
	int		i;
	int		j;
	int		quote;

	i = -1;
	j = 0;
	quote = 0;
	while (input[++i] != '\0')
	{
		if (!quote && input[i] == '\'')
			quote = 1;
		else if (!quote && input[i] == '"')
			quote = 2;
		else if (!quote && is_delimeter(input[i]))
			handle_delimeter(input, &j, &i, 0);
		else if (quote == 1 && input[i] == '\'' || \
		quote == 2 && input[i] == '"')
			handle_delimeter(input, &j, &i, &quote);
	}
	if (j < i)
		add_token(input, j, i - 1, 0);
}
