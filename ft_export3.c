#include "minishell.h"

static void	handle_is_equal2(char *str, t_env *new, t_env *tmp)
{
	new = new_env();
	save_env_variable(new, str);
	if (check_export_key(new->key))
	{
		tmp = get_env(new->key);
		if (tmp->val != 0)
			free(tmp->val);
		tmp->val = malloc(sizeof(char) * (ft_strlen(new->val) + 1));
		ft_strlcpy(tmp->val, new->val, ft_strlen(new->val) + 1);
		free(new->key);
		if (new->val != 0)
			free(new->val);
		free(new);
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_is_equal(char *str, t_env *tmp)
{
	t_env	*new;

	if (check_export_valid(str) || str[0] == '=')
		printf("bash: export: `%s': not a valid identifier\n", str);
	else if (count_equal(str) == 1 && str[ft_strlen(str) - 1] == '=')
	{
		str[ft_strlen(str) - 1] = '\0';
		if (check_export_key(str))
		{
			tmp = get_env(str);
			free(tmp->val);
			tmp->val = malloc(sizeof(char));
			tmp->val[0] = '\0';
			return ;
		}
		new = new_env();
		new->key = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
		ft_strlcpy(new->key, str, ft_strlen(str) + 1);
		new->val = malloc(sizeof(char));
		new->val[0] = '\0';
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		handle_is_equal2(str, new, tmp);
}