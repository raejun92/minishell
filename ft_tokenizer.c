#include "minishell.h"

static int	is_delimiter(char c)
{
	if (c == ' ' || c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

static char	*ft_fill_str(char *s1, int start, int len, int quote)
{
	char			*result;
	unsigned int	i;
	unsigned int	j;

	result = malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	i = 0;
	j = start;
	while (i < len)
	{
		if (!(quote == 1 && s1[j] == '\'' || quote == 2 && s1[j] == '"'))
		{
			if (quote != 1 && s1[j] == '$')
				ft_handle_dollar(result, s1, &i, &j);
			else
				result[i] = s1[j];
			i++;
		}
		j++;
	}
	result[i] = '\0';
	return (result);
}

static void	add_token(char *input, int start, int end, int quote)
{
	t_lexer	*curr;
	int		i;
	int		j;
	int		len;
	if (quote % 3 == 0)
		len = end - start + 1;
	else
		len = end - start - 1;
	if (quote != 1)
		len += count_dollar(input, start, end, quote);
	curr = new_lexer(1);
	if (curr == 0)
		return (ft_error(0));
	curr->str = ft_fill_str(input, start, len, quote);
	curr->quote = quote % 3;
	if (quote == 0)
		curr->connect = 0;
	else
		curr->connect = 1;
	if (curr->str == 0)
		return (ft_error(0));
}

static void	handle_delimiter(char *input, int *start, int *end, int *quote)
{
	if (quote && *quote != 0)
		add_token(input, *start, *end, *quote);
	else if (quote && *start < *end)
		add_token(input, *start, *end - 1, 3);
	else
	{
		if (*start < *end)
			add_token(input, *start, *end - 1, 0);
		else if (!quote)
			new_lexer(0);
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
	if (quote && *quote == 0)
		*start -= 1;
	if (quote)
		*quote = 0;
}

void	ft_tokenizer(char *input)
{
	int		i;
	int		j;
	int		quote;

	i = -1;
	j = 0;
	quote = 0;
	while (input[++i] != '\0')
	{
		if ((!quote && input[i] == '\'') || (!quote && input[i] == '"'))
		{
			handle_delimiter(input, &j, &i, &quote);
			if (input[i] == '\'')
				quote = 1;
			else
				quote = 2;
		}
		else if (!quote && is_delimiter(input[i]))
			handle_delimiter(input, &j, &i, 0);
		else if (quote == 1 && input[i] == '\'' || \
		quote == 2 && input[i] == '"')
			handle_delimiter(input, &j, &i, &quote);
	}
	if (j < i)
		add_token(input, j, i - 1, 0);
}
