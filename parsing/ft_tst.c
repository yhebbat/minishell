/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhebbat <yhebbat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 01:02:48 by mgrissen          #+#    #+#             */
/*   Updated: 2021/11/24 03:49:10 by yhebbat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	*ft_freee(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (0);
}

static	int	ft_mmots(char const *s, char c)
{
	int			i;
	int			k;
	int			p;
	int			d_q;

	d_q = 0;
	i = 0;
	k = 0;
	p = 1;
	if (*s)
	{
		while (s[i])
		{
			ft_mmots_helper(s, &i);
			if (s[i] == c)
				p = 1;
			else if (p == 1 && !d_q)
			{
				p = 0;
				k++;
			}
			i++;
		}
	}
	return (k);
}

static int	ft_alpha(char const *s, char c, int i)
{
	int	r;

	r = 0;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
				laysameh(&r, &i);
			i++;
		}
		else if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				laysameh(&r, &i);
			i++;
		}
		else
			laysameh(&r, &i);
	}
	return (r);
}

static char	**ft_rempp(char **p, char const *s, char c, int mots)
{
	t_toke	*take;

	take = malloc(sizeof(t_toke));
	take->i = 0;
	take->j = 0;
	while (s[take->i] && mots > take->j)
	{
		take->k = 0;
		while (s[take->i] == c)
			s++;
		p[take->j] = malloc(sizeof(char) * ft_alpha(s, c, take->i) + 1);
		if (!p[take->j])
			return (ft_freee(p));
		while (s[take->i] && s[take->i] != c)
		{
			ft_rempp_helper(take, p, s);
		}
		p[take->j][take->k] = '\0';
		take->j++;
	}
	p[take->j] = 0;
	free(take);
	return (p);
}

char	**ft_flex(char const *s, char c)
{
	char	**p;
	int		mots;

	if (s == NULL)
		return (0);
	mots = ft_mmots(s, c);
	p = malloc(sizeof(char *) * (mots + 1));
	if (!p)
		return (0);
	return (ft_rempp(p, s, c, mots));
}
