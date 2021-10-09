#include "minishell.h"

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	*ft_freee(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (0);
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

void	ft_delbottom(t_headers *head)
{
	t_env	*to_delete;
	t_env	*stack;

	if (head != NULL && head->env_h != NULL)
	{
		to_delete = head->env_f;
		if (!to_delete->preced)
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
			stack = to_delete->preced;
			head->env_f = stack;
			stack->suivant = NULL;
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

void	ft_addbottom(t_headers *head, char *var, char *val)
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
		stack = head->env_f;
		to_add->var = add_str(var);
		to_add->val = add_str(val);
		to_add->preced = stack;
		to_add->suivant = NULL;
		stack->suivant = to_add;
		head->env_f = to_add;
	}
}

void	from_tab_to_ll(char **env, t_headers *header)
{
	int i;
	char **str;

	i = 0;
	while(env[i])
	{
		str = ft_split(env[i], '=');
		ft_addbottom(header, str[0], str[1]);
		ft_freee(str);
		i++;
	}
}

// char	**env_from_ll_to_tab(t_henv *henv)
// {
// 	int i;
// 	t_env *nb;
// 	int k;
// 	int r;
// 	char **str;

// 	k = 0;
// 	i = 0;
// 	nb = henv->env_h;
// 	while (nb)
// 	{
// 		i++;
// 		nb = nb->suivant;
// 	}
// 	str = malloc(sizeof(char) * i + 1);
// 	nb = henv->header;
// 	while(nb)
// 	{
// 		k = 0;
// 		while (nb->val[k])
// 			k++;
// 		while (nb->var[])
// 		nb = nb->suivant;
// 	}
// 	i = 0;
// 	// while(env[i])
// 	// {
// 	// 	str = ft_split(env[i], '=');
// 	// 	ft_addbottom(henv, str[0], str[1]);
// 	// 	ft_freee(str, ft_mots(env[i], '=') + 1);
// 	// 	i++;
// 	// }
// 	return (str);
// }

void	envi(char **env, t_headers *header)
{
	// t_env		*new_env;

	// new_env = NULL;
	from_tab_to_ll(env, header);
	// new_env = header->env_h;
	// while (new_env)
	// {
	// 	printf("%s = %s\n", new_env->var, new_env->val);
	// 	new_env = new_env->suivant;
	// }
	// while (header->env_h)
	// 	ft_delbottom(header);
}

char	**flex(char *line, t_headers *header)
{
	(void)header;
	char	**test;
    int     i = 0;

    test = ft_toke(line, '|');
    while (test[i])
    {
        printf("%s\n", test[i]);
        i++;
    }
	return (test);
    // ft_freee(test);
}

void	nb_of_quotes(char *line)
{
	int i;
	int	d_q;
	int	s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			d_q = 1;
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] == '"')
			{
				d_q = 0;
				i++;
			}
		}
		else if (line[i] == '\'')
		{
			s_q = 1;
			i++;
			while (line[i] && line[i] != '\'')
				i++;
			if (line[i] == '\'')
			{
				s_q = 0;
				i++;
			}
		}
		else
			i++;
	}
	if (s_q || d_q)
	{
		free(line);
		printf("syntax error in quotes\n");
		exit(0);
	}
}

void	check_error_pipes(char *line)
{
	int i;

	i = 0;
	if (line[0] == '|')
	{
		free(line);
		printf("parse error near `|'\n");
		exit(0);
	}
	while (line[i])
	{
		if ((line[i] == '|' && !line[i + 1]) || (line[i] == '|' && line[i + 1] == '|'))
		{
			free(line);
			printf("parse error near `|'\n");
			exit(0);
		}
		if ((line[i] == '<' && line[i + 1] == '|') || (line[i] == '>' && line[i + 1] == '|'))
		{
			free(line);
			printf("parse error near \"<>|\"\n");
			exit(0);
		}
		i++;
	}
}

void	check_error_redirections(char *line)
{
	int i;

	i = 0;
	// if (line[0] == '|')
	// {
	// 	free(line);
	// 	printf("parse error near `|'\n");
	// 	exit(0);
	// }
	while (line[i])
	{
		if ((line[i] == '<' && !line[i + 1]) || (line[i] == '<' && !line[i + 1]))
		{
			free(line);
			printf("parse error near `<'\n");
			exit(0);
		}
		if ((line[i] == '<' && line[i + 1] == '|') || (line[i] == '>' && line[i + 1] == '|'))
		{
			free(line);
			printf("parse error near \"<>|\"\n");
			exit(0);
		}
		i++;
	}
}

void	check_error(char *line)
{
	nb_of_quotes(line);
	check_error_pipes(line);
	check_error_redirections(line);
}

// void	before_save(t_headers *header, char	**str)
// {
// 	init_cmd();
// }

// void	save_cmd(t_headers *header, char **str)
// {
// 	before_save(header, str);
// 	// save(header, str);
// }

void	parse(char *line, t_headers *header)
{
	char	**str;
	check_error(line);
	str = flex(line, header);
	// save_cmd(header, str);
    ft_freee(str);

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
		line = readline("minishell🔥>");
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