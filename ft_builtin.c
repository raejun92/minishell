#include "minishell.h"

int	ft_execute_builtin(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;
	int		ret;

	curr_lexer = curr_parser->start;
	while (curr_lexer != 0 && curr_lexer->type != CMD)
		curr_lexer = curr_lexer->next;
	if (curr_lexer == 0)
		return (0);
	if (ft_strcmp(curr_lexer->str, "echo"))
		ret = ft_echo(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "cd"))
		ret = ft_echo(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "pwd"))
		ret = print_pwd();
	else if (ft_strcmp(curr_lexer->str, "export"))
		ret = ft_echo(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "unset"))
		ret = ft_echo(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "env"))
		ret = print_envp();
	else if (ft_strcmp(curr_lexer->str, "exit"))
		ret = ft_exit(curr_parser);
	else
		return (-1);
	return (ret);
}

int	ft_is_builtin(t_parser *curr_parser)
{
	t_lexer	*curr_lexer;
	int		ret;

	curr_lexer = curr_parser->start;
	while (curr_lexer != 0 && curr_lexer->type != CMD)
		curr_lexer = curr_lexer->next;
	if (curr_lexer == 0)
		return (1);
	if (ft_strcmp(curr_lexer->str, "echo"))
		return (1);
	else if (ft_strcmp(curr_lexer->str, "cd"))
		return (1);
	else if (ft_strcmp(curr_lexer->str, "pwd"))
		return (1);
	else if (ft_strcmp(curr_lexer->str, "export"))
		return (1);
	else if (ft_strcmp(curr_lexer->str, "unset"))
		return (1);
	else if (ft_strcmp(curr_lexer->str, "env"))
		return (1);
	else if (ft_strcmp(curr_lexer->str, "exit"))
		return (1);
	else
		return (0);
}
