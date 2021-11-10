/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:40:23 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/10 02:35:43 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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

void     exec_init(t_headers *header, t_exec *exec)
{
    t_env  *env;
	int		i;

	i = 0;
    exec->i = 0;
    exec->in = 0;
    exec->fd = malloc(sizeof(int) * 2);
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
    while (exec->path[i])
    {
        exec->path[i] = ft_strjoin_free(exec->path[i], "/");
        i++;
    }
}

void     exec_free(t_exec *exec)
{
	ft_free(exec->path);
    free(exec->fd);
    free(exec);
}

void	replace_arg(t_headers *header, t_exec *exec)
{
	t_cmds	*cmd;
	char	*str;
	int		i;
	int		fd;

	cmd = header->cmd_h;
	while (cmd)
	{
		i = 0;
		while (exec->path[i])
		{
			str = ft_strjoin(exec->path[i] ,cmd->args[0]);
			if ((fd = open(str,O_RDONLY)) != -1)
			{
				close(fd);
				cmd->args[0] = ft_strjoin_free2(exec->path[i] ,cmd->args[0]);
				free(str);
				break ;
			}
			free(str);
			i++;
		}
		cmd = cmd->next;
	}
}

int     execute(t_headers *header)
{
	t_cmds	*cmd;
	t_exec	*exec;
	int		exit_stat;

    exec = malloc(sizeof(t_exec));
	exec_init(header, exec);
	// int i = 0;
    // while (exec->path[i])
    // {
    //     printf("%s\n",exec->path[i]);
    //     i++;
    // }
	replace_arg(header, exec);
	cmd = header->cmd_h;
    while (cmd)
    {
        pipe(exec->fd);
        exec->pid = fork();
        if(exec->pid == 0)
        {
            ft_pipe(cmd, exec);
			// printf("%s\n", cmd->args[0]);
            execvp(cmd->args[0], cmd->args);
        }
        waitpid(exec->pid, &exit_stat, 0);
        close(exec->fd[1]);
        if (exec->i > 0)
            close(exec->in);
        exec->in = exec->fd[0];
        exec->i++;
        cmd = cmd->next;
    }
	exec_free(exec);
    return (0);
}