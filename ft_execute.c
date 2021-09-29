#include "minishell.h"

int	execute_parser(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;
	int		ret;

	curr_lexer = curr_parser->start;
	ret = ft_execute_builtin(curr_parser);
	if (ret != -1)
		return (ret);
	ret = execve(get_file(curr_lexer->str), get_argv(curr_lexer), get_envp());
	if (ret == -1)
		return (1);
	return (0);
}

void	handle_child(t_parser *curr_parser, int prev_in)
{
	int	ret;

	if (curr_parser->next == 0 && ft_is_builtin(curr_parser) && \
	g_uni.parser_list->start == curr_parser->start)
		ret = 0;
	else
	{
		if (curr_parser->fd_in > 2)
			dup2(curr_parser->fd_in, 0);
		else if (prev_in > 0)
			dup2(prev_in, 0);
		if (prev_in > 0)
			close(prev_in);
		if (curr_parser->fd_out < 2 && curr_parser->next != 0)
			dup2(curr_parser->pipe[1], 1);
		else if (curr_parser->fd_out > 2)
			dup2(curr_parser->fd_out, 1);
		ret = execute_parser(curr_parser);
	}
	exit(ret);
}

void	handle_parent(t_parser *curr_parser, int *prev_in, \
int wait)
{
	int			child_stat;

	if (wait)
	{
		if (curr_parser->next == 0 && ft_is_builtin(curr_parser) && \
		g_uni.parser_list->start == curr_parser->start)
		{
			child_stat = ft_execute_builtin(curr_parser);
			g_uni.exit_status = child_stat;
		}
		return ;
	}
	close(curr_parser->pipe[1]);
	*prev_in = curr_parser->pipe[0];
	if (curr_parser->fd_in > 2)
		close(curr_parser->fd_in);
	if (curr_parser->fd_out > 2)
		close(curr_parser->fd_out);
}

void	handle_remain(void)
{
	t_parser	*curr_parser;
	int			child_stat;

	curr_parser = g_uni.parser_list;
	while (curr_parser != 0)
	{
		if (curr_parser->pid != 0)
		{
			waitpid(curr_parser->pid, &child_stat, WUNTRACED);
			if (curr_parser->next == 0 && !(ft_is_builtin(curr_parser) && \
				g_uni.parser_list->start == curr_parser->start))
			{
				if (WIFSTOPPED(child_stat))
					g_uni.exit_status = 146;
				else if (WIFEXITED(child_stat))
					g_uni.exit_status = WEXITSTATUS(child_stat);
			}
		}
		curr_parser = curr_parser->next;
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
		if (pipe(curr_parser->pipe) != 0) // 파이프가 있을 때만 만들어야 할듯
			return (ft_error(0));
		if (ft_check_red(curr_parser) == 1)
		{
			curr_pid = fork();
			if (curr_pid < 0)
				return (ft_error(0));
			if (curr_pid == 0)
				handle_child(curr_parser, prev_in);
			curr_parser->pid = curr_pid;
			handle_parent(curr_parser, &prev_in, 1);
		}
		handle_parent(curr_parser, &prev_in, 0);
		curr_parser = curr_parser->next;
	}
	handle_remain();
}
