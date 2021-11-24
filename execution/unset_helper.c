/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:25:20 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:25:21 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	unvalid_unset(t_cmds *cmd, int t)
{
	write(2, "export: ", 9);
	write(2, cmd->args[t], ft_strlen(cmd->args[t]));
	write(2, ": not a valid identifier\n", 26);
	__get_var(SETEXIT, 1);
}
