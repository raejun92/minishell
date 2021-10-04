#include "minishell.h"

t_lexer	*delete_red(t_parser *curr_parser, t_lexer *curr_lexer)
{
	t_lexer	*temp;

	temp = 0;
	if (curr_parser->start == curr_lexer)
	{
		if (g_uni.lexer_list == curr_lexer)
			g_uni.lexer_list = curr_lexer->next->next;
		if (curr_parser->end != curr_lexer->next->next)
			curr_parser->start = curr_lexer->next->next;
		else
			curr_parser->start = 0;
	}
	else
	{
		temp = curr_parser->start;
		while (temp->next != curr_lexer)
			temp = temp->next;
		temp->next = curr_lexer->next->next;
	}
	if (curr_parser->end == curr_lexer->next->next && temp == 0)
		curr_parser->end = 0;
	else if (curr_parser->end == curr_lexer->next->next)
		curr_parser->end = temp->next;
	temp = curr_lexer->next->next;
	free(curr_lexer->next->str);
	free(curr_lexer->next);
	free(curr_lexer->str);
	free(curr_lexer);
	return (temp);
}

int	handle_input(t_parser *curr_parser, t_lexer *curr_lexer)
{
	int	fd;

	fd = open(curr_lexer->next->str, O_RDONLY);
	if (fd == -1)
	{
		ft_print_error(2, 0, curr_lexer->next->str, \
		strerror(errno));
		return (1);
	}
	if (curr_parser->fd_in != 0)
		close(curr_parser->fd_in);
	curr_parser->fd_in = fd;
	return (0);
}

int	handle_output(t_parser *curr_parser, t_lexer *curr_lexer, int mode)
{
	int	fd;

	if (mode == 1)
		fd = open(curr_lexer->next->str, O_WRONLY | O_APPEND | O_CREAT, 00644);
	else
		fd = open(curr_lexer->next->str, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
	{
		ft_print_error(2, 0, curr_lexer->next->str, \
		strerror(errno));
		return (1);
	}
	if (curr_parser->fd_out != 1)
		close(curr_parser->fd_out);
	curr_parser->fd_out = fd;
	return (0);
}

int	handle_heredoc(t_parser *curr_parser, t_lexer *curr_lexer)
{
	char		*input;
	t_parser	*new;

	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, curr_lexer->next->str) == 0)
			break ;
		write(curr_parser->pipe[1], input, ft_strlen(input));
		write(curr_parser->pipe[1], "\n", 1);
		free(input);
	}
	free(input);
	delete_red(curr_parser, curr_lexer);
	new = new_parser();
	new->start = curr_parser->start;
	new->end = curr_parser->end;
	new->next = curr_parser->next;
	new->fd_in = curr_parser->fd_in;
	new->fd_out = curr_parser->fd_out;
	curr_parser->next = new;
	return (2);
}

int	ft_check_red(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;
	int		ret;

	curr_lexer = curr_parser->start;
	ret = 0;
	while (curr_lexer != curr_parser->end)
	{
		if (curr_lexer->type == RED)
		{
			if (ft_strcmp(curr_lexer->str, "<") == 0)
				ret = handle_input(curr_parser, curr_lexer);
			else if (ft_strcmp(curr_lexer->str, ">") == 0)
				ret = handle_output(curr_parser, curr_lexer, 0);
			else if (ft_strcmp(curr_lexer->str, ">>") == 0)
				ret = handle_output(curr_parser, curr_lexer, 1);
			else if (ft_strcmp(curr_lexer->str, "<<") == 0)
				return (handle_heredoc(curr_parser, curr_lexer));
			if (ret != 0)
				return (0);
			curr_lexer = delete_red(curr_parser, curr_lexer);
		}
		else
			curr_lexer = curr_lexer->next;
	}
	return (1);
}
