#include "minishell.h"

// 기능: 문자열 처음에 알파벳 또는 '_'인지 확인하고 문자열중 알파벳, 숫자, '_'인지 확인, 리턴: int(알파벳 또는 _ 아니면 1, 맞으면 0)
int	check_unset_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_')) // 숫자는 처음에 못들어옴
			return (1);
	while (str[++i] != '\0')
	{
		if (!(ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i]))) // 처음 이후 숫자 가능
			return (1);
	}
	return (0);
}

//기능: 환경변수 제거, 리턴: void
void	remove_env(char *str)
{
	t_env	*curr_env;
	t_env	*tmp;
	t_env	*prev_env;

	curr_env = g_uni.env_list;
	while (curr_env != 0)
	{
		if (ft_strcmp(curr_env->key, str) == 0)
		{
			tmp = curr_env;
			prev_env->next = curr_env->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
			tmp = 0;
		}
		prev_env = curr_env;
		curr_env = curr_env->next;
	}
}

int	ft_unset(t_parser *parser)
{
	/* TODO 
	unset aa=aa -> bash: unset: `aa=aa': not a valid identifier
	unset aa -> o
	unset aa bb -> o
	unset a= -> bash: unset: `a=': not a valid identifier
	 */
	t_lexer *curr_lexer;

	curr_lexer = parser->start->next;
	while (curr_lexer != 0)
	{
		if (check_unset_valid(curr_lexer->str))
			printf("bash: unset: %s: not a valid identifier\n", \
			curr_lexer->str);
		else
			remove_env(curr_lexer->str);
		curr_lexer = curr_lexer->next;
	}
	return (0);
}