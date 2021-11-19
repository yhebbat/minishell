/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:40:23 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/17 05:49:58 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

// void    ft_pipe(t_cmds *cmd, t_exec *exec)
// {

//     if (cmd->next != NULL)
//     {
//         // write(2, "test\n", 5);
//         if (dup2(exec->fd[1], 1) == -1)
//         {
//             write(2, strerror(errno), ft_strlen(strerror(errno)));
//             write(2, "\n", 1);
//         }
//         close(exec->fd[1]);
//         close(exec->fd[0]);
//     }
//     if (exec->i != 0)
//     {
//         if (dup2(exec->in, 0) == -1)
//         {
//             write(2, "ok\n", 3);
//         }
//         // close(exec->fd[1]);
//         close(exec->in);
//     }
// }

void	fill_env(t_exec *exec, t_headers *header)
{
	int		i;
	t_env	*env;

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
		// if (env->val != NULL)
		// 	printf("%s=%s\n", env->var, env->val);
		if (env->val != NULL)
		{
			exec->env[i] = ft_strjoin(env->var, "=");
			exec->env[i] = ft_strjoin_free(exec->env[i], env->val);
			i++;
		}
		env = env->suivant;
	}
	exec->env[i] = 0;
	// i = 0;
	// while (exec->env[i])
	// {
	// 	printf("%s\n", exec->env[i]);
	// 	i++;
	// }
}

void     exec_init(t_headers *header, t_exec *exec)
{
    t_env  *env;
	t_cmds *cmd;
	int		i;

	i = 0;
	cmd = header->cmd_h;
	while (cmd)
	{
		i++;
		cmd->path = NULL;
		cmd = cmd->next;
	}
	exec->path = NULL;
	exec->pid = malloc(sizeof(int) * (i));
	exec->nb_cmd = i;
	i = 0;
    exec->i = 0;
    exec->in = 0;
	// exec->out = 1;
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
    while (env && exec->path[i])
    {
        exec->path[i] = ft_strjoin_free(exec->path[i], "/");
        i++;
    }
    fill_env(exec, header);
}

void     exec_free(t_exec *exec)
{
	if (exec->path)
		ft_free(exec->path);
	free(exec->pid);
	ft_free(exec->env);
    free(exec->fd);
    free(exec);
}

void    replace_arg(t_headers *header, t_exec *exec)
{
	t_cmds	*cmd;
	char	*str;
	int		i;
	int		fd;

	cmd = header->cmd_h;
	while (cmd)
	{
		i = 0;
		// cmd->path = NULL;
		while (exec->path && exec->path[i])
		{
			//printf("hjk\n");
			str = ft_strjoin(exec->path[i] ,cmd->args[0]);
			if ((fd = open(str,O_RDONLY)) != -1)
			{
				close(fd);
				cmd->path = ft_strjoin(exec->path[i] ,cmd->args[0]);
				free(str);
				break ;
			}
			free(str);
			i++;
		}
		if (cmd->args[0] && strchr(cmd->args[0],'/'))
		{
			cmd->path = ft_strdup(cmd->args[0]);
		}
		cmd = cmd->next;
	}
}

// int     execute(t_headers *header)
// {
// 	t_cmds	*cmd;
// 	t_exec	*exec;
// 	int		exit_stat;

//     exec = malloc(sizeof(t_exec));
// 	exec_init(header, exec);
// 	// int i = 0;
//     // while (exec->path[i])
//     // {
//     //     printf("%s\n",exec->path[i]);
//     //     i++;
//     // }
//     replace_arg(header, exec);
// 	cmd = header->cmd_h;
//     while (cmd)
//     {
//         pipe(exec->fd);
//         exec->pid = fork();
//         if(exec->pid == 0)
//         {
//             ft_pipe(cmd, exec);
// 			// printf("%s\n", cmd->args[0]);
//             execve(cmd->args[0], cmd->args, exec->env);
//         }
//         waitpid(exec->pid, &exit_stat, 0);
//         close(exec->fd[1]);
//         if (exec->i > 0)
//             close(exec->in);
//         exec->in = exec->fd[0];
//         exec->i++;
//         cmd = cmd->next;
//     }
// 	exec_free(exec);
//     return (0);
// }

void	ft_execve(t_cmds *cmd, t_exec *exec)
{
	int		exitstatu;
	int		pid;
	struct stat buff;
	// pid = fork();
	// if (pid == 0)
	// {
		// printf("lll*\n");
	if (!cmd->next && !cmd->prec)
	{
		pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			ft_pipe_last(cmd, exec);
			if (cmd->file_h && cmd->file_h->filename != NULL)
				redirection(cmd, exec);
			if (cmd->path == NULL)
				printf("minishell: %s: command not found\n", cmd->args[0]);
			else
			{
		
				if (cmd->args[0] && strchr(cmd->args[0],'/'))
				{
					stat(cmd->args[0], &buff);
					if(buff.st_mode & S_IFDIR)
					{
						printf("minishell: %s: is a directory\n", cmd->args[0]);
						exit(126);
					}
				}
				execve(cmd->path, cmd->args, exec->env);
			}
			if (cmd->args[0] && strchr(cmd->args[0],'/'))
				printf("minishell: %s: No such file or directory\n", cmd->args[0]);
			exit(127);
		}
		waitpid(pid, &exitstatu, 0);
		if (WIFEXITED(exitstatu))
			__get_var(SETEXIT, WEXITSTATUS(exitstatu));
		else if (WIFSIGNALED(exitstatu))
		{
			//dprintf(2, "im here\n");
			__get_var(SETEXIT, WTERMSIG(exitstatu) + 128);
			//g_exit_status = WTERMSIG(stat) + 128;
			if (WTERMSIG(exitstatu) == SIGQUIT)
				dprintf(2,"\\QUIT\n");
		}
	}
	else
	{
		signal(SIGQUIT, SIG_DFL);
		if (cmd->path == NULL)
			printf("minishell: %s: command not found\n", cmd->args[0]);
		else
		{
			if (cmd->args[0] && strchr(cmd->args[0],'/'))
			{
				stat(cmd->args[0], &buff);
				if(buff.st_mode & S_IFDIR)
				{
					printf("minishell: %s: is a directory\n", cmd->args[0]);
					exit(126);
				}
			}
			execve(cmd->path, cmd->args, exec->env);
		}
		if (cmd->args[0] && strchr(cmd->args[0],'/'))
			printf("minishell: %s: No such file or directory\n", cmd->args[0]);
		exit(127);
	}
	// }
	// else
	// {
	// 	// if (cmd->next)
	// 	// {
	// 		printf("ttt*\n");
	// 		waitpid(pid , &exitstatu, 0);
	// 		if (WIFEXITED(exitstatu))
	// 		{
	// 			dprintf(2, "im here\n");
	// 			__get_var(SETEXIT, WEXITSTATUS(exitstatu));
	// 			printf("%d\n",__get_var(GETEXIT, WEXITSTATUS(exitstatu)));
	// 			//g_exit_status = WEXITSTATUS(stat);
	// 		}
	// 		else if (WIFSIGNALED(exitstatu))
	// 		{
				
	// 			__get_var(SETEXIT, WTERMSIG(exitstatu) + 128);
	// 			//g_exit_status = WTERMSIG(stat) + 128;
	// 			if (WTERMSIG(exitstatu) == SIGQUIT)
	// 				dprintf(2,"\\QUIT\n");
	// 		}
	// 			//exit (__get_var(GETEXIT, 0));
	// 			//dprintf(2, "im here\n");
	// 	// }
	// }
}	

void    check_builtins_execve(t_cmds *cmd, t_exec *exec, t_headers  *header)
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
			cd(cmd);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			ft_exit(cmd);//todo
		else
			ft_execve(cmd, exec);
	}
}

void    check_builtins(t_cmds *cmd, t_exec *exec, t_headers  *header)
{
	int in;
	int out;

	out = dup(1);
	in = dup(0);
	if (cmd->file_h && cmd->file_h->filename != NULL)
		redirection(cmd, exec);
	if (cmd->args[0])
	{
		// printf("++++++++\n");
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
			cd(cmd);
		else if (ft_strcmp(cmd->args[0], "exit") == 0)
			ft_exit(cmd);//todo
	}
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
}

int    is_builtin(t_cmds *cmd, t_exec *exec, t_headers  *header)
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
			return (1);//todo
		return (0);
	}
	return (0);
}

void		ft_cmds(t_exec *exec, t_cmds *cmd, t_headers *header/*, int	exit_stat*/)
{
	exec->pid[exec->i] = fork();
	if (exec->pid[exec->i] == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		ft_pipe(cmd, exec);
		//check_red
		if (cmd->file_h && cmd->file_h->filename != NULL)
			redirection(cmd, exec);
		check_builtins_execve(cmd, exec, header);
		exit(__get_var(GETEXIT,0));
		// printf("%s\n", cmd->args[0]);
		// execve(cmd->args[0], cmd->args, exec->env);
	}
	// check_builtins(cmd, exec, header->env_h);
}

void	ft_last_cmd(t_exec *exec, t_cmds *cmd, t_headers *header)
{
	if (cmd && cmd->next == NULL)
	{
		if (cmd->prec != NULL)
		{
			pipe(exec->fd);
			exec->pid[exec->i] = fork();
			if (exec->pid[exec->i] == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				ft_pipe_last(cmd, exec);
				// check_red
				if (cmd->file_h && cmd->file_h->filename != NULL)
					redirection(cmd, exec);
				check_builtins_execve(cmd, exec, header);
				exit(__get_var(GETEXIT,0));
			}
			close(exec->fd[1]);
			close(exec->fd[0]);
		}
		else
		{
			if (is_builtin(cmd, exec, header) || !cmd->args[0])
			{
				check_builtins(cmd, exec, header);
			}
			else
				check_builtins_execve(cmd, exec, header);
		}
		if (exec->in != 0)
			close(exec->in);
	}
}

int     execute(t_headers *header)
{
	t_cmds	*cmd;
	t_exec	*exec;
	int		stat;
	int 	i;

	__get_var(SETPID, -1);
	i = 0;
    exec = malloc(sizeof(t_exec));
	exec_init(header, exec);
	//if (exec->path)
		replace_arg(header, exec);//maybe kayn some leaks here
	cmd = header->cmd_h;
    while (cmd && cmd->next != NULL)
    {
        pipe(exec->fd);
		ft_cmds(exec, cmd, header/*, &exit_stat*/);
		if (exec->fd[1] > 2)
        	close(exec->fd[1]);
        if (exec->in != 0)
            close(exec->in);
        exec->in = exec->fd[0];
        exec->i++;
        cmd = cmd->next;
    }
	ft_last_cmd(exec, cmd, header);
	// dprintf(2, "DBG exit status : %d\n", value);
	// // printf("%d\n", exec->nb_cmd);
	while (i < exec->nb_cmd)
	{
		waitpid(exec->pid[i], &stat, 0);
		i++;
	}
	if (cmd->prec)
	{
		if (WIFEXITED(stat))
		{
			__get_var(SETEXIT, WEXITSTATUS(stat));
			// dprintf(1,"||%d\n",__get_var(GETEXIT,0));
			// g_exit_status = WEXITSTATUS(stat);
		}
		else if (WIFSIGNALED(stat))
		{
			__get_var(SETEXIT, WTERMSIG(stat) + 128);
			//g_exit_status = WTERMSIG(stat) + 128;
			if (WTERMSIG(stat) == SIGQUIT)
				dprintf(2,"\\QUIT\n");
		}
	}
	// if (exec->out != 1)
	// 	close(exec->out);
	if (exec->in != 0)
		close(exec->in);
	//dprintf(1,"my exit status is %d\n",__get_var(GETEXIT,0));
	exec_free(exec);
//	g_pids = 0;
  	__get_var(SETPID, 0);
    return (0);
}
