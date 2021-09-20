#include "minishell.h"

int	print_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	printf("%s\n", path);
	free(path);
	path = 0;
	return (0);
}
