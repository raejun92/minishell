#include "minishell.h"

// 기능: env의 check를 모두 0으로 바꿈, 리턴: void
void	init_env_check(void)
{
	t_env *tmp;

	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		tmp->check = 0;
		tmp = tmp->next;
	}
}

// 기능: '='의 개수 확인(1개 이상이면 참), 리턴: int(=존재하면 1, 아니면 0)
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

// 기능: export에 key값이 존재하는지 확인, 리턴: int(존재하면 1, 아니면 0)
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

// 기능: export에 "="없이 들어올 때(export abc) 새로운 env 생성 및 추가, 리턴: int(에러 1 아니면 0) 
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

// 기능: 문자열 처음에 알파벳 또는 '_'인지 확인하고 문자열중 알파벳, 숫자, '_'인지 확인, 리턴: int(알파벳 또는 _ 아니면 1, 맞으면 0)
int	check_export_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_' || str[i] == '/' || str[i] == '.' || str[i] == ':')) // 숫자는 처음에 못들어옴
			return (1);
	while (str[++i] != '\0')
	{
		if (!(ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]) || \
		str[i] == '=' || str[i] == '/' || str[i] \
		== '.' || str[i] == ':')) // 처음 이후 숫자 가능
			return (1);
	}
	return (0);
}