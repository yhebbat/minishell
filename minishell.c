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

void	ft_deltop(t_henv *head)
{
	t_env	*to_delete;
	t_env	*stack;

	if (head != NULL && head->header != NULL)
	{
		to_delete = head->header;
		if (!to_delete->suivant)
		{
			free(to_delete->val);
			free(to_delete->var);
			free(to_delete);
			head->header = NULL;
			head->footer = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->suivant;
			head->header = stack;
			stack->preced = NULL;
			free(to_delete->val);
			free(to_delete->var);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

void	ft_delbottom(t_henv *head)
{
	t_env	*to_delete;
	t_env	*stack;

	if (head != NULL && head->header != NULL)
	{
		to_delete = head->footer;
		if (!to_delete->preced)
		{
			free(to_delete->val);
			free(to_delete->var);
			free(to_delete);
			head->header = NULL;
			head->footer = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->preced;
			head->footer = stack;
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

void	ft_addtop(t_henv *head, char *var, char *val)
{
	t_env	*stack;
	t_env	*to_add;

	to_add = malloc(sizeof(t_env));
	if (!to_add)
		exit(0);
	if (head->header == NULL)
	{
		to_add->var = add_str(var);
		to_add->val = add_str(val);
		to_add->suivant = NULL;
		to_add->preced = NULL;
		head->footer = to_add;
		head->header = to_add;
	}
	else
	{
		stack = head->header;
		to_add->var = add_str(var);
		to_add->val = add_str(val);
		to_add->suivant = stack;
		to_add->preced = NULL;
		stack->preced = to_add;
		head->header = to_add;
	}
}

void	ft_addbottom(t_henv *head, char *var, char *val)
{
	t_env	*stack;
	t_env	*to_add;

	to_add = malloc(sizeof(t_env));
	if (!to_add)
		exit(0);
	if (head->header == NULL)
	{
		to_add->var = add_str(var);
		to_add->val = add_str(val);
		to_add->suivant = NULL;
		to_add->preced = NULL;
		head->footer = to_add;
		head->header = to_add;
	}
	else
	{
		stack = head->footer;
		to_add->var = add_str(var);
		to_add->val = add_str(val);
		to_add->preced = stack;
		to_add->suivant = NULL;
		stack->suivant = to_add;
		head->footer = to_add;
	}
}

void	env_from_tab_to_ll(char **env, t_henv *henv)
{
	int i;
	char **str;

	i = 0;
	while(env[i])
	{
		str = ft_split(env[i], '=');
		ft_addbottom(henv, str[0], str[1]);
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
// 	nb = henv->header;
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

int	main(int ac, char **av, char **env)
{
	t_henv	*henv;
	t_env	*new_env;
	(void)ac;
	(void)av;
	(void)env;

	new_env = NULL;
	henv = malloc(sizeof(t_henv));
	henv->header = NULL;
	henv->footer = NULL;
	env_from_tab_to_ll(env, henv);
	// ft_addtop(henv, "tst", "talam");
	// ft_addtop(henv, "tst2", "salam2");
	new_env = henv->header;
	while (new_env)
	{
		printf("%s = %s\n", new_env->var, new_env->val);
		new_env = new_env->suivant;
	}
	while (henv->header)
		ft_delbottom(henv);
	free(henv);
	henv = NULL;
	// system("leaks minishell");
}