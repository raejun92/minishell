/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suko <suko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:56:33 by suko              #+#    #+#             */
/*   Updated: 2021/10/05 19:56:57 by suko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_valid(char *str)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(str[i]) || str[i] == '_'))
		return (1);
	while (str[++i] != '\0')
	{
		if (!(ft_isalpha(str[i]) || str[i] == '_' || ft_isdigit(str[i])))
			return (1);
	}
	return (0);
}

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
	t_lexer	*curr_lexer;

	curr_lexer = parser->start->next;
	while (curr_lexer != parser->end)
	{
		if (check_unset_valid(curr_lexer->str))
		{
			printf("bash: unset: `%s': not a valid identifier\n", \
			curr_lexer->str);
			return (1);
		}
		else
			remove_env(curr_lexer->str);
		curr_lexer = curr_lexer->next;
	}
	return (0);
}
