#include "minishell.h"

void	init_env_check(void)
{
	t_env	*tmp;

	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		tmp->check = 0;
		tmp = tmp->next;
	}
}

int	count_equal(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			cnt++;
		i++;
	}
	return (cnt);
}

int	check_export_key(char *str)
{
	t_env	*tmp;

	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		if (ft_strcmp(tmp->key, str) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	handle_is_not_equal(char *str)
{
	t_env	*tmp;
	t_env	*new;

	tmp = g_uni.env_list;
	if (check_export_valid(str))
	{
		printf("bash: export: `%s': not a valid identifier\n", str);
		return (1);
	}
	else
	{
		if (check_export_key(str))
			return (0);
		new = new_env();
		new->key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		ft_strlcpy(new->key, str, ft_strlen(str) + 1);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

int	check_export_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_' || str[i] == '/' || \
	str[i] == '.' || str[i] == ':'))
		return (1);
	while (str[++i] != '\0')
	{
		if (!(ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]) || \
		str[i] == '=' || str[i] == '/' || str[i] \
		== '.' || str[i] == ':'))
			return (1);
	}
	return (0);
}
