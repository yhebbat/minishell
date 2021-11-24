/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:57:54 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 04:01:36 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_mots_helper(char const *s, int	*i)
{
	if (s[*i] == '"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '"')
			(*i)++;
	}
	else if (s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
}

void	laysameh(int *r, int *i)
{
	(*r)++;
	(*i)++;
}

void	ft_remp_helper2(t_toke *toke, char **p, char const *s)
{
	p[toke->j][toke->k] = s[toke->i];
	toke->k++;
	toke->i++;
}

void	ft_remp_helper(t_toke *toke, char **p, char const *s)
{
	if (s[toke->i] == '"')
	{
		ft_remp_helper2(toke, p, s);
		while (s[toke->i] != '"')
		{
			ft_remp_helper2(toke, p, s);
		}
		ft_remp_helper2(toke, p, s);
	}
	else if (s[toke->i] == '\'')
	{
		ft_remp_helper2(toke, p, s);
		while (s[toke->i] != '\'')
		{
			ft_remp_helper2(toke, p, s);
		}
		ft_remp_helper2(toke, p, s);
	}
	else
		p[toke->j][toke->k++] = s[toke->i++];
}

char	**split_pipe(char *line, t_headers *header)
{
	char	**test;

	(void)header;
	test = ft_toke(line, '|');
	return (test);
}
