/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:28:49 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:32:20 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_check_error(char *str)
{
	write(2, "minishell: ", 12);
	write(2, "syntax error near unexpected token `", 36);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 3);
	__get_var(SETEXIT, 258);
	return (1);
}

void	nb_of_dq(char *line, int *d_q, int *i)
{
	(*d_q) = 1;
	(*i)++;
	while (line[*i] && line[*i] != '"')
		(*i)++;
	if (line[*i] == '"')
	{
		(*d_q) = 0;
		(*i)++;
	}
}

void	nb_of_sq(char *line, int *s_q, int *i)
{
	(*s_q) = 1;
	(*i)++;
	while (line[*i] && line[*i] != '\'')
		(*i)++;
	if (line[*i] == '\'')
	{
		(*s_q) = 0;
		(*i)++;
	}
}

int	nb_of_quotes(char *line)
{
	int	i;
	int	d_q;
	int	s_q;

	i = 0;
	d_q = 0;
	s_q = 0;
	while (line[i])
	{
		if (line[i] == '"')
			nb_of_dq(line, &d_q, &i);
		else if (line[i] == '\'')
			nb_of_sq(line, &s_q, &i);
		else
			i++;
	}
	if (s_q || d_q)
	{
		printf("syntax error in quotes\n");
		return (1);
	}
	return (0);
}

int	check_space(char *line, int i)
{
	if (line[i] == '|')
	{
		i++;
		while (line[i] == ' ')
			i++;
		if (line[i] == '|' || line[i] == '\0')
			return (1);
	}
	return (0);
}
