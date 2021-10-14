/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suko <suko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:56:00 by suko              #+#    #+#             */
/*   Updated: 2021/10/14 13:20:49 by suko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_delimiter(char c, int i)
{
	if (c == '>' || c == '<' || c == '|' || c == ' ' || \
	c == '\'' || c == '"' || c == '$' || c == '?' || c == '=' || \
	c == '/' || (i == 1 && c >= '0' && c <= '9'))
		return (1);
	else
		return (0);
}

static char	*get_exit_status(void)
{
	char	*val;
	int		len;
	int		num;

	val = malloc(sizeof(char) * 4);
	num = g_uni.exit_status;
	if (num >= 100)
		len = 3;
	else if (num >= 10)
		len = 2;
	else
		len = 1;
	val[len] = '\0';
	while (--len >= 0)
	{
		val[len] = num % 10 + '0';
		num /= 10;
	}
	return (val);
}

static char	*get_val(char *input, int start, int end)
{
	char	*key;
	int		i;
	t_env	*curr_env;

	if (start < 0)
		return (0);
	i = -1;
	if (start == end - 1 && input[end] == '?')
		return (get_exit_status());
	key = malloc(sizeof(char) * (end - start + 1));
	while (++i < end - start)
		key[i] = input[start + i + 1];
	key[i] = '\0';
	curr_env = get_env(key);
	free(key);
	if (curr_env == 0)
		return (0);
	else
		return (curr_env->val);
}

int	count_dollar(char *input, int start, int end, int count)
{
	int		i;
	int		dollar;

	dollar = -1;
	i = start - 1;
	while (++i <= end)
	{
		if (is_delimiter(input[i], i - dollar))
		{
			if (dollar >= 0 && dollar != i - 1)
				count += ft_strlen(get_val(input, dollar, i - 1)) - i + dollar;
			else if (dollar >= 0 && input[i] == '?' && g_uni.exit_status >= 100)
				count += 1;
			else if (dollar >= 0 && input[i] == '?' && g_uni.exit_status < 10)
				count -= 1;
			else if (dollar >= 0 && input[i] >= '0' && input[i] <= '9')
				count += ft_strlen(get_val(input, dollar, i)) - i + dollar - 1;
			dollar = -1;
			if (input[i] == '$')
				dollar = i;
		}
	}
	if (dollar >= 0 && dollar != i - 1)
		count += ft_strlen(get_val(input, dollar, i - 1)) - i + dollar;
	return (count);
}

void	ft_handle_dollar(char *out, char *in, int *out_idx, int *in_idx)
{
	int		i;
	int		j;
	char	*val;

	i = *in_idx + 1;
	while (in[i] != '\0' && !is_delimiter(in[i], i - *in_idx))
		i++;
	if (*in_idx == i - 1 && (in[i] == '?' || (in[i] >= '0' && in[i] <= '9')))
		val = get_val(in, *in_idx, i);
	else if (*in_idx == i - 1)
		val = ft_strdup("$");
	else
		val = get_val(in, *in_idx, i - 1);
	j = -1;
	while (++j < (int)ft_strlen(val))
		out[j + *out_idx] = val[j];
	if (*in_idx == i - 1 && (in[i] == '?' || (in[i] >= '0' && in[i] <= '9')))
	{
		if (in[i] == '?')
			free(val);
		*in_idx = i;
	}
	else
		*in_idx = i - 1;
	*out_idx = *out_idx + j - 1;
}
