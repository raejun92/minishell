/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suko <suko@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 19:56:16 by suko              #+#    #+#             */
/*   Updated: 2021/10/14 15:56:36 by suko             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(void)
{
	t_parser	*curr_parser;

	curr_parser = g_uni.parser_list;
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGINT);
		curr_parser = curr_parser->next;
	}
	rl_replace_line("", 0);
	printf("\n");
	if (g_uni.parser_list == 0)
		rl_on_new_line();
	rl_redisplay();
}

void	sigquit_handler(void)
{
	t_parser	*curr_parser;

	curr_parser = g_uni.parser_list;
	if (g_uni.parser_list == 0)
	{
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
			kill(curr_parser->pid, SIGQUIT);
		curr_parser = curr_parser->next;
	}
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(int signum)
{
	if (signum == SIGINT)
		sigint_handler();
	else if (signum == SIGQUIT)
		sigquit_handler();
}
