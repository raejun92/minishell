#include "minishell.h"

static	unsigned int	ft_isspace(char const c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||\
		c == '\f' || c == '\r' || c == ' ')
		return 1;
	else
		return 0;
}

static	unsigned int	ft_isincluded(char const *s)
{
	unsigned int	i;
	unsigned int	count;

	if (s == 0)
		return (0);
	i = -1;
	count = 0;
	while (s[++i] != '\0')
	{
		if (ft_isspace(s[i]) == 1)
			count++;
	}
	return (count);
}

static	char			**ft_free(char ***result, unsigned int count)
{
	unsigned int	i;

	i = count;
	while (i != 0)
	{
		free((*result)[--i]);
	}
	free(*result);
	return (0);
}

char					*ft_substr(const char *s,\
		unsigned int start, size_t len)
{
	char			*result;
	unsigned int	i;
	unsigned int	j;

	if (s == 0)
		return (0);
	result = malloc(sizeof(char) * (len + 1));
	if (result == 0)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0' && j < len)
	{
		if (i >= start)
		{
			result[j] = s[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

char					**ft_split(char const *s)
{
	char			**result;
	unsigned int	i;
	unsigned int	count;
	unsigned int	j;

	result = malloc(sizeof(char *) * (ft_isincluded(s) + 2));
	if (result == 0 || s == 0)
		return (0);
	i = -1;
	count = 0;
	while (s[++i] != '\0')
	{
		j = i;
		while (ft_isspace(s[i]) == 0 && s[i] != '\0')
			i++;
		if (j != i)
		{
			result[count] = ft_substr(s, j, (i--) - j);
			if (result[count] == 0)
				return (ft_free(&result, count));
			count++;
		}
	}
	result[count] = 0;
	return (result);
}