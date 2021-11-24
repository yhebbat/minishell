/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flex_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 03:50:35 by yhebbat           #+#    #+#             */
/*   Updated: 2021/11/24 03:50:36 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_mmots_helper(char const *s, int	*i)
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

void	ft_rempp_helper2(t_toke *toke, char **p, char const *s)
{
	p[toke->j][toke->k] = s[toke->i];
	toke->k++;
	toke->i++;
}

void	ft_rempp_helper(t_toke *toke, char **p, char const *s)
{
	if (s[toke->i] == '"')
	{
		toke->i++;
		while (s[toke->i] != '"')
		{
			ft_rempp_helper2(toke, p, s);
		}
		toke->i++;
	}
	else if (s[toke->i] == '\'')
	{
		toke->i++;
		while (s[toke->i] != '\'')
		{
			ft_rempp_helper2(toke, p, s);
		}
		toke->i++;
	}
	else
		p[toke->j][toke->k++] = s[toke->i++];
}
