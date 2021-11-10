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
	int		*fd;
    int		in;
    int		i;
    int		pid;
}t_exec;

int     execute(t_headers *header);
#endif
