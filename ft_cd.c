#include "minishell.h"

char	*concat_path(char *curr_path, char *rel_path)
{
	char	*new_path;
	int		i;
	int		j;

	new_path = malloc(sizeof(char) * (ft_strlen(curr_path) + 1 + \
	ft_strlen(rel_path) + 1));
	if (new_path == 0)
	{
		ft_error(0);
		return (0);
	}
	i = -1;
	while (curr_path[++i] != '\0')
		new_path[i] = curr_path[i];
	new_path[i] = '/';
	j = -1;
	while (rel_path[++j] != '\0')
		new_path[++i] = rel_path[j];
	new_path[++i] = '\0';
	return (new_path);
}

static int	handle_relative(t_lexer *curr_lexer)
{
	char	*curr_path;
	char	*new_path;
	int		i;

	curr_path = getcwd(NULL, 0);
	if (!curr_path)
	{
		ft_print_error(g_uni.err_pipe[1], "cd", 0, \
	strerror(errno));
		return (1);
	}
	new_path = concat_path(curr_path, curr_lexer->str);
	if (!new_path)
		return (1);
	if (chdir(new_path) == -1)
	{
		ft_print_error(g_uni.err_pipe[1], "cd", 0, \
	strerror(errno));
		return (1);
	}
	free(curr_path);
	free(new_path);
	return (0);
}

static int	handle_absolute(t_lexer *curr_lexer)
{
	if (chdir(curr_lexer->str) == -1)
	{
		ft_print_error(g_uni.err_pipe[1], "cd", 0, \
	strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_cd(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;
	char	*path;

	curr_lexer = curr_parser->start;
	while (curr_lexer->next != 0)
	{
		if (curr_lexer->type != CMD)
			break ;
		curr_lexer = curr_lexer->next;
	}
	if (curr_lexer->next != 0)
	{
		ft_print_error(g_uni.err_pipe[1], "cd", 0, \
		"too many arguments");
		return (1);
	}
	if ((curr_lexer->str)[0] == '/')
		return (handle_absolute(curr_lexer));
	else
		return (handle_relative(curr_lexer));
}
