/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:49:36 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:13:57 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"execution.h"

void	export(t_cmds *cmd, t_exec *exec, t_headers *header)
{
	int		t;
	t_env	*env;

	env = header->env_h;
	t = 1;
	only_export(cmd, env);
	while (cmd->args[t])
	{
		if (cmd->args[t][0] != '_' && ft_isalpha(cmd->args[t][0]) == 0)
		{
			ft_error(cmd->args[t]);
			__get_var(SETEXIT, 1);
		}
		else
		{
			add_to_export(cmd, env, header, t);
			if (__get_var(GETEXIT, 0) != 1)
				__get_var(SETEXIT, 0);
		}
		t++;
	}
	fill_env2(exec, header);
}
