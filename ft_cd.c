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

static int	handle_absolute(t_lexer *curr_lexer, char *path)
{
	if (chdir(path) == -1)
	{
		ft_print_error(2, "cd", curr_lexer->str, \
	strerror(errno));
		return (1);
	}
	set_pwd("PWD");
	return (0);
}

static int	handle_relative(t_lexer *curr_lexer)
{
	char	*curr_path;
	char	*new_path;
	int		ret;

	curr_path = getcwd(NULL, 0);
	if (!curr_path)
	{
		ft_print_error(2, "cd", 0, \
	strerror(errno));
		return (1);
	}
	new_path = concat_path(curr_path, curr_lexer->str);
	if (!new_path)
	{
		free(curr_path);
		return (1);
	}
	ret = handle_absolute(curr_lexer, new_path);
	free(curr_path);
	free(new_path);
	return (ret);
}

static int	handle_home(t_parser *curr_parser, t_lexer *curr_lexer)
{
	char	*home_path;
	int		ret;

	if (curr_lexer == curr_parser->end)
		home_path = concat_path(get_env("HOME")->val, "");
	else
		home_path = concat_path(get_env("HOME")->val, \
		&curr_lexer->str[1]);
	ret = handle_absolute(curr_lexer, home_path);
	free(home_path);
	return (ret);
}

int	ft_cd(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;

	curr_lexer = curr_parser->start;
	set_pwd("OLDPWD");
	if (curr_lexer->next == curr_parser->end || \
		(curr_lexer->next->str[0] == '~' && \
		(curr_lexer->next->str[1] == '\0' || curr_lexer->next->str[1] == '/')))
		return (handle_home(curr_parser, curr_lexer->next));
	while (curr_lexer->next != 0)
	{
		if (curr_lexer->type != CMD)
			break ;
		curr_lexer = curr_lexer->next;
	}
	if ((curr_lexer->str)[0] == '/')
		return (handle_absolute(curr_lexer, curr_lexer->str));
	else
		return (handle_relative(curr_lexer));
}
