/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:40:23 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/09 16:40:24 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <sys/errno.h>

void    ft_pipe(t_cmds *cmd, t_exec *exec)
{

    if (cmd->next != NULL)
    {
        // write(2, "test\n", 5);
        if (dup2(exec->fd[1], 1) == -1)
        {
            write(2, strerror(errno), ft_strlen(strerror(errno)));
            write(2, "\n", 1);
        }
        close(exec->fd[1]);
        close(exec->fd[0]);
    }
    if (exec->i != 0)
    {
        if (dup2(exec->in, 0) == -1)
        {
            write(2, "ok\n", 3);
        }
        // close(exec->fd[1]);
        close(exec->in);
    }
}

int     execute(t_headers *header)
{
    t_cmds *cmd;
    t_exec *exec;
    int k;

    exec = malloc(sizeof(t_exec));
    exec->i = 0;
    exec->in = 0;
    exec->fd = malloc(sizeof(int) * 2);
    cmd = header->cmd_h;
    while (cmd)
    {
        pipe(exec->fd);
        exec->pid = fork();
        if(exec->pid == 0)
        {
            ft_pipe(cmd, exec);
            execvp(cmd->args[0], cmd->args);
        }
        if (exec->pid == 0)
            execvp(cmd->args[0], cmd->args);
        waitpid(exec->pid, &k, 0);
        close(exec->fd[1]);
        if (exec->i > 0)
            close(exec->in);
        exec->in = exec->fd[0];
        exec->i++;
        cmd = cmd->next;
    }
    
    return (0);
}