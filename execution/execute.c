/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:27 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:06:13 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_cmds	*commands(t_exec *exec, t_cmds *cmd, t_headers *header)
{
	while (cmd && cmd->next != NULL)
	{
		pipe(exec->fd);
		ft_cmds(exec, &cmd, header);
		if (exec->fd[1] > 2)
			close(exec->fd[1]);
		if (exec->in != 0)
			close(exec->in);
		exec->in = exec->fd[0];
		exec->i++;
		cmd = cmd->next;
	}
	return (cmd);
}

void	some_status_code(t_cmds *cmd, int *stat)
{
	if (cmd->prec)
	{
		if (WIFEXITED(*stat))
			__get_var(SETEXIT, WEXITSTATUS(*stat));
		else if (WIFSIGNALED(*stat))
		{
			__get_var(SETEXIT, WTERMSIG(*stat) + 128);
			if (WTERMSIG(*stat) == SIGQUIT)
				write(2, "QUIT\n", 6);
		}
	}
}

int	execute(t_headers *header)
{
	t_cmds	*cmd;
	t_exec	*exec;
	int		stat;
	int		i;

	__get_var(SETPID, -1);
	i = 0;
	exec = malloc(sizeof(t_exec));
	exec_init(header, exec);
	replace_arg(header, exec);
	cmd = header->cmd_h;
	cmd = commands(exec, cmd, header);
	ft_last_cmd(exec, cmd, header);
	while (i < exec->nb_cmd)
	{
		waitpid(exec->pid[i], &stat, 0);
		i++;
	}
	some_status_code(cmd, &stat);
	if (exec->in != 0)
		close(exec->in);
	exec_free(exec);
	__get_var(SETPID, 0);
	return (0);
}
