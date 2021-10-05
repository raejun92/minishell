/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suko <suko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:55:48 by suko              #+#    #+#             */
/*   Updated: 2021/10/05 19:56:57 by suko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	input_env_check(t_env *tmp, char *min)
{
	while (tmp != 0)
	{
		if (tmp->key == min)
			tmp->check = 1;
		tmp = tmp->next;
	}
}

int	print_export(t_parser *curr_parser)
{
	t_env	*tmp;
	t_env	*min;
	char	*max;
	int		fd;

	if (curr_parser->fd_out > 2)
		fd = curr_parser->fd_out;
	else
		fd = 1;
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
		util_export(min, fd);
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
	if (curr_parser->start->next == curr_parser->end)
		ret = print_export(curr_parser);
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
