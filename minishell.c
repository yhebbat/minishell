#include "minishell.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_deltop(t_headers *head)
{
	t_env	*to_delete;
	t_env	*stack;

	if (head != NULL && head->env_h != NULL)
	{
		to_delete = head->env_h;
		if (!to_delete->suivant)
		{
			free(to_delete->val);
			free(to_delete->var);
			free(to_delete);
			head->env_h = NULL;
			head->env_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->suivant;
			head->env_h = stack;
			stack->preced = NULL;
			free(to_delete->val);
			free(to_delete->var);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

char	*add_str(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i])
		i++;
	res = malloc(sizeof(char) * i + 1);
	i = 0;
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	ft_addtop(t_headers *head, char *var, char *val)
{
	t_env	*stack;
	t_env	*to_add;

	to_add = malloc(sizeof(t_env));
	if (!to_add)
		exit(0);
	if (head->env_h == NULL)
	{
		to_add->var = add_str(var);
		to_add->val = add_str(val);
		to_add->suivant = NULL;
		to_add->preced = NULL;
		head->env_f = to_add;
		head->env_h = to_add;
	}
	else
	{
		stack = head->env_h;
		to_add->var = add_str(var);
		to_add->val = add_str(val);
		to_add->suivant = stack;
		to_add->preced = NULL;
		stack->preced = to_add;
		head->env_h = to_add;
	}
}

void	parse(char *line, t_headers *header)
{
	char	**str;
	check_error(line);
	str = split_pipe(line, header);
	save_cmd(header, str);
    ft_free(str);
}

int	main(int ac, char **av, char **env)
{
	t_headers	*header;
	char		*line;
	(void)		ac;
	(void)		av;
	int			k;

	k = 1;
	line = NULL;
	header = malloc(sizeof(t_headers));
	header->env_h = NULL;
	header->env_f = NULL;
	header->cmd_h = NULL;
	envi(env, header);
	while (k)
	{
		line = readline("minishell🔥\%");
		if (!line)
			break;
		parse(line, header);
		add_history(line);
		if (!strcmp(line, "exit"))
		{
			k = 0;
			free(line);
		}
		else
			free(line);
	}
	while (header->env_h)
		ft_delbottom(header);
	free(header);
	header = NULL;
	// system("leaks minishell");
}