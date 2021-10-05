#include "minishell.h"

int	check_format(struct stat sb, t_lexer *curr_lexer)
{
	if ((sb.st_mode & S_IFMT) != S_IFREG)
	{
		if ((sb.st_mode & S_IFMT) == S_IFBLK)
			ft_print_error(2, 0, curr_lexer->str, "is a block device");
		else if ((sb.st_mode & S_IFMT) == S_IFSOCK)
			ft_print_error(2, 0, curr_lexer->str, "is a socket");
		else if ((sb.st_mode & S_IFMT) == S_IFLNK)
			ft_print_error(2, 0, curr_lexer->str, "is a symbolic link");
		else if ((sb.st_mode & S_IFMT) == S_IFDIR)
			ft_print_error(2, 0, curr_lexer->str, "is a directory");
		else if ((sb.st_mode & S_IFMT) == S_IFCHR)
			ft_print_error(2, 0, curr_lexer->str, "is a character device");
		else if ((sb.st_mode & S_IFMT) == S_IFIFO)
			ft_print_error(2, 0, curr_lexer->str, "is a FIFO/pipe");
		return (126);
	}
	return (0);
}

int	ft_check_stat(t_parser *curr_parser)
{
	t_lexer			*curr_lexer;
	struct stat		sb;

	curr_lexer = curr_parser->start;
	if (stat(get_file(curr_lexer->str), &sb) == -1)
	{
		if (errno == ENOENT && !is_contain(get_file(curr_lexer->str), '/'))
		{
			ft_print_error(2, curr_lexer->str, 0, "command not found");
			return (127);
		}
		ft_print_error(2, curr_lexer->str, 0, strerror(errno));
		if (errno == EFAULT)
			return (126);
		else
			return (127);
	}
	if ((sb.st_mode & S_IXUSR) == 0 && curr_lexer->str[0] == '.')
	{
		ft_print_error(2, curr_lexer->str, 0, "Permission denied");
		return (126);
	}
	return (check_format(sb, curr_lexer));
}
