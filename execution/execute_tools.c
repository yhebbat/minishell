/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:00:23 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:00:24 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_perror(char *c, char *s)
{
	write(2, "minishell: ", 12);
	write(2, c, ft_strlen(c));
	write(2, s, ft_strlen(s));
}

void	fill_env(t_exec *exec, t_headers *header)
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
	exec->env = malloc(sizeof(char *) * (i + 1));
	env = header->env_h;
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

void	half_exec_init(t_exec *exec, t_cmds **cmd)
{
	int	i;

	i = 0;
	while (*cmd)
	{
		i++;
		(*cmd)->path = NULL;
		*cmd = (*cmd)->next;
	}
	exec->path = NULL;
	exec->pid = malloc(sizeof(int) * (i));
	exec->nb_cmd = i;
	i = 0;
	exec->i = 0;
	exec->in = 0;
	exec->fd = malloc(sizeof(int) * 2);
}

void	exec_init(t_headers *header, t_exec *exec)
{
	t_env		*env;
	t_cmds		*cmd;
	int			i;

	i = 0;
	cmd = header->cmd_h;
	half_exec_init(exec, &cmd);
	env = header->env_h;
	while (env)
	{
		if (ft_strcmp(env->var, "PATH") == 0)
		{
			exec->path = ft_split(env->val, ':');
			break ;
		}
		env = env->suivant;
	}
	while (env && exec->path[i])
	{
		exec->path[i] = ft_strjoin_free(exec->path[i], "/");
		i++;
	}
	fill_env(exec, header);
}

void	exec_free(t_exec *exec)
{
	if (exec->path)
		ft_free(exec->path);
	free(exec->pid);
	ft_free(exec->env);
	free (exec->fd);
	free (exec);
}
