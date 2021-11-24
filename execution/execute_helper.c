/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:05:21 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:05:35 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	one_command(t_cmds *cmd, t_exec *exec)
{
	int	pid;
	int	exitstatu;

	pid = fork();
	if (pid == 0)
	{
		child_proccess(cmd, exec);
		if (cmd->args[0] && strchr(cmd->args[0], '/'))
			ft_perror(cmd->args[0], ": No such file or directory\n");
		exit(127);
	}
	waitpid(pid, &exitstatu, 0);
	if (WIFEXITED(exitstatu))
		__get_var(SETEXIT, WEXITSTATUS(exitstatu));
	else if (WIFSIGNALED(exitstatu))
	{
		__get_var(SETEXIT, WTERMSIG(exitstatu) + 128);
		if (WTERMSIG(exitstatu) == SIGQUIT)
			write(2, "\\QUIT\n", 7);
	}
}

void	ft_execve(t_cmds *cmd, t_exec *exec)
{
	if (!cmd->next && !cmd->prec)
	{
		one_command(cmd, exec);
	}
	else
		ft_more_cmd(cmd, exec);
}

void	check_builtins_execve(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	if (cmd->args[0])
	{
		if (ft_strcmp(cmd->args[0], "env") == 0)
			ft_env(exec);
		else if (ft_strcmp(cmd->args[0], "echo") == 0)
			echo(cmd);
		else if (ft_strcmp(cmd->args[0], "export") == 0)
			export(cmd, exec, header);
		else if (ft_strcmp(cmd->args[0], "unset") == 0)
			unset(cmd, exec, header);
		else if (ft_strcmp(cmd->args[0], "pwd") == 0)
			pwd(cmd);
		else if (ft_strcmp(cmd->args[0], "cd") == 0)
			cd(cmd, header);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			ft_exit(cmd);
		else
			ft_execve(cmd, exec);
	}
}

void	dup_n_close(int out, int in)
{
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

void	check_builtins_condition(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	if (ft_strcmp(cmd->args[0], "env") == 0)
		ft_env(exec);
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		echo(cmd);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		export(cmd, exec, header);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		unset(cmd, exec, header);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		pwd(cmd);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		cd(cmd, header);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		ft_exit(cmd);
}
