#include "minishell.h"

void	print_export(void)
{
	t_env	*tmp;

	tmp = g_uni.env_list;
}

void	export(t_parser *curr_parser)
{
	/* TODO
		1 export만 썼을 때
			- declare -x 환경변수들
			- 기존에 존재하는 환경변수들 정렬
			- 새로 추가되는 환경변수는 기존아래에 추가
			- 새로 추가된 환경변수에서 또 새로추가시 정렬 
				ex) a=a
					b=b 에서 ab=ab추가하면 a=a b=b사이에 들어감
		2 export a
		3 export a="hello" or a=hello
		4 export a=a b=b c=c ...
		5 export aa=aa bb = bb aa는 들어가고 bb에 대한 오류 처리
		6 export는 pipe로 아무것도 안넘어가는듯?
	 */
	if (curr_parser->next == NULL && ft_strcmp(curr_parser->start->str, "export") == 0)
		print_export();
}

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

// 기능: envp 문자열의 가장 뒷순 key값, 리턴: char *(key값)
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

//기능: env를 문자열 오름차순 정렬, 리턴: void
void	set_export(void)
{
	t_env	*tmp;
	char	*max;
	char	*min;

	max = find_envp_max();
	while (check_env())
	{
		tmp = g_uni.env_list;
		min = max;
		while (tmp != 0)
		{
			if (tmp->check == 0 && ft_strcmp(min, tmp->key) > 0)
				min = tmp->key;
			tmp = tmp->next;
		}
		tmp = g_uni.env_list;
		while (tmp != 0)
		{
			if (tmp->key == min)
				tmp->check = 1;
			tmp = tmp->next;
		}
	}
}