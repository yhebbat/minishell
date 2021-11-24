/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct_sec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:33:30 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:33:31 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addbotcmd_help(t_cmds *to_add)
{
	to_add->file_h = NULL;
	to_add->file_f = NULL;
	to_add->path = NULL;
	to_add->next = NULL;
	to_add->args = NULL;
}

void	ft_addbotcmd(t_headers *head, char *val)
{
	t_cmds	*stack;
	t_cmds	*to_add;

	to_add = malloc(sizeof(t_cmds));
	if (!to_add)
		exit(0);
	if (head->cmd_h == NULL)
	{
		to_add->cmd = ft_strdup(val);
		ft_addbotcmd_help(to_add);
		to_add->prec = NULL;
		head->cmd_f = to_add;
		head->cmd_h = to_add;
	}
	else
	{
		stack = head->cmd_f;
		to_add->cmd = ft_strdup(val);
		ft_addbotcmd_help(to_add);
		to_add->prec = stack;
		stack->next = to_add;
		head->cmd_f = to_add;
	}
}

void	ft_freefile(t_cmds *head)
{
	while (head->file_h)
		ft_delbotfile(head);
}

void	ft_delbotcmd_help(t_cmds *to_delete)
{
	ft_freefile(to_delete);
	ft_free(to_delete->args);
	free(to_delete->cmd);
	if (to_delete->path != NULL)
		free(to_delete->path);
}

void	ft_delbotcmd(t_headers *head)
{
	t_cmds	*to_delete;
	t_cmds	*stack;

	if (head != NULL && head->cmd_h != NULL)
	{
		to_delete = head->cmd_f;
		if (!to_delete->prec)
		{
			ft_delbotcmd_help(to_delete);
			free(to_delete);
			head->cmd_h = NULL;
			head->cmd_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->prec;
			head->cmd_f = stack;
			stack->next = NULL;
			ft_delbotcmd_help(to_delete);
			free(to_delete);
			to_delete = NULL;
		}
	}
}
