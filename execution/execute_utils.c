/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:06:29 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:06:40 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	check_builtins(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	int	in;
	int	out;

	out = dup(1);
	in = dup(0);
	if (cmd->file_h && cmd->file_h->filename != NULL)
		redirection(cmd, exec);
	if (__get_var(GETEXIT, 0) == -1)
	{
		__get_var(SETEXIT, 1);
		dup_n_close(out, in);
	}
	else
	{
		if (cmd->args[0])
			check_builtins_condition(cmd, exec, header);
		dup_n_close(out, in);
	}
}

int	is_builtin(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	if (cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "env") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "echo") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "cd") == 0)
			return (1);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			return (1);
		return (0);
	}
	return (0);
}

void	ft_cmds(t_exec *exec, t_cmds **cmd, t_headers *header)
{
	exec->pid[exec->i] = fork();
	if (exec->pid[exec->i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_pipe((*cmd), exec);
		if ((*cmd)->file_h && (*cmd)->file_h->filename != NULL)
			redirection((*cmd), exec);
		if (__get_var(GETEXIT, 0) == -1)
		{
			__get_var(SETEXIT, 1);
			exit(1);
		}
		check_builtins_execve((*cmd), exec, header);
		exit(__get_var(GETEXIT, 0));
	}
}

void	ft_simple_cmd(t_exec *exec, t_cmds *cmd, t_headers *header)
{
	pipe(exec->fd);
	exec->pid[exec->i] = fork();
	if (exec->pid[exec->i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_pipe_last(cmd, exec);
		if (cmd->file_h && cmd->file_h->filename != NULL)
			redirection(cmd, exec);
		if (__get_var(GETEXIT, 0) == -1)
		{
			__get_var(SETEXIT, 1);
			close(exec->fd[1]);
			close(exec->fd[0]);
			exit(1);
		}
		check_builtins_execve(cmd, exec, header);
		exit(__get_var(GETEXIT, 0));
	}
	close(exec->fd[1]);
	close(exec->fd[0]);
}

void	ft_last_cmd(t_exec *exec, t_cmds *cmd, t_headers *header)
{
	if (cmd && cmd->next == NULL)
	{
		if (cmd->prec != NULL)
			ft_simple_cmd(exec, cmd, header);
		else
		{
			if (is_builtin(cmd, exec, header) || !cmd->args[0])
				check_builtins(cmd, exec, header);
			else
				check_builtins_execve(cmd, exec, header);
		}
		if (exec->in != 0)
			close(exec->in);
	}
}
