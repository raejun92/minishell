#include "minishell.h"

// 기능: env에서 환경변수를 모두 검사헀는지 확인, 리턴: int(남아있으면 1 다 검사했으면 0)
static int	check_env(void)
{
	t_env	*tmp;

	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		if (tmp->check == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

// 기능: envp 문자열 오름차순의 맨뒤 key값, 리턴: char *(key값)
static char	*find_envp_max(void)
{
	t_env	*tmp;
	char	*max;

	tmp = g_uni.env_list;
	max = tmp->key;
	while (tmp != 0)
	{
		if (ft_strcmp(tmp->key, max) > 0)
			max = tmp->key;
		tmp = tmp->next;
	}
	return (max);
}

// 기능: env의 check변수를 1로 바꿈, 리턴: void
static void	input_env_check(t_env *tmp, char *min)
{
	while (tmp != 0)
	{
		if (tmp->key == min)
			tmp->check = 1;
		tmp = tmp->next;
	}
}

//기능: env를 문자열 오름차순으로 출력, 리턴: int(0)
int	print_export(void)
{
	t_env	*tmp;
	t_env	*min;
	char	*max;
	
	max = find_envp_max();
	while (check_env())
	{
		tmp = g_uni.env_list;
		min = get_env(max);
		while (tmp != 0)
		{
			if (tmp->check == 0 && ft_strcmp(min->key, tmp->key) > 0)
				min = tmp;
			tmp = tmp->next;
		}
		if (min->val == NULL)
			printf("declare -x %s\n", min->key);
		else
			printf("declare -x %s=\"%s\"\n", min->key, min->val);
		input_env_check(g_uni.env_list, min->key);
	}
	init_env_check();
	return (0);
}

int	ft_export(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;
	int		ret;

	curr_lexer = curr_parser->start->next;
	if (curr_parser->start->next == NULL)
		ret = print_export();
	else
	{
		while (curr_lexer != curr_parser->end)
		{
			if (!count_equal(curr_lexer->str))
				ret = handle_is_not_equal(curr_lexer->str);
			else
				ret = handle_is_equal(curr_lexer->str, g_uni.env_list);
			if (ret == 1)
				break ;
			curr_lexer = curr_lexer->next;
		}
	}
	return (ret);
}