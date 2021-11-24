/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:03:19 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:55:23 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addbottom_helper(t_env *to_add, char *var, char *val)
{
	if (var != NULL)
		to_add->var = ft_strdup(var);
	if (val != NULL)
		to_add->val = ft_strdup(val);
	else
		to_add->val = NULL;
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
		ft_addbottom_helper(to_add, var, val);
		to_add->suivant = NULL;
		to_add->preced = NULL;
		head->env_f = to_add;
		head->env_h = to_add;
	}
	else
	{
		stack = head->env_f;
		ft_addbottom_helper(to_add, var, val);
		to_add->preced = stack;
		to_add->suivant = NULL;
		stack->suivant = to_add;
		head->env_f = to_add;
	}
}

void	from_tab_to_ll(char **env, t_headers *header)
{
	int		i;
	char	**str;

	i = 0;
	while (env[i])
	{
		str = ft_split(env[i], '=');
		ft_addbottom(header, str[0], str[1]);
		ft_free(str);
		i++;
	}
}

void	envi(char **env, t_headers *header)
{
	from_tab_to_ll(env, header);
}
