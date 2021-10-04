#include "minishell.h"

// void	ft_free(t_env *to_del)
// {
// 	int i;
// 	// int j;

// 	i = 0;
// 	// j = 0;
// 	// while (to_del->val[i])
// 	// 	i++;
// 	// i++;
// 	// while (i >= 0)
// 	// {
// 		// printf("%c\n", to_del->val[i]);
// 		free(to_del->val);
// 	// 	i--;
// 	// }
// 	// i = 0;
// 	// // while (to_del->var[i])
// 	// // {
// 	// // 	// printf("%c\n", to_del->var[i]);
// 	// // 	free(&to_del->var[i]);
// 	// // 	i++;
// 	// // }
// 	// while (i >= 0)
// 	// {
// 	// 	i--;
// 	// }
// 	// i = 0;
// 	// j = 0;
// 	// while (to_del->var[i])
// 	// 	i++;
// 	// // i++;
// 	// while (j < i)
// 	// {
// 	// 	free(&to_del->var[j]);
// 	// 	j++;
// 	// }
// }

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

// void	env_from_tab_to_ll(char **env, t_henv *henv)
// {
// 	int	i;

// 	i = 0;
// 	while(env[i])
// 	{

// 		i++;
// 	}
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
//	env_from_tab_to_ll(env, henv);
	ft_addtop(henv, "tst", "talam");
	printf("---%s\n", henv->header->val);
	ft_addtop(henv, "tst2", "salam2");
	new_env = henv->header;
	while (new_env)
	{
		printf("%s = %s\n", new_env->var, new_env->val);
		new_env = new_env->suivant;
	}
	ft_deltop(henv);
	ft_deltop(henv);
	free(henv);
	henv = NULL;
}