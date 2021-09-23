#include "minishell.h"

// 기능: pwd 출력, 리턴: void
int	print_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_print_error(g_uni.err_pipe[1], "pwd", 0, \
	strerror(errno));
		return (1);
	}
	printf("%s\n", path);
	free(path);
	path = 0;
	return (0);
}
