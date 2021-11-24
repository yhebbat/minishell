/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:51 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:24:42 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "execution.h"

void	del1(t_headers *header, t_env *to_del)
{
	t_env	*exist_env;

	exist_env = to_del->suivant;
	header->env_h = exist_env;
	exist_env->preced = NULL;
	if (to_del->val != NULL)
		free(to_del->val);
	if (to_del->var != NULL)
		free(to_del->var);
	free(to_del);
	to_del = NULL;
}

void	del2(t_headers *header, t_env *to_del)
{
	t_env	*exist_env;

	exist_env = to_del->suivant;
	exist_env->preced = to_del->preced;
	exist_env = to_del->preced;
	exist_env->suivant = to_del->suivant;
	if (to_del->val != NULL)
		free(to_del->val);
	if (to_del->var != NULL)
		free(to_del->var);
	free(to_del);
	to_del = NULL;
}

void	del3(t_headers *header, t_env *to_del)
{
	t_env	*exist_env;

	exist_env = to_del->preced;
	exist_env->suivant = NULL;
	header->env_f = exist_env;
	if (to_del->val != NULL)
		free(to_del->val);
	if (to_del->var != NULL)
		free(to_del->var);
	free(to_del);
	to_del = NULL;
}

void	valid_unset(t_headers *header, t_env *to_del)
{
	if (to_del)
	{
		if (to_del->preced == NULL && to_del->suivant)
			del1(header, to_del);
		else if (to_del->preced && to_del->suivant)
			del2(header, to_del);
		else if (to_del->preced && to_del->suivant == NULL)
			del3(header, to_del);
	}
}

void	unset(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	int		t;
	t_env	*to_del;
	t_env	*env;
	char	*str;

	t = 1;
	env = header->env_h;
	while (cmd->args[t])
	{
		if (cmd->args[t][0] != '_' && ft_isalpha(cmd->args[t][0]) == 0)
			unvalid_unset(cmd, t);
		else
		{
			str = ft_strdup(cmd->args[t]);
			to_del = find_var_env(str, env);
			valid_unset(header, to_del);
			free(str);
			if (__get_var(GETEXIT, 0) != 1)
				__get_var(SETEXIT, 0);
		}
		t++;
	}
	fill_env2(exec, header);
}
