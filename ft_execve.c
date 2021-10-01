#include "minishell.h"

// 기능: path경로에 +/ +cmd, 리턴: char*(path/cmd)
static char *join_cmd(char *path, char *cmd)
{
	char	*path_tmp;
	char	*cmd_tmp;
	char	*rst;
	int		i;

	path_tmp = malloc(sizeof(char) * (ft_strlen(path) + 2));
	cmd_tmp = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	i = -1;
	while (path[++i] != '\0')
		path_tmp[i] = path[i];
	path_tmp[i] = '/';
	path_tmp[i + 1] = '\0';
	i = -1;
	while (cmd[++i] != '\0')
		cmd_tmp[i] = cmd[i];
	cmd_tmp[i] = '\0';
	rst = ft_strjoin(path_tmp, cmd_tmp);
	return (rst);
}

// 기능: 명령어가 존재하는 파일 위치를 찾아서 반환, 리턴: char*(명령어 파일위치 or 명령어)
char *get_file(char *cmd)
{
	t_env		*env_path;
	char		**path;
	char		**path_tmp;
	char		*path_cmd;
	struct stat	s_stat;

	if (is_contain(cmd, '/'))
		return cmd;
	env_path = get_env("PATH");
	path = ft_split(env_path->val, ':');
	path_tmp = path;
	while (*path != 0)
	{
		path_cmd = join_cmd(*path, cmd);
		if (stat(path_cmd, &s_stat) != -1) {
			free_double_pointer(path_tmp);
			return (path_cmd);
		}
		path++;
	}
	free_double_pointer(path_tmp);
	free(path_cmd);
	path_cmd = 0;
	return (cmd);
}

// 기능: 입력한 명령어를 char **로 변환, 리턴: char**(입력 명령어)
char **get_argv(t_lexer *curr_lexer, t_lexer *end_lexer, int i)
{
	char	**str;
	t_lexer	*tmp;
	int		cnt;

	tmp = curr_lexer;
	cnt = 0;
	while (tmp != 0)
	{
		cnt++;
		tmp = tmp->next;
	}
	str = malloc(sizeof(char *) * (cnt + 1));
	tmp = curr_lexer;
	while (tmp != end_lexer)
	{
		str[i] = malloc(sizeof(char) * (ft_strlen(tmp->str) + 1));
		ft_strlcpy(str[i], tmp->str, ft_strlen(tmp->str) + 1);
		i++;
		tmp = tmp->next;
	}
	str[i] = NULL;
	return (str);
}

static void	combine_key_val(char **envp, char *key, char *val)
{
	char	*key_tmp;
	char	*val_tmp;
	int		i;

	key_tmp = malloc(sizeof(char) * (ft_strlen(key) + 2));
	i = -1;
	while (key[++i] != '\0')
		key_tmp[i] = key[i];
	key_tmp[i] = '=';
	key_tmp[i + 1] = '\0';
	val_tmp = malloc(sizeof(char) * (ft_strlen(val) + 1));
	ft_strlcpy(val_tmp, val, ft_strlen(val) + 1);
	*envp = ft_strjoin(key_tmp, val_tmp);
}

// 기능: env_list를 원래의 envp형태로 변환, 리턴: char**(env_list)
char	**get_envp(void)
{
	t_env	*tmp;
	char	**envp;
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		cnt++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (cnt + 1));
	tmp = g_uni.env_list;
	while (tmp != 0)
	{
		combine_key_val(&envp[i], tmp->key, tmp->val);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
