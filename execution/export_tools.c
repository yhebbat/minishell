/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:14:29 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:14:30 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	inside_fill(t_exec *exec, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->val != NULL)
		{
			exec->env[i] = ft_strjoin(env->var, "=");
			exec->env[i] = ft_strjoin_free(exec->env[i], env->val);
			i++;
		}
		env = env->suivant;
	}
	exec->env[i] = 0;
}

void	fill_env2(t_exec *exec, t_headers *header)
{
	int		i;
	t_env	*env;

	i = 0;
	env = header->env_h;
	while (env)
	{
		if (env->val != NULL)
			i++;
		env = env->suivant;
	}
	ft_free(exec->env);
	exec->env = NULL;
	exec->env = malloc(sizeof(char *) * (i + 1));
	env = header->env_h;
	inside_fill(exec, env);
}

void	only_export(t_cmds *cmd, t_env *env)
{
	if (!cmd->args[1])
	{
		while (env)
		{
			if (env->val != NULL)
			{
				printf("declare -x");
				printf(" %s=", env->var);
				printf("\"%s\"\n", env->val);
			}
			else
			{
				printf("declare -x ");
				printf("%s\n", env->var);
			}
			env = env->suivant;
		}
		__get_var(SETEXIT, 0);
	}
}

void	init_str(char **str, t_cmds *cmd, int *eq, int t)
{
	str[0] = check_eq(cmd->args[t], eq);
	str[1] = fill_exportval(cmd->args[t], eq);
	str[2] = 0;
}

void	add_to_export(t_cmds *cmd, t_env *env, t_headers *header, int t)
{
	int		eq;
	t_env	*exist_env;
	char	**str;

	str = malloc(sizeof(char *) * 3);
	init_str(str, cmd, &eq, t);
	exist_env = find_var_env(str[0], env);
	if (eq == 0 && !exist_env)
		ft_addbottom(header, str[0], NULL);
	else if (eq == 1 && exist_env)
	{
		free(exist_env->val);
		exist_env->val = ft_strdup_free(str[1]);
	}
	else if ((eq == 1 || eq == 2) && !exist_env)
		ft_addbottom(header, str[0], str[1]);
	else if (eq == 2 && exist_env)
		exist_env->val = ft_strjoin_free(exist_env->val, str[1]);
	if (((eq == 1 || eq == 2) && !exist_env) || (eq == 2 && exist_env))
		free(str[1]);
	free(str[0]);
	free(str);
}
