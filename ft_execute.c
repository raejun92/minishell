#include "minishell.h"

int	execute_parser(t_parser *curr_parser)
{
	int	ret;

	ret = ft_execute_builtin(curr_parser);
	if (ret != -1)
		return (ret);
	// execve ->
	return (0);
}

void	handle_child(t_parser *curr_parser, int prev_in)
{
	if (curr_parser->next == 0 && ft_is_builtin(curr_parser) && \
	g_uni.parser_list->start == curr_parser->start)
		exit(7);
	if (curr_parser->fd_in > 2)
		dup2(curr_parser->fd_in, 0);
	else if (prev_in > 0)
		dup2(prev_in, 0);
	if (prev_in > 0)
		close(prev_in);
	if (curr_parser->fd_out < 2)
		dup2(curr_parser->pipe[1], 1);
	else
		dup2(curr_parser->fd_out, 1);
	exit(execute_parser(curr_parser));
}

void	handle_parent(t_parser *curr_parser, int child_pid, int *prev_in, \
int wait)
{
	int			child_stat;

	if (wait)
	{
		waitpid(child_pid, &child_stat, 0);
		if (curr_parser->next == 0 && WEXITSTATUS(child_stat) == 7 && \
		g_uni.parser_list->start == curr_parser->start)
		{
			child_stat = ft_execute_builtin(curr_parser);
			g_uni.exit_status = child_stat;
		}
		else
			g_uni.exit_status = WEXITSTATUS(child_stat);
		return ;
	}
	close(curr_parser->pipe[1]);
	*prev_in = curr_parser->pipe[0];
	if (curr_parser->fd_in > 2)
		close(curr_parser->fd_in);
	if (curr_parser->fd_out > 2)
		close(curr_parser->fd_out);
}

void	handle_remain(int prev_in)
{
	char		buffer[256];
	int			count;

	if (prev_in > 0)
	{
		count = read(prev_in, buffer, sizeof(buffer));
		close(prev_in);
		write(1, buffer, count);
	}
}

void	ft_execute(void)
{
	t_parser	*curr_parser;
	pid_t		curr_pid;
	int			prev_in;

	curr_parser = g_uni.parser_list;
	prev_in = -1;
	while (curr_parser != 0)
	{
		if (pipe(curr_parser->pipe) != 0)
			return (ft_error(0));
		if (ft_check_red(curr_parser) == 1)
		{
			curr_pid = fork();
			if (curr_pid < 0)
				return (ft_error(0));
			if (curr_pid == 0)
				handle_child(curr_parser, prev_in);
			handle_parent(curr_parser, curr_pid, &prev_in, 1);
		}
		handle_parent(curr_parser, curr_pid, &prev_in, 0);
		curr_parser = curr_parser->next;
	}
	handle_remain(prev_in);
}
