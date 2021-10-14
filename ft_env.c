/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suko <suko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:55:27 by suko              #+#    #+#             */
/*   Updated: 2021/10/14 13:43:00 by suko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(void)
{
	t_env	*env;

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
		if (envp[i] == '=' && cnt == 0)
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
	handle_is_not_equal("OLDPWD");
}

int	print_env(t_parser *parser)
{
	t_env	*tmp;

	if (parser->start->next != parser->end)
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
