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
	if (ft_strcmp(curr_lexer->str, "echo") == 0)
		ret = ft_echo(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "cd") == 0)
		ret = ft_cd(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "pwd") == 0)
		ret = print_pwd();
	else if (ft_strcmp(curr_lexer->str, "export") == 0)
		ret = ft_export(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "unset") == 0)
		ret = ft_unset(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "env") == 0)
		ret = print_envp(curr_parser);
	else if (ft_strcmp(curr_lexer->str, "exit") == 0)
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
	if (ft_strcmp(curr_lexer->str, "echo") == 0)
		return (1);
	else if (ft_strcmp(curr_lexer->str, "cd") == 0)
		return (1);
	else if (ft_strcmp(curr_lexer->str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(curr_lexer->str, "export") == 0)
		return (1);
	else if (ft_strcmp(curr_lexer->str, "unset") == 0)
		return (1);
	else if (ft_strcmp(curr_lexer->str, "env") == 0)
		return (1);
	else if (ft_strcmp(curr_lexer->str, "exit") == 0)
		return (1);
	else
		return (0);
}
