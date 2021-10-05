/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suko <suko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:56:11 by suko              #+#    #+#             */
/*   Updated: 2021/10/05 19:56:57 by suko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_print_error(2, "pwd", 0, \
	strerror(errno));
		return (1);
	}
	printf("%s\n", path);
	free(path);
	path = 0;
	return (0);
}

void	set_pwd(char *type)
{
	t_env	*new;
	t_env	*tmp;
	char	*path;

	path = getcwd(NULL, 0);
	tmp = g_uni.env_list;
	if (check_export_key(type))
	{
		new = get_env(type);
		free(new->val);
		new->val = ft_strdup(path);
		free(path);
	}
	else
	{
		new = new_env();
		new->key = ft_strdup(type);
		new->val = ft_strdup(path);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		free(path);
	}
}
