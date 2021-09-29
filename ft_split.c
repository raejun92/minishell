#include "minishell.h"

static unsigned int	cnt_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	word_cnt;

	i = 0;
	word_cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			word_cnt++;
			i++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (word_cnt);
}

static void	str_point_len(char **str_point, unsigned int *str_len, char c)
{
	unsigned int	i;

	*str_point = *str_point + *str_len;
	*str_len = 0;
	while (**str_point && **str_point == c)
		(*str_point)++;
	i = 0;
	while ((*str_point)[i] && (*str_point)[i] != c)
	{
		(*str_len)++;
		i++;
	}
	return ;
}

char	**free_double_pointer(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i++;
	}
	free(str);
	str = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char			**str;
	char			*str_point;
	unsigned int	i;
	unsigned int	word_cnt;
	unsigned int	str_len;

	if (!s)
		return (0);
	word_cnt = cnt_word(s, c);
	if (!(str = (char **)malloc(sizeof(char *) * (word_cnt + 1))))
		return (0);
	str_point = (char *)s;
	str_len = 0;
	i = 0;
	while (i < word_cnt)
	{
		str_point_len(&str_point, &str_len, c);
		if (!(str[i] = (char *)malloc(sizeof(char) * (str_len + 1))))
			return (free_double_pointer(str));
		ft_strlcpy(str[i], str_point, str_len + 1);
		i++;
	}
	str[i] = 0;
	return (str);
}
