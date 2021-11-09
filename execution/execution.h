/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:38:46 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/09 16:39:31 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"

typedef struct s_exec
{
	int		*fd;
    int		in;
    int		i;
    int		pid;
}t_exec;
int     execute(t_headers *header);
#endif
