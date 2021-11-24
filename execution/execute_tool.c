/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tool.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:04:14 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:04:15 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	join_path(t_exec *exec, t_cmds **cmd)
{
	char	*str;
	int		fd;
	int		i;

	i = 0;
	while (exec->path && exec->path[i])
	{
		str = ft_strjoin(exec->path[i], (*cmd)->args[0]);
		fd = open(str, O_RDONLY);
		if (fd != -1)
		{
			close(fd);
			(*cmd)->path = ft_strjoin(exec->path[i], (*cmd)->args[0]);
			free(str);
			break ;
		}
		free(str);
		i++;
	}	
}

void	replace_arg(t_headers *header, t_exec *exec)
{
	t_cmds	*cmd;

	cmd = header->cmd_h;
	while (cmd)
	{
		join_path(exec, &cmd);
		if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
			cmd->path = ft_strdup(cmd->args[0]);
		cmd = cmd->next;
	}
}

void	ft_more_cmd(t_cmds *cmd, t_exec *exec)
{
	struct stat	buff;

	signal(SIGQUIT, SIG_DFL);
	if (cmd->path == NULL)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", ft_strlen(": command not found\n"));
	}
	else
	{
		if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
		{
			stat(cmd->args[0], &buff);
			if (buff.st_mode & S_IFDIR)
			{
				ft_perror(cmd->args[0], "is a directory\n");
				exit(126);
			}
		}
		execve(cmd->path, cmd->args, exec->env);
	}
	if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
		ft_perror(cmd->args[0], ": No such file or directory\n");
	exit(127);
}

void	print_error(t_cmds *cmd, char *s, int i)
{
	write(2, "minishell: ", 12);
	write(2, cmd->args[0], ft_strlen(cmd->args[0]));
	write(2, s, ft_strlen(s));
	if (i)
		exit (i);
}

void	child_proccess(t_cmds *cmd, t_exec *exec)
{
	struct stat	buff;

	signal(SIGQUIT, SIG_DFL);
	ft_pipe_last(cmd, exec);
	if (cmd->file_h && cmd->file_h->filename != NULL)
		redirection(cmd, exec);
	if (__get_var(GETEXIT, 0) == -1)
	{
		__get_var(SETEXIT, 1);
		exit(1);
	}
	if (cmd->path == NULL)
		print_error(cmd, ": command not found\n", 0);
	else
	{
		if (cmd->args[0] && ft_strchr(cmd->args[0], '/'))
		{
			stat(cmd->args[0], &buff);
			if (buff.st_mode & S_IFDIR)
				print_error(cmd, ": is a directory\n", 126);
		}
		execve(cmd->path, cmd->args, exec->env);
	}
}
