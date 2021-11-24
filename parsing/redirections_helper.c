/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 04:04:24 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 04:05:00 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_addbotfile_helper(t_file	*to_add, char *val)
{
	if (val != NULL)
		to_add->filename = ft_strdup(val);
	else
		to_add->filename = ft_strdup("");
}

void	ft_addbotfile(t_cmds *head, char *val, int type)
{
	t_file	*stack;
	t_file	*to_add;

	to_add = malloc(sizeof(t_file));
	if (!to_add)
		exit(0);
	if (head->file_h == NULL)
	{
		ft_addbotfile_helper(to_add, val);
		to_add->type = type;
		to_add->next = NULL;
		to_add->prec = NULL;
		head->file_f = to_add;
		head->file_h = to_add;
	}
	else
	{
		stack = head->file_f;
		ft_addbotfile_helper(to_add, val);
		to_add->type = type;
		to_add->prec = stack;
		to_add->next = NULL;
		stack->next = to_add;
		head->file_f = to_add;
	}
}

void	ft_delbotfile(t_cmds *head)
{
	t_file	*to_delete;
	t_file	*stack;

	if (head != NULL && head->file_h != NULL)
	{
		to_delete = head->file_f;
		if (!to_delete->prec)
		{
			free(to_delete->filename);
			free(to_delete);
			head->file_h = NULL;
			head->file_f = NULL;
			to_delete = NULL;
		}
		else
		{
			stack = to_delete->prec;
			head->file_f = stack;
			stack->next = NULL;
			free(to_delete->filename);
			free(to_delete);
			to_delete = NULL;
		}
	}
}

int	redcounter(char *str, int i)
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

void	type_of_red(char *str, int r, int *red)
{
	if (str[r] == '>' && str[r + 1] != '>')
		*red = ONE;
	else if (str[r] == '>' && str[r + 1] == '>')
		*red = TWO;
	else if (str[r] == '<' && str[r + 1] != '<')
		*red = ONEREV;
	else if (str[r] == '<' && str[r + 1] == '<')
		*red = TWOREV;
}
