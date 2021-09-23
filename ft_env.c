#include "minishell.h"

// 기능: env 생성 및 초기화, 리턴: t_env
t_env	*new_env(void)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = NULL;
	env->val = NULL;
	env->next = NULL;
	env->check = 0;
	return (env);
}

t_env	*get_env(char *key)
{
	t_env	*curr;

	curr = g_uni.env_list;
	while (curr != 0)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (0);
}

// 기능: 환경변수의 key, value 저장, 리턴: void
void	save_env_variable(t_env *env, char *envp)
{
	int	i;
	int	tmp;
	int	cnt;

	i = 0;
	tmp = 0;
	cnt = 0;
	while (envp[i] != '\0')
	{
		if (envp[i] == '=' && cnt == 0) // a=a=a에서 앞의 =에서 잘라주기 위해 cnt추가
		{
			env->key = (char *)malloc(sizeof(char) * (i + 1));
			ft_strlcpy(env->key, envp, i + 1);
			tmp = i + 1;
			cnt++;
		}
		i++;
	}
	env->val = (char *)malloc(sizeof(char) * (i - tmp + 1));
	ft_strlcpy(env->val, &envp[tmp], (i - tmp + 1));
}

// 기능: 환경변수를 받아와 env_list 구성, 리턴: void
void	ft_env(char **envp)
{
	t_env	*env;
	t_env	*temp;

	while (*envp != 0)
	{
		env = new_env();
		save_env_variable(env, *envp);
		if (g_uni.env_list == NULL)
			g_uni.env_list = env;
		else
		{
			temp = g_uni.env_list;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = env;
		}
		envp++;
	}
}

// 기능: envp 출력, 리턴: void
int	print_envp(t_parser *parser)
{
	t_env	*tmp;

	if (parser->start->next != NULL)
	{
		printf("env: %s: No such file or directory\n", \
		parser->start->next->str);
		return (127);
	}
	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		if (tmp->val != NULL)
			printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}