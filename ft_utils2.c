#include "minishell.h"

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_contain(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

char	*ft_strdup(const char *s1)
{
	int		l;
	int		i;
	char	*str;

	l = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (!str)
		return (0);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	util_export(t_env *min, int fd)
{
	if (min->val == NULL)
	{
		write(fd, "declare -x ", ft_strlen("declare -x "));
		write(fd, min->key, ft_strlen(min->key));
		write(fd, "\n", 1);
	}
	else
	{
		write(fd, "declare -x ", ft_strlen("declare -x "));
		write(fd, min->key, ft_strlen(min->key));
		write(fd, "=\"", ft_strlen("=\""));
		write(fd, min->val, ft_strlen(min->val));
		write(fd, "\"\n", 2);
	}
}