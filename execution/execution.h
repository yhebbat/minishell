/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:38:46 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/10 01:11:11 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/errno.h>

typedef struct s_exec
{
    char    **path;
    char    **env;
	int		*fd;
    int		in;
    int		i;
    int		pid;
}t_exec;

void	ft_env(t_exec *exec);
void    cd(t_cmds *cmd);
int     execute(t_headers *header);
void    unset(t_cmds *cmd);
void    pwd(t_cmds *cmd);
void    echo(t_cmds *cmd);
void    export(t_cmds *cmd);
void    ft_exit(t_cmds *cmd);
void    ft_pipe(t_cmds *cmd, t_exec *exec);
void    ft_pipe_last(t_cmds *cmd, t_exec *exec);
#endif
