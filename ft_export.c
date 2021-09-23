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

static void	handle_is_equal2(char *str, t_env *new, t_env *tmp)
{
	new = new_env();
	save_env_variable(new, str);
	if (check_export_key(new->key))
	{
		tmp = get_env(new->key);
		free(tmp->val);
		tmp->val = new->val;
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	handle_is_equal(char *str, t_env *tmp)
{
	t_env	*new;

	if (check_export_valid(str) || str[0] == '=')
		printf("bash: export: `%s': not a valid identifier\n", str);
	else if (count_equal(str) == 1 && str[ft_strlen(str) - 1] == '=')
	{
		str[ft_strlen(str) - 1] = '\0';
		if (check_export_key(str))
		{
			tmp = get_env(str);
			free(tmp->val);
			tmp->val = "";
			return ;
		}
		new = new_env();
		new->key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		ft_strlcpy(new->key, str, ft_strlen(str) + 1);
		new->val = "";
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		handle_is_equal2(str, new, tmp);
}

//기능: env를 문자열 오름차순으로 출력, 리턴: void
void	print_export(void)
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
}

int	ft_export(t_parser *curr_parser)
{
	/* TODO
		1 export만 썼을 때
			- declare -x 환경변수들
			- 기존에 존재하는 환경변수들 정렬
			- 새로 추가되는 환경변수는 기존아래에 추가
			- 새로 추가된 환경변수에서 또 새로추가시 정렬 
				ex) a=a
					b=b 에서 ab=ab추가하면 a=a b=b사이에 들어감
		2 export a -> a 이건 빼자;
		3 export a="hello" or a=hello
		4 export a=a b=b c=c ...
		5 export aa=aa bb = bb -> aa=aa, bb 들어가고 
			bash: export: `=': not a valid identifier
		6 export a= -> a="" 
		7 export는 pipe로 아무것도 안넘어가는듯?
	 */
	t_lexer	*curr_lexer;

	curr_lexer = curr_parser->start->next;
	if (curr_parser->start->next == NULL)
		print_export();
	else
	{
		while (curr_lexer != 0)
		{
			if (!count_equal(curr_lexer->str))
				handle_is_not_equal(curr_lexer->str);
			else
			{
				handle_is_equal(curr_lexer->str, g_uni.env_list);
			}
			curr_lexer = curr_lexer->next;
		}
	}
	return (0);
}