/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:44:44 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:44:45 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*print_exitstat(char *str, char *var)
{
	str = ft_itoa(__get_var(GETEXIT, 0));
	if (var[2])
		str = ft_strjoin_free(str, var + 2);
	return (str);
}

char	*findit(t_headers *header, char *var)
{
	t_env	*checkenv;
	char	*str;

	str = NULL;
	checkenv = header->env_h;
	if (var[1] == '?')
		return (print_exitstat(str, var));
	if (var[1] != '_' && !ft_isalpha(var[1]))
	{
		var += 2;
		return (ft_strdup(var));
	}
	var++;
	while (checkenv)
	{
		if (!ft_strcmp(checkenv->var, var))
		{
			str = ft_strdup(checkenv->val);
			return (str);
		}
		checkenv = checkenv->suivant;
	}
	str = malloc(1);
	*str = '\0';
	return (str);
}

int	calculate_dollar(char *str, int i)
{
	int	d;

	d = 0;
	while (str[i] && str[i] == '$')
	{
		i++;
		d++;
	}
	return (d);
}

void	check_dollarquotes(int *s_q, int *d_q, char c)
{
	if (c == '\'' && (*d_q % 2) == 0)
		(*s_q)++;
	if (c == '"' && (*s_q % 2) == 0)
		(*d_q)++;
}

void	dollar_is_here(t_cmds *new_cmd, int *i, t_headers *header)
{
	char	*var;
	char	*val;
	char	*rest;

	var = to_find(new_cmd->cmd, *i);
	rest = ft_strdup(ft_strstr(new_cmd->cmd + (*i), var));
	val = findit(header, var);
	new_cmd->cmd = ft_strjoin_dollarfree(new_cmd->cmd, val, *i);
	new_cmd->cmd = ft_strjoin_free(new_cmd->cmd, rest);
	(*i) = -1;
	free(var);
	free(val);
	free(rest);
}
