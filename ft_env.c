#include "minishell.h"

t_env	*new_env(t_env *env)
{
	env = (t_env *)malloc(sizeof(t_env) * 1);
	env->key = NULL;
	env->val = NULL;
	env->next = NULL;
	return (env);
}

t_env	*get_env(char *key)
{
	t_env	*curr;

	curr = g_uni.env_list;
	while (curr != 0)
	{
		if (ft_strcmp(curr->key, key))
			return (curr);
		curr = curr->next;
	}
	return (0);
}

void	set_env(t_env *env, char *envp)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (envp[i] != '\0')
	{
		if (envp[i] == '=')
		{
			env->key = (char *)malloc(sizeof(char) * (i + 1));
			ft_strlcpy(env->key, envp, i+1);
			tmp = i + 1;
		}
		i++;
	}
	env->val = (char *)malloc(sizeof(char) * (i - tmp + 1));
	ft_strlcpy(env->val, &envp[tmp], (i - tmp + 1));
}

void	save_env_variable(char **envp)
{
	t_env	*env;
	t_env	*temp;

	while (*envp != 0){
		env = new_env(env);
		set_env(env, *envp);
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

int	print_envp(void)
{
	t_env	*tmp;

	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		printf("%s=%s\n", tmp->key, tmp->val);
		tmp = tmp->next;
	}
	return (0);
}
