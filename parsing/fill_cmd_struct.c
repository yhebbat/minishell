/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:02:00 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:41:50 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_calcul(char *str, int *i, int *d)
{
	if (str[*i] == '$')
	{
		(*d) = calculate_dollar(str, *i);
		(*i) += (*d - 1);
	}
}

int	dollar_herdoc(char *str, int i)
{
	if (str[i] == '$')
	{
		i--;
		while (i > 0 && str[i] == ' ')
			i--;
		if (i >= 1 && str[i] == '<' && str[i - 1] == '<')
			return (1);
	}
	return (0);
}

int	ft_condition(t_cmds	*n_cmd, int i, int s_q, int d)
{
	if (n_cmd->cmd[i] == '$' && (d % 2) && n_cmd->cmd[i + 1] != '\0'
		&& n_cmd->cmd[i + 1] != '"' && n_cmd->cmd[i + 1] != '='
		&& n_cmd->cmd[i + 1] != '+' && n_cmd->cmd[i + 1] != '-'
		&& s_q % 2 == 0)
		return (1);
	return (0);
}

void	checkdollar_cmd(t_headers *header)
{
	t_cmds	*n_cmd;
	int		i;
	int		s_q;
	int		d_q;
	int		d;

	n_cmd = header->cmd_h;
	while (n_cmd)
	{
		d = 0;
		i = 0;
		s_q = 0;
		d_q = 0;
		while (n_cmd->cmd[i])
		{
			check_dollarquotes(&s_q, &d_q, n_cmd->cmd[i]);
			dollar_calcul(n_cmd->cmd, &i, &d);
			dollar_herdoc(n_cmd->cmd, i);
			if (ft_condition(n_cmd, i, s_q, d) && !dollar_herdoc(n_cmd->cmd, i))
				dollar_is_here(n_cmd, &i, header);
			i++;
		}
		n_cmd = n_cmd->next;
	}
}

void	save_cmd(t_headers *header, char **str)
{
	t_cmds	*new_cmd;
	t_file	*file;
	int		i;

	fill_cmd(header, str);
	checkdollar_cmd(header);
	i = checkredirection_cmd(header->cmd_h);
	ft_complet(header);
	if (header->cmd_h)
		if (i != -1 && (header->cmd_h->args[0] || header->cmd_h->file_h))
			execute(header);
	new_cmd = header->cmd_h;
	while (new_cmd)
	{
		file = new_cmd->file_h;
		while (file)
		{
			if (file->type == 4)
				unlink(file->filename);
			file = file->next;
		}
		new_cmd = new_cmd->next;
	}
	while (header->cmd_h)
		ft_delbotcmd(header);
}
